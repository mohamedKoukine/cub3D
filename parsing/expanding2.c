/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:38:04 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/08 13:15:37 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

char	*duh(char *line, int i, int cp)
{
	while (line[i])
	{
		if (line[i] == '"')
			cp++;
		if (line[i] == '\'' && cp % 2 == 0)
		{
			i++;
			while (line[i] != '\'' && line[i])
				i++;
		}
		if (line[i] == ('$' * -1))
			line[i] *= -1;
		if (line[i])
			i++;
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
			if (!ft_strncmp(&line[i], "<<<", 3)
				|| !ft_strncmp(&line[i], ">>)", 3))
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

char	*dollar0(char *line, char *line2, int s)
{
	int	i;
	int	j;
	int	cp;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$' && !if_its_q(line[i + 1]) && s == 0)
		{
			cp = con_d(&i, line, &s);
			if (cp % 2 != 0 && (!if_its_q(line[i]) || in_or_out(line, i - 1)))
				line2[j++] = '$';
		}
		else if (line[i] == '$' && if_its_q(line[i + 1]) && !in_or_out(line, i)
			&& s == 0)
		{
			i++;
			s = 1;
		}
		if (line[i])
			line2[j++] = line[i++];
	}
	line2[j] = '\0';
	return (line2);
}

char	*dollar(char *line, char *line2, t_list *lst)
{
	line2 = malloc(ft_strlen(line) + 1);
	if (!line2)
		ft_mallocerr(NULL, lst, line, NULL);
	line2 = dollar0(line, line2, 0);
	free (line);
	return (line2);
}
