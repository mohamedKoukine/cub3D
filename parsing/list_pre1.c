/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pre1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:28:04 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/09 08:28:09 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

char	*no_qutes0(char *line, char *no_q)
{
	int		i;
	int		j;
	char	q;

	q = '\0';
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			q = line[i];
			i++;
			while (line[i] != q && line[i])
				no_q[j++] = line[i++];
			i++;
		}
		else if (line[i] && line[i] != q)
			no_q[j++] = line[i++];
	}
	no_q[j] = '\0';
	return (no_q);
}

char	*no_qutes(char *line, int fre, t_m_list *list, t_list *lst)
{
	char	*no_q;

	if (!line)
		return (NULL);
	no_q = malloc(ft_strlen(line) + 1);
	if (!no_q)
		ft_mallocerr(list, lst, NULL, NULL);
	no_q = no_qutes0(line, no_q);
	if (fre)
		free(line);
	return (no_q);
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

t_m_list	*decript_stack(t_m_list *list)
{
	t_m_list	*tmp;
	int			r;

	tmp = list;
	while (tmp)
	{
		garbag_find(tmp->command);
		r = -1;
		while (tmp->d_com && tmp->d_com[++r])
			garbag_find(tmp->d_com[r]);
		tmp = tmp->next;
	}
	return (list);
}
