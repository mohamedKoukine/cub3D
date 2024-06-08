/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:32:22 by aelbouab          #+#    #+#             */
/*   Updated: 2024/06/08 14:06:25 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_stack(t_m_list *list)
{
	t_m_list	*tmp;
	int			r;

	tmp = list;
	while (tmp)
	{
		magic_hide(tmp->command);
		magic_hide(tmp->first_comm);
		r = 0;
		while (tmp->d_com && tmp->d_com[r])
			magic_hide(tmp->d_com[r++]);
		r = 0;
		while (tmp->d_h && tmp->d_h[r])
			magic_hide(tmp->d_h[r++]);
		r = 0;
		while (tmp->file && tmp->file[r])
			magic_hide(tmp->file[r++]);
		r = 0;
		while (tmp->dup_com && tmp->dup_com[r])
			magic_hide(tmp->dup_com[r++]);
		tmp = tmp->next;
	}
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
	if (quotes_nb(line) != 1)
		return (NULL);
	line = rm_space(line);
	if (syntax_error(line) != 1)
		return (NULL);
	line = add_space(line);
	if (!line)
		exit (1);
	line = dollar(line, 0, 0, NULL);
	line = expanding(magic_hide2(line), lst);
	magic_hide2(line);
	if (is_empty(line))
		return (NULL);
	return (line);
}

void	list_to_exe(char *line)
{
	t_m_list	*list;

	list = split_all(line);
	list = en_s(list, 0);
	list = final_s(list);
	print_stack(list);
}

char	*read_lines(char *line)
{
	char	*tmp;

	line = readline("minishell$====>");
	tmp = NULL;
	if (!line)
	{
		printf("\n");
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

int	main(int ac, char **av, char **env)
{
	t_list	*lst;
	char	*line;

	(void) ac;
	(void) av;
	lst = NULL;
	line = NULL;
	while (1)
	{
		ft_env(env, &lst);
		line = read_lines(line);
		line = line_shower(line, lst);
		if (!line)
			continue ;
		list_to_exe(line);
		free(line);
	}
	return (0);
}
