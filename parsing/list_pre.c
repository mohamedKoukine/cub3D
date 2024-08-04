/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:18:15 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 15:52:51 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

t_m_list	*split_all(char *line)
{
	char		**commands;
	t_m_list	*list;
	t_m_list	*new;
	int			i;

	i = 1;
	commands = ft_split(line, '|');
	list = ft_lstnew(commands[0], ft_split(commands[0], ' '));
	while (commands[i])
	{
		new = ft_lstnew(commands[i], ft_split(commands[i], ' '));
		ft_lstadd_back(&list, new);
		i++;
	}
	return (list);
}

t_m_list	*clear_lst(t_m_list *list)
{
	t_m_list	*tmp;
	int			i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i = 0;
		tmp->command = no_qutes(tmp->command, 1, 0, 0);
		while (tmp->d_com[i])
		{
			tmp->d_com[i] = no_qutes(tmp->d_com[i], 1, 0, 0);
			i++;
		}
		tmp = tmp->next;
	}
	return (list);
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
		tmp->first_comm = tmp->dup_com[0];
		tmp = tmp->next;
	}
	return (lst);
}

t_m_list	*list_to_exe(char *line)
{
	t_m_list	*list;

	list = split_all(line);
	free(line);
	list = clear_lst(list);
	list = en_s(list, 0);
	list = final_s(list);
	list = decript_stack(list);
	list->p[0] = dup(STDIN_FILENO);
	list->p[1] = dup(STDOUT_FILENO);
	return (list);
}
