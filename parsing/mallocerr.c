/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocerr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:14:26 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/09 08:29:21 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

int	strchr_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	garbag_find(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i])
	{
		if (arg[i] < 0)
			arg[i] *= -1;
		i++;
	}
}

int	if_its_q(char q)
{
	if (q == '"' || q == '\'')
		return (1);
	return (0);
}

char	*digit_dollar(char *line, t_list *lst, int k)
{
	char	*str;

	if (line[k] >= '0' && line[k] <= '9')
	{
		str = malloc(2);
		if (!str)
			ft_mallocerr(NULL, lst, line, NULL);
		str[0] = line[k];
		str[1] = '\0';
		return (str);
	}
	return (NULL);
}

void	ft_mallocerr(t_m_list *list, t_list *lst, char *line, char **lines)
{
	if (line)
		free(line);
	if (lines)
		free(lines);
	if (lst)
		free_env(lst);
	if (list)
		free_list(list);
	write (2, "minishell: filed allocation", 28);
	exit (1);
}
