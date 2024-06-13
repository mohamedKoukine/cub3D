/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:57:00 by aelbouab          #+#    #+#             */
/*   Updated: 2024/06/10 14:12:38 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_space(char *line)
{
	int		i;
	int		j;
	int		ls;
	char	*line2;

	i = 0;
	j = 0;
	ls = ft_strlen(line);
	line2 = ft_calloc(ls, 3);
	if (!line2)
		return (NULL);
	while (i < ls)
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
		i++;
	}
	line2[j] = '\0';
	return (line2);
}

char	*place_key1(char *line)
{
	int		i;
	int		s;
	char	*line2;

	s = 0;
	i = 0;
	line2 = malloc(ft_strlen(line) + 1);
	while (line[i])
	{
		if (line[i] == '$' && s == 0)
		{
			line2[i] = line[i] * -1;
			s = 1;
		}
		else
			line2[i] = line[i];
		i++;
	}
	line2[i] = '\0';
	return (line2);
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
	while (line[i])
	{
		if ((line[i] == '$') && s == 0)
		{
			while (lst->ex[k])
				line2[j++] = lst->ex[k++];
			i += ft_strlen(str) + 1;
			s = 1;
		}
		line2[j] = line[i];
		if (line[i])
		{
			i++;
			j++;
		}
	}
	line2[j] = '\0';
	return (line2);
}

char	*place_key3(char *line, char *str)
{
	int		i;
	int		j;
	char	*line2;

	i = 0;
	j = 0;
	line2 = malloc(ft_strlen(line) - ft_strlen(str));
	while ((size_t)i < ft_strlen(line))
	{
		if (line[i] == '$' && !ft_strncmp(&line[i + 1], str, ft_strlen(str)))
			i += ft_strlen(str) + 1;
		line2[j] = line[i];
		if (line[i])
		{
			i++;
			j++;
		}
	}
	line2[j] = '\0';
	return (line2);
}

char	*place_key(char *line, char *str, t_list *lst)
{
	char	*line2;

	if (!str || !str[0])
	{
		line2 = place_key1(line);
		return (line2);
	}
	while (lst)
	{
		if (!ft_strcmp(str, lst->key))
		{
			line2 = place_key2(line, str, lst, 0);
			return (line2);
		}
		lst = lst->next;
	}
	line2 = place_key3(line, str);
	return (line2);
}

char	*expanding1(char *line, int i, int k)
{
	int		j;
	char	*str;

	j = 0;
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
	str[k] = '\0';
	return (str);
}

char	*expanding(char *line, t_list *lst)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	str = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			k = ++i;
			str = expanding1(line, i, k);
			line = place_key(line, str, lst);
			free(str);
			i = 0;
		}
		if (line[i])
			i++;
	}
	line = duh(line, -1, 0);
	return (line);
}

void	fill_dfile(t_m_list *tmp)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (tmp->d_com[i])
	{
		if (!checkit(tmp->d_com[i]))
		{
			tmp->d_h[j] = tmp->d_com[i];
			tmp->file[j] = tmp->d_com[i + 1];
			j++;
		}
		i++;
	}
	tmp->d_h[j] = NULL;
	tmp->file[j] = NULL;
}

t_m_list	*en_s(t_m_list *lst, int cp)
{
	t_m_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		cp = cp_hd(tmp->command);
		tmp->d_h = malloc(sizeof(char *) * (cp + 1));
		tmp->file = malloc(sizeof(char *) * (cp + 1));
		if (!tmp->d_h || !tmp->file)
			return (NULL);
		fill_dfile(tmp);
		tmp = tmp->next;
	}
	return (lst);
}

int	cp_conter(t_m_list *tmp, int cp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp->d_com[i])
	{
		j = 0;
		while (tmp->d_h[j])
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

void	final_ss(t_m_list *tmp, int i, int j, int cp)
{
	while (tmp->d_com[i])
	{
		j = 0;
		while (tmp->d_h[j])
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
		tmp->dup_com[cp] = tmp->d_com[i];
		if (tmp->d_com[i])
		{
			cp++;
			i++;
		}
	}
		tmp->dup_com[cp] = NULL;
}

t_m_list	*final_s(t_m_list *lst)
{
	t_m_list	*tmp;
	int			i;
	int			cp;

	tmp = lst;
	while (tmp)
	{
		cp = cp_conter(tmp, 0);
		tmp->dup_com = malloc(sizeof(char *) * (cp + 1));
		if (!tmp->dup_com)
			return (NULL);
		i = 0;
		cp = 0;
		final_ss(tmp, i, 0, cp);
		if (!ft_strcmp(tmp->first_comm, tmp->d_h[0]))
			tmp->first_comm = tmp->dup_com[0];
		tmp = tmp->next;
	}
	return (lst);
}
