/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:41:19 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/04 15:04:47 by mkaoukin         ###   ########.fr       */
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
