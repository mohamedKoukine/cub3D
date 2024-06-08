/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:26:26 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/05/14 16:28:44 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew1(char *env)
{
	t_list	*d;
	int		i;
	
	i = 0;
	d = (t_list *)malloc(sizeof(t_list));
	if (!d)
		return (0);
	d->env = malloc (ft_strlen(env, 0) + 1);
	d->next = NULL;
	while (env[i])
	{
		d->env[i] = env[i];
		i++;
	}
	d->env[i] = '\0';
	return (d);
}

void ft_env(char **env, t_list **lst)
{
	int		j;
	t_list *lst1;

	j = 0;
	while (env[j])
	{
		lst1 = ft_lstnew1(env[j]);
		ft_lstadd_back(lst,lst1);
		j++;
	}
}
void aff_env(t_list *lst)
{
	while (lst)
	{
		printf ("%s\n",lst->env);
		lst = lst->next;
	}
}
