/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:10:24 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 16:40:23 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

char	*magic_hide2(char *line, int s)
{
	int		i;
	char	q;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			q = line[i];
			while (line[++i])
			{
				if (line[i] == q)
					break ;
				if (line[i] >= 0 && s == 0)
					line[i] *= -1;
				if (line[i] < 0 && s == 1)
					line[i] *= -1;
			}
		}
		if (line[i])
			i++;
	}
	return (line);
}

char	*magic_hide(char *line)
{
	int		i;
	char	q;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			q = line[i];
			while (line[++i])
			{
				if (line[i] == q)
					break ;
				line[i] *= -1;
			}
		}
		if (line[i])
			i++;
	}
	return (line);
}

int	con_d(int *i, char *line, int *s)
{
	int	cp;

	cp = 0;
	while (line[*i] == '$')
	{
		(*i)++;
		cp++;
	}
	*s = 1;
	return (cp);
}
