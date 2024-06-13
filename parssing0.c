/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:52:34 by aelbouab          #+#    #+#             */
/*   Updated: 2024/06/12 14:58:00 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_nb(char *line)
{
	int	i;
	int	qd;
	int	qs;

	i = 0;
	qd = 0;
	qs = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			qd++;
		if (line[i] == '\'')
			qs++;
		i++;
	}
	if (qs % 2 != 0 || qd % 2 != 0)
		return (write(2, "syntax error\n", 13), 7);
	return (1);
}

void	*allocation(char *line)
{
	int		i;
	int		j;
	char	*nospace;

	i = 0;
	j = 0;
	while (line[i])
	{
		if ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			j++;
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		if (line[i])
		{
			j++;
			i++;
		}
	}
	nospace = malloc(j + 1);
	if (!nospace)
		return (NULL);
	return (nospace);
}

char	*rm_space(char *line)
{
	int		i;
	int		j;
	char	*nospace;

	i = 0;
	j = 0;
	nospace = allocation(line);
	while (line[i])
	{
		if (!((line[i] < 9 || line[i] > 13) && line[i] != 32))
			nospace[j++] = ' ';
		while (!((line[i] < 9 || line[i] > 13) && line[i] != 32))
			i++;
		if ((line[i] < 9 || line[i] > 13) && line[i] != 32)
			nospace[j++] = line[i];
		if (line[i])
			i++;
	}
	nospace[j] = '\0';
	return (nospace);
}

int	cases(char *line)
{
	if (!ft_strncmp(line, "<< |", 4)
		|| !ft_strncmp(line, "<<|", 3)
		|| !ft_strncmp(line, "< |", 3)
		|| !ft_strncmp(line, "<|", 2)
		|| !ft_strncmp(line, ">> |", 4)
		|| !ft_strncmp(line, ">>|", 3)
		|| !ft_strncmp(line, "> |", 3)
		|| !ft_strncmp(line, "||", 2)
		|| !ft_strncmp(line, "| |", 3)
		|| !ft_strncmp(line, "< <", 3)
		|| !ft_strncmp(line, "> >", 3)
		|| !ft_strncmp(line, ">> >>", 5)
		|| !ft_strncmp(line, ">>>", 3)
		|| !ft_strncmp(line, "<< <<", 5)
		|| !ft_strncmp(line, "<<<<", 4)
		|| !ft_strncmp(line, "< >", 3)
		|| !ft_strncmp(line, "&", 2)
		|| !ft_strncmp(line, "&&", 2)
		|| !ft_strncmp(line, "& &", 3)
		|| !ft_strncmp(line, "> <", 3))
		return (0);
	return (1);
}

int	syntax_error(char *line)
{
	int	ls;
	int	i;

	ls = ft_strlen(line);
	i = 0;
	if (line[0] == '|' || line[ls - 1] == '|'
		|| line[ls - 1] == '>' || line[ls - 1] == '<')
		return (write(2, "syntax error\n", 13), 9);
	while (i < ls)
	{
		if (!cases(&line[i]))
			return (write(2, "syntax error\n", 13), 8);
		i++;
	}
	return (1);
}
