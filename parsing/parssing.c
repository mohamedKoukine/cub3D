/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:57:00 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/31 15:17:06 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

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
	free(line);
	return (line2);
}

char	*place_key1(char *line)
{
	int		i;

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

int	export_check(char c,char *line, int i)
{
	int j = 0;
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
		return (NULL);
	while (line[i])
	{
		if ((line[i] == '$') && s == 0)
		{
			while (lst->ex[k])
			{
				if (lst->ex[k] == '"' || lst->ex[k] == '\'' || lst->ex[k] == '$' || export_check(lst->ex[k],line, i))
					line2[j++] = lst->ex[k++] * -1;
				else
					line2[j++] = lst->ex[k++];
			}
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

char	*place_key3(char *line, char *str)
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
		if (line[i] == '$' && !ft_strncmp(&line[i + 1], str, ft_strlen(str)) && s == 0)
		{
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
	free (line);
	return (line2);
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

int	here_expand(char **line, char *str, t_list *lst)
{
	int	i;
	int	s;
	char	*tmp;
	i = 0;
	s = 0;
	while (line[i])
	{
		if (!ft_strcmp(line[i], "<<")
			&& strchr_char(line[i + 1], '$'))
			return (1);
		i++;
	}
	i = 0;
	while (lst)
	{
		tmp = ft_strtrim(lst->ex, " ", 0);
		if (!ft_strcmp(lst->key, str) && lst->check_aff == 0 && tmp[0])
		{
			s = 1;
			free (tmp);
			break ;
		}
		free (tmp);
		lst = lst->next;
	}
	while (line[i])
	{
		if ((!ft_strncmp(line[i], ">", 1) || !ft_strncmp(line[i], "<", 1))
				&& !ft_strncmp(line[i + 1], "$", 1) && s == 0)
			return (1);
		i++;
	}
	i = 0;
	while (line[i])
		free(line[i++]);
	free (line);
	return (0);
}

char	*place_key(char *line, char *str, t_list *lst)
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

char	*expanding1(char *line, int i, int k)
{
	int		j;
	char	*str;

	j = 0;
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
	str[k] = '\0';
	return (str);
}

int    exit_key(char *line)
{
	int i;
	int cp;

	i = 0;
	cp = 0;
	while(line[i])
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

char    *exit_code(char *line, char *code)
{
	char    *line2;
	int        i;
	int        j;
	int        k;
	int        cp;

	i = 0;
	k = 0;
	if (!line)
		return (0);
	cp = exit_key(line);
	line2 = malloc (ft_strlen(line) - (cp * 2) + (cp * ft_strlen(code)) + 1);
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "$?", 2))
		{
			j = 0;
			while (code[j])
			{
				line2[k] = code[j];
				k++;
				j++;
			}
			i = i + 2;
		}
		else if (line[i])
			line2[k++] = line[i++];
	}
	line2[k] = '\0';
	free (line);
	return (line2);
}

int    d_cp(char *line, int j)
{
    int    cp;

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

char	*ddhere(char *line)
{
	char	*line2;
	int		i = 0;
	int		j = 0;
	int		cp;
	int		s = 0;
	
	line2 = malloc(ft_strlen(line) + 1);
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "<<", 2))
		{
			while (line[i] == '<' || line[i] == ' ')
				line2[j++] = line[i++];
			if (line[i] == '$')
			{
				cp = 0;
				while (line[i] == '$')
				{
					i++;
					cp++;
				}
				if (cp % 2 != 0 && if_its_q(line[i]))
				{
					s = 1;
					while (s < cp)
					{
						line2[j++] = '$';
						s++;
					}
				}
				if ((cp % 2 == 0 && if_its_q(line[i])) || !if_its_q(line[i]))
				{
					s = 0;
					while (s < cp)
					{
						line2[j++] = '$';
						s++;
					}
				}
			}
		}
		if (line[i])
			line2[j++] = line[i++];
	}
	line2[j] = '\0';
	free(line);
	return (line2);
}

char    *here_dollar(char *line)
	{
	int		i;
	int		cp;
	char	*hold;

	i = 0;
	line = ddhere(line);
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			hold = &line[i];
			while (line[i] == '<' || line[i] == '>' || line[i] == ' ')
				i++;
			cp = d_cp(line, i);
			int j = i;
			while (line[i] == '$' || line[i] == '"' || line[i] == '\'')
			{
				if (line[i] == '"' || line[i] == '\'')
				{
					i++;
					continue ;
				}
				if (line[i] == '$' && !ft_strncmp(hold, "<<", 2))
					line[i] = line[i] * (-1);
				i++;
			}
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
		if (line[i])
			i++;
	}
	return (line);
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
		line = here_dollar(line);
		line = dollar(line, 0, 0, NULL);
		if (line[i] == '$')
		{
			k = ++i;
			str = expanding1(line, i, k);
			line = place_key(line, str, lst);
			free(str);
			i = 0;
		}
		else if (line[i])
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

void	final_ss(t_m_list *tmp, int i, int j, int cp)
{
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
	int			cp;

	tmp = lst;
	while (tmp)
	{
		cp = cp_conter(tmp, 0);
		tmp->dup_com = malloc(sizeof(char *) * (cp + 1));
		if (!tmp->dup_com)
			return (NULL);
		final_ss(tmp, 0, 0, 0);
		// if (!ft_strcmp(tmp->first_comm, tmp->d_h[0]))/////////////// 3andak am3alm
		tmp->first_comm = tmp->dup_com[0];
		tmp = tmp->next;
	}
	return (lst);
}
