/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:57:00 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 17:56:30 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

char	*add_space(char *line, int ls, int i, int j)
{
	char	*line2;

	line2 = ft_calloc(ls, 3);
	if (!line2)
		return (NULL);
	while (++i < ls)
	{
		if ((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>'))
		{
			line2[j++] = ' ';
			line2[j++] = line[i++];
			line2[j++] = line[i];
			line2[j++] = ' ';
		}
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			line2[j++] = ' ';
			line2[j++] = line[i];
			line2[j++] = ' ';
		}
		else
			line2[j++] = line[i];
	}
	return (line2[j] = '\0', free(line), line2);
}

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

int	exit_key(char *line)
{
	int	i;
	int	cp;

	i = 0;
	cp = 0;
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "$?", 2))
		{
			cp++;
			i++;
		}
		if (line[i])
			i++;
	}
	return (cp);
}

int	multi_pip(char *line, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (line[j] == '|')
			return (1);
		j++;
	}
	return (0);
}

char	*exit_code(char *line, char *code, int i, int k)
{
	char	*line2;
	int		j;
	int		cp;

	if (!line)
		return (0);
	cp = exit_key(line);
	line2 = malloc (ft_strlen(line) - (cp * 2) + (cp * ft_strlen(code)) + 1);
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "$?", 2))
		{
			j = 0;
			if (multi_pip(line, i))
				line2[k++] = '0';
			else
				while (code[j])
					line2[k++] = code[j++];
			i = i + 2;
		}
		else if (line[i])
			line2[k++] = line[i++];
	}
	free (code);
	return (line2[k] = '\0', free (line), line2);
}
