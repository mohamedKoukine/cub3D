/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:32:22 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/16 16:50:20 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

char	*line_shower(char *line, t_list *lst, t_fd *fd)
{
	int	e_c;

	e_c = fd->ex_c;
	if (!line)
		return (NULL);
	line = ft_strtrim(line, " ", 1);
	if (!line)
		ft_mallocerr(NULL, lst, line, NULL);
	line = magic_hide(line);
	fd->ex_c = quotes_nb(line);
	if (!line || fd->ex_c)
		return (NULL);
	line = rm_space(line, lst);
	fd->ex_c = syntax_error(line);
	if (!line || fd->ex_c)
		return (NULL);
	line = add_space(line, lst, -1, 0);
	line = ambiguous(magic_hide2(line, 1), lst);
	line = handel_here(line, 0, 0, lst);
	line = handel_ambi(line, 0, 0, lst);
	line = expanding(magic_hide2(line, 1), lst);
	magic_hide2(line, 0);
	if (is_empty(line))
		return (NULL);
	return (fd->ex_c = e_c, line);
}

char	*read_lines(char *line, t_fd *fd, t_list *lst)
{
	static char	*tmp;

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

char	*get_home1(t_list *lst, t_m_list *list)
{
	char	*pwd;
	char	*home;
	int		i;
	int		j;

	i = 0;
	j = -1;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	while (pwd[i])
	{
		if (!ft_strncmp("/Desktop", &pwd[i], 8))
			break ;
		i++;
	}
	home = malloc(i + 1);
	if (!home)
		ft_mallocerr(list, lst, pwd, NULL);
	while (++j < i)
		home[j] = pwd[j];
	home[j] = '\0';
	free (pwd);
	return (home);
}

void	ft_while(t_list *lst, t_fd *fd, t_m_list *list, char *line)
{
	while (1)
	{
		line = read_lines(line, fd, lst);
		line = exit_code(magic_hide(line), lst, fd);
		garbag_find (line);
		line = line_shower(line, lst, fd);
		if (!line)
			continue ;
		list = list_to_exe(lst, line);
		ft_pipex(list, lst, fd);
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
}

int	main(int ac, char **av, char **env)
{
	t_list		*lst;
	t_fd		fd;

	(void)av;
	(void)ac;
	lst = NULL;
	if (!isatty(STDIN_FILENO))
		exit(1);
	ft_env(env, &lst, 0, NULL);
	fd.ex_c = 0;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	ft_while(lst, &fd, NULL, NULL);
	return (0);
}
