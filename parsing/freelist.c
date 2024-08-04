/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:55:33 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 15:56:16 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

void	free_env(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		free (lst->env);
		if (lst->ex)
			free (lst->ex);
		free (lst->key);
		lst = lst->next;
		free (tmp);
	}
}

void	free_list(t_m_list *list)
{
	int			i;
	t_m_list	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		i = 0;
		while (list->d_com[i])
			free(list->d_com[i++]);
		free (list->d_com);
		free (list->command);
		if (list->dup_com)
			free(list->dup_com);
		if (list->d_h)
			free(list->d_h);
		if (list->file)
			free(list->file);
		list = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}
