/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:36:45 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/09 10:28:30 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	read_heredoc(char	*line, int i, t_m_list *lst, t_list *list)
{
	while (1)
	{
		line = readline("> ");
		if (!ttyname(0))
		{
			g_s = 1;
			open (ttyname(2), O_RDWR);
			break ;
		}
		if (!line)
			break ;
		if ((ft_strlen1(line, 1) == ft_strlen1(lst->file[i], 0))
			&& (ft_strncmp(line, lst->file[i], ft_strlen1(line, 1)) == 0))
		{
			free(line);
			break ;
		}
		if (!ft_strcmp(lst->d_h[i], "<<"))
			line = expanding(line, list);
		write (lst->w_h, line, ft_strlen1(line, 0));
		write (lst->w_h, "\n", 1);
		free (line);
		line = NULL;
	}
}

int	here_d(t_m_list *lst, int i, t_list *list)
{
	char	*line;

	line = NULL;
	unlink("here_doc");
	lst->w_h = open ("here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	lst->r_h = open ("here_doc", O_RDONLY, 0777);
	unlink("here_doc");
	if (lst->w_h == -1 || lst->r_h == -1)
		ft_exit(1, "minishell,", "filed heredoc\n", list);
	read_heredoc(line, i, lst, list);
	close (lst->w_h);
	signal(SIGINT, ft_handler);
	if (g_s == 1)
		return (1);
	return (0);
}

void	check_number_herdc(t_m_list *lst, t_list *list, int i, int cp)
{
	while (lst->d_h[i])
	{
		if (!ft_strncmp(lst->d_h[i], "<<", 2))
			cp++;
		i++;
	}
	if (cp > 16)
	{
		free_list (lst);
		ft_exit(2, "maximum here-document count exceeded\n", "\0", list);
	}
}

void	open_heredoc(t_m_list *lst, t_list *list, int i, int cp)
{
	check_number_herdc(lst, list, i, cp);
	while (lst)
	{
		i = -1;
		lst->r_h = 200;
		while (lst->d_h[++i])
		{
			if ((!ft_strcmp(lst->d_h[i], "<<"))
				|| (!ft_strcmp(lst->d_h[i], "<<<")))
			{
				signal(SIGINT, ft_handler0);
				close(lst->r_h);
				if (here_d(lst, i, list))
					return ;
			}
		}
		lst = lst->next;
	}
}
