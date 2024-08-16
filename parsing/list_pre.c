/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:18:15 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/16 16:09:00 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

t_m_list	*split_all(char *line, t_list *lst, int i)
{
	char		**commands;
	t_m_list	*list;
	t_m_list	*new;

	commands = ft_split(line, '|');
	if (!commands)
		ft_mallocerr(NULL, lst, NULL, NULL);
	list = ft_lstnew(commands[0], ft_split(commands[0], ' '));
	if (!list)
	{
		free (commands);
		ft_mallocerr(NULL, lst, NULL, NULL);
	}
	while (commands[++i])
	{
		new = ft_lstnew(commands[i], ft_split(commands[i], ' '));
		if (!new)
		{
			free(commands);
			ft_mallocerr(list, lst, NULL, NULL);
		}
		ft_lstadd_back(&list, new);
	}
	free (commands);
	return (list);
}

t_m_list	*clear_lst(t_m_list *list, t_list *lst)
{
	t_m_list	*tmp;
	int			i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i = 0;
		tmp->command = no_qutes(tmp->command, 1, list, lst);
		while (tmp->d_com[i])
		{
			tmp->d_com[i] = no_qutes(tmp->d_com[i], 1, list, lst);
			i++;
		}
		tmp = tmp->next;
	}
	return (list);
}

t_m_list	*en_s(t_m_list *lst, int cp, t_list *list)
{
	t_m_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		cp = cp_hd(tmp->command);
		tmp->d_h = malloc(sizeof(char *) * (cp + 1));
		if (!tmp->d_h)
			ft_mallocerr(lst, list, NULL, NULL);
		tmp->file = malloc(sizeof(char *) * (cp + 1));
		if (!tmp->file)
			ft_mallocerr(lst, list, NULL, NULL);
		fill_dfile(tmp);
		tmp = tmp->next;
	}
	return (lst);
}

t_m_list	*final_s(t_m_list *lst, t_list *list)
{
	t_m_list	*tmp;
	int			cp;

	tmp = lst;
	while (tmp)
	{
		cp = cp_conter(tmp, 0);
		tmp->dup_com = malloc(sizeof(char *) * (cp + 1));
		if (!tmp->dup_com)
			ft_mallocerr(lst, list, NULL, NULL);
		final_ss(tmp, 0, 0, 0);
		tmp->first_comm = tmp->dup_com[0];
		tmp = tmp->next;
	}
	return (lst);
}

t_m_list	*list_to_exe(t_list *lst, char *line)
{
	t_m_list	*list;

	list = split_all(line, lst, 0);
	free(line);
	line = NULL;
	list = telda_to_home(list, lst, NULL);
	list = clear_lst(list, lst);
	list = en_s(list, 0, lst);
	list = final_s(list, lst);
	list = decript_stack(list);
	list->p[0] = dup(STDIN_FILENO);
	list->p[1] = dup(STDOUT_FILENO);
	return (list);
}
