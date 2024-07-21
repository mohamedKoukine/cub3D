/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:16:12 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/20 16:32:37 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

static int	key_lloc(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=' || env[i] == '+')
			break ;
		i++;
	}
	return (i);
}

t_list	*ft_lstnew1(char *env, int i, int k)
{
	t_list	*d;
	int		j;
	int l=0;
	int x=0;
	j = key_lloc(env);
	d = (t_list *)malloc(sizeof(t_list));
	d->env = malloc (ft_strlen(env) + 1);
	d->key = malloc (j + 1);
	d->ex = malloc (ft_strlen(env) - j);
	if (!d || !d->env || !d->key ||!d->ex)
		return (0);
	d->next = NULL;
	while ((size_t)i < ft_strlen(env))
	{
		if (env[i] == '+' && x == 0)
			x = 1;
		else
			d->env[l++] = env[i];
			
		if (i < j)
			d->key[i] = env[i];
		else if (i > j)
			d->ex[k++] = env[i];
		if (i + 1 == j)
			d->key[i + 1] = '\0';
		i++;
	}
	d->env[l] = '\0';
	d->ex[k] = '\0';
	d->check_aff = 1;
	i = -1;
	while (env[++i])
	{
		if (env[i] == '=')
			d->check_aff = 0;
	}
	d->i = 0;
	return (d);
}

void	ft_env(char **env, t_list **lst)
{
	int		j;
	t_list	*lst1;

	j = 0;
	*lst = ft_lstnew1(env[j++], 0, 0);
	while (env[j])
	{
		lst1 = ft_lstnew1(env[j], 0, 0);
		if (!ft_strncmp("SHLVL",lst1->env,5))
			lst1->env = ft_strjoin(ft_substr(lst1->env, 0, 6, 0)
				, ft_itoa(ft_atoi(&lst1->env[6]) + 1), 0);
		ft_lstadd_back_env(lst, lst1);
		j++;
	}
}

void	aff_env(t_list *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->check_aff == 0)
			printf ("%s\n", lst->env);
		lst = lst->next;
	}
}
