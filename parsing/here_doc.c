/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:57:29 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/08 11:18:55 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

void	here_dollar_con1(char *line, int j, char *hold, int cp)
{
	if (!line[j + cp])
	{
		while (line[j] == '$')
		{
			if (line[j] == '$' && (hold[0] == '>' || hold[0] == '<')
				&& cp % 2 == 0)
				line[j] = line[j] * (-1);
			j++;
		}
	}
}

void	here_dollar_con(char *line, int *i, char *hold)
{
	char	q;

	while (line[*i] != ' ' && line[*i])
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			q = line[*i];
			while (line[*i] != q)
			{
				if (line[*i] == '$' && !ft_strncmp(hold, "<<", 2))
					line[*i] = line[*i] * (-1);
				(*i)++;
			}
			(*i)++;
			continue ;
		}
		if (line[*i] == '$' && !ft_strncmp(hold, "<<", 2))
			line[*i] = line[*i] * (-1);
		if (line[*i])
			(*i)++;
	}
}

char	*here_dollar(char *line, t_list *lst, int i)
{
	int		j;
	int		cp;
	char	*hold;

	line = ddhere(line, 0, 0, lst);
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			hold = &line[i];
			while (line[i] == '<' || line[i] == '>' || line[i] == ' ')
				i++;
			cp = d_cp(line, i);
			j = i;
			here_dollar_con(line, &i, hold);
			here_dollar_con1(line, j, hold, cp);
		}
		if (line[i])
			i++;
	}
	return (line);
}

int	include_q(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' && line[i])
		i++;
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*handel_here(char *line, int i, int j, t_list *lst)
{
	char	*line2;
	int		ls;

	ls = ft_strlen(line) + 17;
	line2 = malloc(ls);
	if (!line2)
		ft_mallocerr(NULL, lst, line, NULL);
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "<<", 2))
		{
			while (line[i] == '<' || line[i] == ' ')
			{
				if (line[i] == ' ' && include_q(&line[i]))
					line2[j++] = '<';
				while (line[i] == ' ')
					line2[j++] = line[i++];
				line2[j++] = line[i++];
			}
		}
		if (line[i])
			line2[j++] = line[i++];
	}
	return (line2[j++] = '\0', free(line), line2);
}
