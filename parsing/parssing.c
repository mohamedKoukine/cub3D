/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:57:00 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/16 16:31:06 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

char	*add_space(char *line, t_list *lst, int i, int j)
{
	char	*line2;

	line2 = ft_calloc(ft_strlen(line), 3);
	if (!line2)
		ft_mallocerr(NULL, lst, line, NULL);
	while (++i < (int)ft_strlen(line))
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

char	*exit_code0(char *line, char *l, char *code)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "$?", 2))
		{
			j = 0;
			if (multi_pip(line, i))
				l[k++] = '0';
			else
				while (code[j])
					l[k++] = code[j++];
			i += 2;
		}
		else if (line[i])
			l[k++] = line[i++];
	}
	l[k] = '\0';
	return (l);
}

char	*exit_code(char *line, t_list *lst, t_fd *fd)
{
	char	*l;
	int		cp;
	char	*code;

	code = ft_itoa(fd->ex_c);
	if (!line)
		return (free(code), NULL);
	cp = exit_key(line);
	l = malloc (ft_strlen(line) - (cp * 2) + (cp * ft_strlen(code)) + 1);
	if (!l)
	{
		free (code);
		ft_mallocerr(NULL, lst, line, NULL);
	}
	magic_hide2 (line, 1);
	l = exit_code0(line, l, code);
	free (code);
	return (free (line), l);
}
