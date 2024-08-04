/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:37:36 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/04 14:56:05 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	ft_exit(int l, char *s, char *err, t_list *lst)
{
	int	i;

	i = 0;
	if (l == 0)
	{
		if (lst)
			free_env(lst);
		exit (0);
	}
	else
	{
		if (lst)
			free_env(lst);
		printf("minishell: ");
		printf("%s: ", s);
		printf("%s", err);
		exit (l);
	}
}

int	ft_check_builtins(char **line)
{
	if (ft_strcmp(line[0], "export") == 0)
		return (0);
	else if (ft_strcmp(line[0], "env") == 0)
		return (0);
	else if (ft_strcmp(line[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(line[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(line[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(line[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(line[0], "unset") == 0)
		return (0);
	else
		return (1);
}

int	ft_builtins(char **line, t_list *list, t_m_list *lst, t_fd *fd)
{
	int	i;

	i = fd->ex_c;
	fd->ex_c = 0;
	if (ft_strcmp(line[0], "export") == 0)
		ft_export(line, list, fd);
	else if (ft_strcmp(line[0], "env") == 0)
		aff_env(line, list, fd);
	else if (ft_strcmp(line[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(line[0], "echo") == 0)
		ft_echo(lst, 0);
	else if (ft_strcmp(line[0], "exit") == 0)
		my_exit(lst, fd, i);
	else if (ft_strcmp(line[0], "cd") == 0)
		ft_cd(list, lst, fd);
	else if (ft_strcmp(line[0], "unset") == 0)
		ft_unset(list, lst, line, fd);
	else
		return (fd->ex_c = i, 1);
	return (0);
}

void	command_con(t_fd	*fd, t_m_list *lst, t_list *list, int p[2])
{
	g_s = 1;
	signal(SIGQUIT, SIG_DFL);
	g_s = 0;
	ft_redirection(lst, fd, 0);
	if (lst->first_comm)
	{
		parsing_b(lst->first_comm, fd->env, fd);
		if (fd->id == 1 && lst->next)
		{
			close(p[0]);
			dup2(p[1], STDOUT_FILENO);
			close(p[1]);
		}
		if (ft_builtins(lst->dup_com, list, lst, fd) == 0)
			exit(fd->ex_c);
		else if (execve(fd->path, lst->dup_com, fd->env) == -1)
		{
			write (2, "minishell: ", 11);
			write (2, lst->first_comm, ft_strlen(lst->first_comm));
			write (2, ": ", 2);
			write (2, "command not found\n", 18);
			exit (127);
		}
	}
	exit(0);
}

void	command(t_fd *fd, t_m_list *lst, t_list *list)
{
	int		p[2];

	if (pipe(p) == -1)
		ft_exit(1, "pipe", "ERROR PIPE\n", NULL);
	fd->id1 = fork();
	if (fd->id1 == -1)
	{
		close(p[1]);
		close(p[0]);
		printf ("minishell: fork: Resource temporarily unavailable\n");
		return ;
	}
	signal(SIGINT, ft_handler1);
	if (fd->id1 == 0)
		command_con(fd, lst, list, p);
	else
	{
		if (lst->next == NULL)
			fd->id_ex = fd->id1;
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
	}
}
