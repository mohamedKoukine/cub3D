/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amibguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:45:26 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 15:50:07 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

char	*ambi_str(char *line, t_list *lst)
{
	int		i;
	int		cp;
	char	*p;

	i = -1;
	cp = 0;
	while (line[++i])
	{
		if (!ft_isalnum(line[i]))
			break ;
		cp++;
	}
	p = malloc(cp + 1);
	if (!p)
		ft_exit(127, "minishell", "", lst);
	i = -1;
	while (line[++i])
	{
		if (!ft_isalnum(line[i]))
			break ;
		p[i] = line[i];
	}
	p[i] = '\0';
	return (p);
}

int	chek_ambi(char *line, t_list *lst)
{
	int		i;
	char	*p;
	char	*a;

	a = NULL;
	p = ambi_str(line, lst);
	while (lst)
	{
		if (!ft_strcmp(p, lst->key))
		{
			a = ft_strtrim(lst->ex, " ", 0);
			i = -1;
			while (a[++i])
			{
				if (a[i] == ' ')
					return (free(a), free(p), 1);
			}
		}
		lst = lst->next;
	}
	if (a)
		free(a);
	return (free(p), 0);
}

char	*ambiguous(char *line, t_list *lst)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strncmp(&line[i], ">", 1) || !ft_strncmp(&line[i], "<<", 2))
		{
			while (line[i] == '>' || line[i] == '<' || line[i] == ' ')
				i++;
			while (line[i] && line[i] != ' ')
			{
				if (line[i] == '$')
				{
					i++;
					if (chek_ambi(&line[i], lst))
						line[i - 1] = line[i - 1] * -1;
				}
				if (line[i])
					i++;
			}
		}
		if (line[i])
			i++;
	}
	return (magic_hide2(line, 0), line);
}

int	include_sq(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[j])
	{
		if (line[j] == '$')
			return (0);
		j++;
	}
	while (line[i] == ' ')
		i++;
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*handel_ambi(char *line, int i, int j)
{
	char	*line2;
	int		ls;

	ls = ft_strlen(line) + 17;
	line2 = malloc(ls);
	while (line[i])
	{
		if (!ft_strncmp(&line[i], ">", 1))
		{
			while (line[i] == '>' || line[i] == ' ')
			{
				if (line[i] == ' ' && include_sq(&line[i]))
					line2[j++] = ')';
				while (line[i] == ' ')
					line2[j++] = line[i++];
				line2[j++] = line[i++];
			}
		}
		if (line[i])
			line2[j++] = line[i++];
	}
	while (j < ls)
		line2[j++] = '\0';
	return (free(line), line2);
}