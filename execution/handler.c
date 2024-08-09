/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:41:19 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/09 10:28:05 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"
#include "../parsing/pr_minishell.h"

void	ft_handler0(int sig)
{
	if (sig == SIGINT)
		close(0);
}

void	ft_handler1(int sig)
{
	if (sig == SIGINT)
		printf("");
}

void	ft_handler(int sig)
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

void	convert_env(t_list *list, t_fd *fd, t_m_list *lst)
{
	int	i;
	int	j;

	i = -1;
	fd->env = malloc (sizeof(char *) * (ft_lstsize1(list) + 1));
	if (!fd->env)
		ft_mallocerr (lst, list, NULL, NULL);
	while (list)
	{
		j = -1;
		if (ft_strchr(list->env))
		{
			fd->env[++i] = malloc(ft_strlen(list->env) + 1);
			if (!fd->env[i])
				ft_mallocerr (lst, list, NULL, fd->env);
			while (list->env[++j])
				fd->env[i][j] = list->env[j];
			fd->env[i][j] = '\0';
		}
		list = list->next;
	}
	fd->env[++i] = NULL;
}
