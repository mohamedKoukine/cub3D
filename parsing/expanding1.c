/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:19:41 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/09 08:21:51 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

int	checkis_one(char **line, int on, int s)
{
	int	i;

	i = 0;
	if (on == 0)
	{
		while (line[i])
		{
			if (!ft_strcmp(line[i], "<<")
				&& strchr_char(line[i + 1], '$'))
				return (1);
			i++;
		}
	}
	else
	{
		while (line[i])
		{
			if ((!ft_strncmp(line[i], ">", 1) || !ft_strncmp(line[i], "<", 1))
				&& !ft_strncmp(line[i + 1], "$", 1) && s == 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int	here_expand(char **line, char *str, t_list *lst)
{
	int		s;
	char	*tmp;

	s = 0;
	if (checkis_one(line, 0, s) == 1)
		return (1);
	while (lst)
	{
		tmp = ft_strtrim(lst->ex, " ", 0);
		if (!ft_strcmp(lst->key, str) && lst->check_aff == 0 && tmp[0])
		{
			s = 1;
			free (tmp);
			break ;
		}
		if (tmp)
			free (tmp);
		lst = lst->next;
	}
	if (checkis_one(line, 1, s) == 1)
		return (1);
	free_all(line);
	return (0);
}

int	export_check(char c, char *line, int i, int j)
{
	if (c == ' ')
	{
		while (line[j])
		{
			if (!ft_strncmp(&line[j], "export", 6))
			{
				j += 6;
				while (line[j] == ' ')
					j++;
				while (line[j] != '=' && line[j])
					j++;
				while (line[j])
				{
					if (j == i)
						return (1);
					if (line[j] == ' ')
						break ;
					j++;
				}
			}
			if (line[j])
				j++;
		}
	}
	return (0);
}

static int	place_key2_cun(char *line, t_list *lst, int j, char *line2)
{
	int	k;
	int	i;

	k = 0;
	i = j;
	while (lst->ex[k])
	{
		if (lst->ex[k] == '"' || lst->ex[k] == '\'' || lst->ex[k] == '$'
			|| export_check(lst->ex[k], line, i, 0))
			line2[j++] = lst->ex[k++] * -1;
		else
			line2[j++] = lst->ex[k++];
	}
	return (j);
}

char	*place_key2(char *line, char *str, t_list *lst, int i)
{
	int		s;
	int		j;
	int		k;
	char	*line2;

	j = 0;
	k = 0;
	s = 0;
	line2 = malloc(ft_strlen(line) - ft_strlen(str)
			+ ft_strlen(lst->ex));
	if (!line2)
		ft_mallocerr(NULL, lst, line, NULL);
	while (line[i])
	{
		if ((line[i] == '$') && s == 0)
		{
			j = place_key2_cun(line, lst, j, line2);
			i += ft_strlen(str) + 1;
			s = 1;
		}
		if (line[i])
			line2[j++] = line[i++];
	}
	return (line2[j] = '\0', free (line), line2);
}
