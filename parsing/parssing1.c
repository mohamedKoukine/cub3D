/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:10:24 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/29 12:44:55 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

char	*magic_hide2(char *line)
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

int	if_its_q(char q)
{
	if (q == '"' || q == '\'')
		return (1);
	return (0);
}

int	in_or_out(char *line, int f)
{
	int		i;
	char	q;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			q = line[i];
			i++;
			while (line[i] != q)
			{
				if (i == f)
					return (1);
				i++;
			}
		}
		if (i == f)
			return (0);
		if (line[i])
			i++;
	}
	return (0);
}

char	*dollar(char *line, int i, int j, char *line2)
{
	int		cp;
	int		s = 0;

	line2 = malloc(ft_strlen(line) + 1);
	if (!line2)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && !if_its_q(line[i + 1]) && s == 0)
		{
			cp = 0;
			while (line[i] == '$')
			{
				i++;
				cp++;
			}
			if (cp % 2 != 0 && (!if_its_q(line[i]) || in_or_out(line,i - 1)))
				line2[j++] = '$';
			s = 1;
		}
		else if (line[i] == '$' && if_its_q(line[i + 1]) && !in_or_out(line, i) && s == 0)
		{
			i++;
			s = 1;
		}
		if (line[i])
			line2[j++] = line[i++];
	}
	line2[j] = '\0';
	free (line);
	return (line2);
}

char	*duh(char *line, int i, int cp)
{
	while (line[++i])
	{
		if (line[i] == '"')
			cp++;
		if (line[i] == '\'' && cp % 2 == 0)
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		if (line[i] == ('$' * -1))
			line[i] *= -1;
	}
	return (line);
}

int	cp_hd(char *line)
{
	int	i;
	int	cp;

	i = 0;
	cp = 0;
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "<<", 2) || !ft_strncmp(&line[i], ">>", 2))
		{
			if (!ft_strncmp(&line[i], "<<<", 3))
				i++;
			cp++;
			i += 2;
		}
		else if (!ft_strncmp(&line[i], ">", 1) || !ft_strncmp(&line[i], "<", 1))
		{
			cp ++;
			i++;
		}
		else
			i++;
	}
	return (cp);
}
