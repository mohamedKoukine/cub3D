/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:32:22 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/01 14:02:41 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

void print_stack(t_m_list *list)
{
	int r;

	while (list)
	{
		printf("c = %s\n", list->command);
		printf("f_c = %s\n", list->first_comm);
		r = 0;
		while (list->d_com && list->d_com[r])
			printf("{%s}  ", list->d_com[r++]);
		printf("\n");
		r = 0;
		while (list->d_h && list->d_h[r])
			printf("[%s]  ", list->d_h[r++]);
		printf("\n");
		r = 0;
		while (list->file && list->file[r])
			printf("(%s)  ", list->file[r++]);
		printf("\n");
		r = 0;
		while (list->dup_com && list->dup_com[r])
			printf("**%s**  ", list->dup_com[r++]);
		printf("\n");
		list = list->next;
	}
}

char *no_qutes(char *line, int fre)
{
	char *no_q;
	char q = '\0';
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
		else if (line[i] && line[i] != q)
			no_q[j++] = line[i++];
	}
	no_q[j] = '\0';
	if (fre)
		free(line);
	return (no_q);
}

void	garbag_find(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < 0)
			arg[i] *= -1;
		i++;
	}
}

t_m_list *decript_stack(t_m_list *list)
{
	t_m_list *tmp;
	int r;

	tmp = list;
	while (tmp)
	{
		garbag_find(tmp->command);
		r = -1;
		while (tmp->d_com && tmp->d_com[++r])
			garbag_find(tmp->d_com[r]);
		tmp = tmp->next;
	}
	return (list);
}

t_m_list *split_all(char *line)
{
	char **commands;
	t_m_list *list;
	t_m_list *new;
	int i;

	i = 1;
	commands = ft_split(line, '|');
	list = ft_lstnew(no_qutes(commands[0], 0), ft_split(commands[0], ' '));
	while (commands[i])
	{
		new = ft_lstnew(no_qutes(commands[i], 0), ft_split(commands[i], ' '));
		ft_lstadd_back(&list, new);
		i++;
	}
	i = 0;
	while(commands[i])
		free(commands[i++]);
	free(commands);
	return (list);
}

int	chek_ambi(char *line, t_list *lst)
{
	int i = 0;
	int cp = 0;
	char *p = NULL;
	char *a = NULL;
	while(line[i])
	{
		if (!ft_isalnum(line[i]))
			break ;
		cp++;
		i++;
	}
	p = malloc(cp + 1);
	i = 0;
	while(line[i])
	{
		if (!ft_isalnum(line[i]))
			break ;
		p[i] = line[i];
		i++;
	}
	p[i] = '\0';
	while (lst)
	{
		if (!ft_strcmp(p,lst->key))
		{
			a = ft_strtrim(lst->ex, " ", 0);
			i = 0;
			while (a[i])
			{
				if (a[i] == ' ')
				{
					free(a);
					free(p);
					return (1);
				}
				i++;
			}
			
		}
		lst = lst->next;
	}
	if (a)
		free(a);
	free(p);
	return (0);
}

char	*ambiguous(char *line, t_list *lst)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_strncmp(&line[i], ">", 1) || (line[i] == '<' && line[i + 1] != '<'))
		{
			while (line[i] == '>' || line[i] == '<' || line[i] == ' ')
				i++;
			while (line[i] && line[i] != ' ')
			{
				if (line[i] == '$')
				{
					i++;
					if (chek_ambi(&line[i], lst))
						line[i - 1] = line[i - 1] * -1;
				}
				if (line[i])
					i++;
			}
		}
		if (line[i])
			i++;
	}
	return (line);
}

int	include_q(char *line)
{
	int i = 0;
	while (line[i] == ' ' && line[i])
		i++;
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*handel_here(char *line)
{
	char	*line2;
	int		i = 0;
	int		j = 0;
	int		ls = ft_strlen(line) + 17;
	
	line2 = malloc(ls);
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "<<", 2))
		{
			while (line[i] == '<' || line[i] == ' ')
			{
				if (line[i] == ' ' && include_q(&line[i]))
					line2[j++] = '<';
				while (line[i] == ' ')
					line2[j++] = line[i++];
				line2[j++] = line[i++];
			}
		}
		if (line[i])
			line2[j++] = line[i++];
	}
	while (j < ls)
		line2[j++] = '\0';
	free(line);
	return (line2);
}

char *line_shower(char *line, t_list *lst, t_fd *fd)
{
	if (!line)
		return (0);
	line = ft_strtrim(line, " ", 1);
	line = magic_hide(line);
	fd->ex_c = quotes_nb(line);
	if (!line || fd->ex_c)
		return (NULL);
	line = rm_space(line);
	fd->ex_c = syntax_error(line);
	if (!line || fd->ex_c)
		return (NULL);
	line = add_space(line);
	if (!line)
		exit(1);
	line = ambiguous(magic_hide2(line), lst);
	magic_hide2(line);
	line = handel_here(line);
	line = expanding(magic_hide2(line), lst);
	magic_hide2(line);
	if (is_empty(line))
		return (NULL);
	return (line);
}

t_m_list *clear_lst(t_m_list *list)
{
	t_m_list *tmp;
	int i;

	i = 0;
	tmp = list;

	while (tmp)
	{
		i = 0;
		while (tmp->d_com[i])
		{
			tmp->d_com[i] = no_qutes(tmp->d_com[i], 1);
			i++;
		}
		tmp = tmp->next;
	}
	return (list);
}

t_m_list    *home_pl(t_m_list *list, t_list *lst, t_m_list *tmp)
{
    int            i;

    while (tmp)
    {
        i = -1;
        while (tmp->d_com[++i])
        {
            if (!ft_strcmp(tmp->d_com[i], "~"))
            {
                
                free(tmp->d_com[i]);
                tmp->d_com[i] = ft_strdup(get_home(lst));
            }
        }
        tmp = tmp->next;
    }
    return (list);
}

t_m_list *list_to_exe(char *line, t_list *lst)
{
	t_m_list *list;

	list = split_all(line);
	free(line);
	list = clear_lst(list);
	list = home_pl(list, lst, list);
	list = en_s(list, 0);
	list = final_s(list);
	list = decript_stack(list);
	// print_stack(list);
	list->p[0] = dup(STDIN_FILENO);
	list->p[1] = dup(STDOUT_FILENO);
	return (list);
}
void free_env(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		free (lst->env);
		if (lst->ex)
			free (lst->ex);
		free (lst->key);
		lst = lst->next;
		free (tmp);
	}
}

char *read_lines(char *line, t_fd *fd, t_list *lst)
{
	static char *tmp;

	line = readline("➜ minishell$ ✗ ");
    if (g_s == 1)
    {
        fd->ex_c = 1;
        g_s = 0;
    }
	if (!line)
	{
		free_env(lst);
		printf("exit\n");
		exit(fd->ex_c);
	}
	if (is_empty(line))
		return (0);
	if (line[0] != '\0' && ft_strcmp(line, tmp))
	{
		free (tmp);
		add_history(line);
		tmp = ft_strdup(line);
	}
	return (line);
}

void ft_handler(int sig)
{
    if (sig == SIGINT)
    {
        g_s = 1;
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void free_list(t_m_list *list)
{
	int	i;
	t_m_list *tmp;
	
	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		i = 0;
		while (list->d_com[i])
			free(list->d_com[i++]);
		free (list->d_com);
		free (list->command);
		if (list->dup_com)
			free(list->dup_com);
		if (list->d_h)
			free(list->d_h);
		if (list->file)
			free(list->file);
		list = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}
	
void f()
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
	// atexit(f);
	t_list *lst;
	t_m_list *list;
	char *line;
	char *ito;
	t_fd	fd;

	(void)av;
	(void)ac;
	lst = NULL;
	list = NULL;
	line = NULL;
	ft_env(env, &lst);
	fd.ex_c = 0;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	while (1)
	{
		line = read_lines(line, &fd, lst);
		ito = ft_itoa(fd.ex_c);
		line = exit_code(line, ito);
		free (ito);
		line = line_shower(line, lst, &fd);
		if (!line)
			continue;
		list = list_to_exe(line, lst);
		ft_pipex(list, lst, &fd);
		if (list && list->ptr_unset)
		{
			lst = list->ptr_unset;
			list->ptr_unset = NULL;
		}
		dup2(list->p[0], STDIN_FILENO);
		dup2(list->p[1], STDOUT_FILENO);
		close (list->p[0]);
		close (list->p[1]);
		free_list(list);
		list = NULL;
	}
	return (0);
}
