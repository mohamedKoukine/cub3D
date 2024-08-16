/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:10:39 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/16 17:37:02 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	update_env_(t_m_list *lst, t_list *list)
{
	int	i;

	i = 0;
	while (lst->dup_com[i])
		i++;
	if (i)
		i--;
	while (list)
	{
		if (list->env[0] == '_' && list->env[1] == '=')
		{
			free (list->env);
			free (list->ex);
			list->env = ft_strjoin(list->key, "=", 1);
			list->ex = ft_substr(lst->dup_com[i], 0,
					ft_strlen(lst->dup_com[i]), 0);
			if (!list->ex)
				list->ex = ft_strdup("");
			list->env = ft_strjoin(list->env, list->ex, 0);
			if (!list->env)
				ft_mallocerr (lst, list, NULL, NULL);
		}
		list = list->next;
	}
}

void	update_env_1(t_m_list *lst, t_list *list)
{
	t_list	*lst1;

	lst1 = list;
	while (lst1)
	{
		if (lst1->env[0] == '_' && lst1->env[1] == '=')
		{
			free (lst1->env);
			free (lst1->ex);
			lst1->env = ft_strjoin(lst1->key, "=", 1);
			lst1->ex = ft_strdup("");
			if (!lst1->ex)
				ft_mallocerr (lst, list, NULL, NULL);
			break ;
		}
		lst1 = lst1->next;
	}
}

void	ft_function1(int ac, t_m_list *lst, t_fd *fd, t_list *list)
{
	int			i;

	update_env_(lst, list);
	i = 0;
	fd->id1 = 1;
	fd->id3 = 1;
	while (++i <= ac && fd->id1 != -1)
	{
		if (lst->dup_com[0] && ft_check_builtins(lst->dup_com) == 0 && ac == 1)
		{
			ft_redirection(lst, fd, 1);
			if (fd->id3 != -1 && fd->id3 != -5 && fd->id2 != -1)
				ft_builtins(lst->dup_com, list, lst, fd);
		}
		else
		{
			convert_env(list, fd, lst);
			command(fd, lst, list);
			free_all(fd->env);
		}
		lst = lst->next;
	}
	if (ac > 1)
		update_env_1(lst, list);
}

void	ft_function(t_fd *fd)
{
	int		ex;

	waitpid(fd->id_ex, &ex, 0);
	if (WIFSIGNALED(ex))
	{
		if (WTERMSIG(ex) == 3)
		{
			fd->ex_c = 131;
			write (1, "quit 3\n", 8);
		}
		if (WTERMSIG(ex) == 2)
		{
			g_s = 0;
			write (1, "\n", 1);
			fd->ex_c = 130;
		}
	}
	else
		fd->ex_c = WEXITSTATUS(ex);
}

void	ft_pipex(t_m_list *lst, t_list *list, t_fd *fd)
{
	struct termios	state;

	fd->id_ex = 0;
	open_heredoc(lst, list, 0, 0);
	if (g_s == 1)
	{
		remove_f_h(lst);
		return ;
	}
	tcgetattr(STDOUT_FILENO, &state);
	ft_function1(ft_lstsize(lst), lst, fd, list);
	if (fd->id3 == 1)
		ft_function(fd);
	while (waitpid(-1, NULL, 0) != -1)
		;
	tcsetattr(STDOUT_FILENO, TCSANOW, &state);
	signal(SIGINT, ft_handler);
	remove_f_h(lst);
}
