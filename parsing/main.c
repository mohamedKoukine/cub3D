/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:32:22 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/05 13:09:53 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

void	print_stack(t_m_list *list)
{
	int			r;

	while (list)
	{
		printf("c = %s\n",list->command);
		printf("f_c = %s\n",list->first_comm);
		r = 0;
		while (list->d_com && list->d_com[r])
			printf("{%s}  ",list->d_com[r++]);
		printf("\n");
		r = 0;
		while (list->d_h && list->d_h[r])
			printf("[%s]  ",list->d_h[r++]);
		printf("\n");
		r = 0;
		while (list->file && list->file[r])
			printf("(%s)  ",list->file[r++]);
		printf("\n");
		r = 0;
		while (list->dup_com && list->dup_com[r])
			printf("**%s**  ",list->dup_com[r++]);
		printf("\n");
		list = list->next;
	}
}

char *no_qutes(char *line)
{
	char *no_q;
	char q;
	int i = 0;
	int j = 0;

	if (!line)
		return (NULL);
	no_q = malloc(ft_strlen(line) + 1);
	if (!no_q)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			q = line[i];
			i++;
			while (line[i] != q && line[i])
				no_q[j++] = line[i++];
			i++;
		}
		if (line[i] && line[i] != q)
			no_q[j++] = line[i++];
	}
	no_q[j] = '\0';
	return (no_q);
}

void	clear_stack(t_m_list *list)
{
	t_m_list	*tmp;
	int			r;

	tmp = list;
	while (tmp)
	{
		tmp->command = no_qutes(tmp->command);
		tmp->first_comm = no_qutes(tmp->first_comm);
		r = -1;
		while (tmp->d_com && tmp->d_com[++r])
			tmp->d_com[r] = no_qutes(tmp->d_com[r]);
		r = -1;
		while (tmp->d_h && tmp->d_h[++r])
			tmp->d_h[r] = no_qutes(tmp->d_h[r]);
		r = -1;
		while (tmp->file && tmp->file[++r])
			tmp->file[r] = no_qutes(tmp->file[r]);
		r = -1;
		while (tmp->dup_com && tmp->dup_com[++r])
			tmp->dup_com[r] = no_qutes(tmp->dup_com[r]);
		tmp = tmp->next;
	}
}

t_m_list	*decript_stack(t_m_list *list)
{
	t_m_list	*tmp;
	int			r;

	tmp = list;
	while (tmp)
	{
		magic_hide(tmp->command);
		r = -1;
		while (tmp->d_com && tmp->d_com[++r])
			magic_hide(tmp->d_com[r]);
		r = -1;
		while (tmp->d_h && tmp->d_h[++r])
			magic_hide(tmp->d_h[r]);
		r = -1;
		while (tmp->file && tmp->file[++r])
			magic_hide(tmp->file[r]);
		tmp = tmp->next;
	}
	return (list);
}

t_m_list	*split_all(char *line)
{
	char		**commands;
	t_m_list	*list;
	t_m_list	*new;
	int			i;

	i = 1;
	commands = ft_split(line, '|');
	list = ft_lstnew(commands[0], ft_split(commands[0], ' '));
	while (commands[i])
	{
		new = ft_lstnew(commands[i], ft_split(commands[i], ' '));
		ft_lstadd_back(&list, new);
		i++;
	}
	return (list);
}

char	*line_shower(char *line, t_list *lst)
{
	if (!line)
		return (0);
	line = ft_strtrim(line, " ");
	if (ft_strcmp(line, "env") == 0)
	{
		aff_env(lst);
		return (NULL);
	}
	line = magic_hide(line);
	if (!line || quotes_nb(line) != 1)
		return (NULL);
	line = rm_space(line);
	e_code = syntax_error(line);
	if (!line || e_code)
		return (NULL);
	line = add_space(line);
	if (!line)
		exit (1);
	line = magic_hide(dollar(magic_hide(line), 0, 0, NULL));
	line = expanding(magic_hide2(line), lst);
	magic_hide2(line);
	if (is_empty(line))
		return (NULL);
	return (line);
}

t_m_list	*list_to_exe(char *line)
{
	t_m_list	*list;

	list = split_all(line);
	list = en_s(list, 0);
	list = final_s(list);
	list = decript_stack(list);
	clear_stack(list);
	// print_stack(list);
	list->p[0] = dup(STDIN_FILENO);
	list->p[1] = dup(STDOUT_FILENO);
	return (list);
}         

char	*read_lines(char *line)
{
	static char	*tmp;

	line = readline("➜ minishell$ ✗ ");
	if (!line)
	{
		printf("exit");
		exit (0);
	}
	if (is_empty(line))
		return (0);
	if (line[0] != '\0' && ft_strcmp(line, tmp))
	{
		add_history(line);
		tmp = ft_strdup(line);
	}
	return (line);
}

void ft_handler(int sig)
{
	(void)sig;
	printf("\n");
    rl_on_new_line(); 
	rl_replace_line("", 0);
    rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	t_list		*lst;
	t_m_list	*list;
	char		*line;

	(void) av;
	(void) ac;
	lst = NULL;
	line = NULL;
	ft_env(env, &lst);
	while (1)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
		line = read_lines(line);
		line = line_shower(line, lst);
		if (!line)
			continue ;
		list  = list_to_exe(line);
		ft_pipex(ft_lstsize(list), list, env);
		free(line);
		line = NULL;
		dup2(list->p[0],STDIN_FILENO);
		dup2(list->p[1],STDOUT_FILENO);
	}
	return (0);
}
