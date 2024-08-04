/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:07:22 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 16:13:56 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

int	cp_conter(t_m_list *tmp, int cp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp->d_com[i])
	{
		j = 0;
		while (tmp->file[j] && tmp->d_h[j])
		{
			if (!ft_strcmp(tmp->d_h[j], tmp->d_com[i])
				|| tmp->file[j] == tmp->d_com[i])
			{
				j = 0;
				i++;
				continue ;
			}
			j++;
		}
		if (tmp->d_com[i])
		{
			cp++;
			i++;
		}
	}
	return (cp);
}

int	d_cp(char *line, int j)
{
	int	cp;

	cp = 0;
	while (line[j] == '$' || line[j] == '"' || line[j] == '\'')
	{
		if (line[j] == '"' || line[j] == '\'')
		{
			j++;
			continue ;
		}
		cp++;
		j++;
	}
	return (cp);
}

void	ddhere_con(char *line, int *i, int *j, char *line2)
{
	int	cp;
	int	s;

	s = 0;
	cp = 0;
	while (line[*i] == '$')
	{
		(*i)++;
		cp++;
	}
	if (cp % 2 != 0 && if_its_q(line[*i]))
	{
		s = 0;
		while (++s < cp)
			line2[(*j)++] = '$';
	}
	if ((cp % 2 == 0 && if_its_q(line[*i])) || !if_its_q(line[*i]))
	{
		s = -1;
		while (++s < cp)
			line2[(*j)++] = '$';
	}
}

char	*ddhere(char *line, int i, int j, t_list *lst)
{
	char	*line2;

	line2 = malloc(ft_strlen(line) + 1);
	if (!line2)
	{
		free (line);
		ft_exit (1, "minishell", "filed allocation", lst);
	}
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "<<", 2))
		{
			while (line[i] == '<' || line[i] == ' ')
				line2[j++] = line[i++];
			if (line[i] == '$')
				ddhere_con(line, &i, &j, line2);
		}
		if (line[i])
			line2[j++] = line[i++];
	}
	return (line2[j] = '\0', free(line), line2);
}
