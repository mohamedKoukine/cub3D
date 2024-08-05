/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd0.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:50:52 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/05 10:28:42 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

char	*get_home(t_list *lst)
{
	while (lst)
	{
		if (!ft_strncmp(lst->env, "HOME=", 5))
			return (lst->ex);
		lst = lst->next;
	}
	return (NULL);
}

char	*is_pwd(t_list *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, "PWD"))
			return (lst->ex);
		lst = lst->next;
	}
	return (NULL);
}

char	*oldisgold(t_list *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, "OLDPWD"))
			return (lst->ex);
		lst = lst->next;
	}
	return (NULL);
}

void	freethis(char *env, char *ex)
{
	free(env);
	if (ex)
		free(ex);
}
