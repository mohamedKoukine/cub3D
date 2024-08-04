/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:33:16 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/04 13:34:05 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	check_ambiguous_ch(t_m_list *lst, t_fd *fd, int i, int l)
{
	int	j;

	j = -1;
	while (lst->file[i][++j])
	{
		if (lst->file[i][j] == '$' && lst->file[i][j + 1] != '\0'
			&& ft_strcmp(lst->d_h[i], ">>)") && ft_strcmp(lst->d_h[i], ">)"))
			ft_exit(1, lst->file[i], "ambiguous redirect\n", NULL);
	}
	if (l)
		fd->id2 = open(lst->file[i], O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		fd->id2 = open(lst->file[i], O_CREAT | O_RDWR | O_TRUNC, 0777);
}

void	ft_redirection_ch(t_m_list *lst, t_fd *fd, int i)
{
	while (lst->d_h[++i])
	{
		if (lst->d_h[i][0] == '>' && lst->d_h[i][1] == '>')
			check_ambiguous_ch(lst, fd, i, 1);
		else if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')
			fd->id3 = lst->r_h;
		else if (lst->d_h[i][0] == '<')
			fd->id3 = open(lst->file[i], O_RDWR, 0777);
		else
			check_ambiguous_ch(lst, fd, i, 0);
		if (fd->id2 == -1 || fd->id3 == -1)
			ft_exit(1, lst->file[i], "No such file or directory\n", NULL);
	}
}

void	check_ambiguous_par(t_m_list *lst, t_fd *fd, int i, int l)
{
	int	j;

	j = -1;
	while (lst->file[i][++j])
	{
		if (lst->file[i][j] == '$' && lst->file[i][j + 1] != '\0'
			&& ft_strcmp(lst->d_h[i], ">>)") && ft_strcmp(lst->d_h[i], ">)"))
		{
			fd->id3 = -5;
			printf ("minishell: %s: ambiguous redirect\n", lst->file[i]);
			return ;
		}
	}
	if (l)
		fd->id2 = open(lst->file[i], O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		fd->id2 = open(lst->file[i], O_CREAT | O_RDWR | O_TRUNC, 0777);
}

void	ft_redirection_par(t_m_list *lst, t_fd *fd, int i)
{
	while (lst->d_h[++i])
	{
		if (lst->d_h[i][0] == '>' && lst->d_h[i][1] == '>')
			check_ambiguous_par(lst, fd, i, 1);
		else if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')
			fd->id3 = lst->r_h;
		else if (lst->d_h[i][0] == '<')
			fd->id3 = open(lst->file[i], O_RDWR, 0777);
		else
			check_ambiguous_par(lst, fd, i, 0);
		if (fd->id2 == -1 || fd->id3 == -1)
		{
			printf ("minishell: %s: No such file or directory\n", lst->file[i]);
			break ;
		}
	}
}

void	ft_redirection(t_m_list *lst, t_fd *fd, int i)
{
	fd->id = 1;
	fd->id2 = -2;
	fd->id3 = -2;
	if (i == 0)
		ft_redirection_ch(lst, fd, -1);
	else
		ft_redirection_par(lst, fd, -1);
	if (fd->id2 != -2)
	{
		fd->id = 0;
		dup2(fd->id2, STDOUT_FILENO);
		close(fd->id2);
	}
	if (fd->id3 != -2)
	{
		dup2(fd->id3, STDIN_FILENO);
		close(fd->id3);
	}
}
