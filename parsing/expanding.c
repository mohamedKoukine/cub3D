/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:15:23 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 16:26:36 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

static char	*place_key3(char *line, char *str)
{
	int		i;
	int		j;
	int		s;
	char	*line2;

	i = 0;
	j = 0;
	s = 0;
	line2 = malloc(ft_strlen(line) - ft_strlen(str));
	if (!line2)
		return (NULL);
	while ((size_t)i < ft_strlen(line))
	{
		if (line[i] == '$' && !ft_strncmp(&line[i + 1], str, ft_strlen(str))
			&& s == 0)
		{
			i += ft_strlen(str) + 1;
			s = 1;
		}
		if (line[i])
			line2[j++] = line[i++];
	}
	line2[j] = '\0';
	free (line);
	return (line2);
}

static char	*place_key1(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			line[i] = line[i] * -1;
			break ;
		}
		i++;
	}
	return (line);
}

static char	*place_key(char *line, char *str, t_list *lst)
{
	if (!str || !str[0] || here_expand(ft_split(line, ' '), str, lst))
	{
		line = place_key1(line);
		return (line);
	}
	while (lst)
	{
		if (!ft_strcmp(str, lst->key) && lst->ex && lst->ex[0])
		{
			line = place_key2(line, str, lst, 0);
			return (line);
		}
		lst = lst->next;
	}
	line = place_key3(line, str);
	return (line);
}

static char	*expanding1(char *line, int i, int k, int j)
{
	char	*str;

	if (line[k] >= '0' && line[k] <= '9')
	{
		str = malloc(2);
		if (!str)
			return (NULL);
		str[0] = line[k];
		str[1] = '\0';
		return (str);
	}
	while (line[k] && line[k] != ' ' && ft_isalnum(line[k]))
	{
		j++;
		k++;
	}
	str = malloc(j + 1);
	if (!str)
		return (NULL);
	j = i;
	k = 0;
	while (line[j] && line[j] != ' ' && ft_isalnum(line[j]))
		str[k++] = line[j++];
	return (str[k] = '\0', str);
}

char	*expanding(char *line, t_list *lst)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	str = NULL;
	if (!line)
		return (NULL);
	while (line[i])
	{
		line = here_dollar(line, lst, 0);
		line = dollar(line, 0, 0, NULL);
		if (line[i] == '$')
		{
			k = ++i;
			str = expanding1(line, i, k, 0);
			line = place_key(line, str, lst);
			free(str);
			i = 0;
		}
		else if (line[i])
			i++;
	}
	return (line = duh(line, -1, 0), line);
}