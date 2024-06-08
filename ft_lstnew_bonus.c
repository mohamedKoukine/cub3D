/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:59:23 by aelbouab          #+#    #+#             */
/*   Updated: 2024/06/06 16:25:08 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_m_list	*ft_lstnew(char *content, char **com)
{
	t_m_list	*nede;

	if (!com)
		return (NULL);
	nede = malloc(sizeof(t_m_list));
	if (!nede)
		return (NULL);
	nede->command = content;
	nede->d_com = com;
	nede->first_comm = *com;
	nede->d_h = NULL;
	nede->file = NULL;
	nede->next = NULL;
	nede->dup_com = NULL;
	return (nede);
}
