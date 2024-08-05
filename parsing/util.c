/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:15:21 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 17:49:43 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

int	ft_isalnum(int i)
{
	if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')
		|| (i >= '0' && i <= '9') || i == '_')
		return (1);
	return (0);
}

int	checkit(char *red)
{
	if (!ft_strcmp(red, ">")
		|| !ft_strcmp(red, ">>")
		|| !ft_strcmp(red, "<")
		|| !ft_strcmp(red, "<<")
		|| !ft_strcmp(red, ">)")
		|| !ft_strcmp(red, ">>)")
		|| !ft_strcmp(red, "<<<"))
		return (0);
	return (1);
}

void	fill_key(t_list *d, char *env, int j)
{
	int	i;
	int	l;
	int	k;
	int	x;

	i = 0;
	l = 0;
	k = 0;
	x = 0;
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
}

static t_list	*key_lloc(char *env)
{
	t_list	*d;
	int		i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=' || env[i] == '+')
			break ;
		i++;
	}
	d = (t_list *)malloc(sizeof(t_list));
	if (!d)
		ft_exit(1, "minishell", "filed allocation", NULL);
	d->env = malloc (ft_strlen(env) + 1);
	d->key = malloc (i + 1);
	d->ex = malloc (ft_strlen(env) - i);
	if (!d->env || !d->key ||!d->ex)
		ft_exit(1, "minishell", "filed allocation", d);
	d->next = NULL;
	fill_key(d, env, i);
	return (d);
}

t_list	*ft_lstnew1(char *env, int i, char *p)
{
	t_list	*d;

	d = key_lloc(env);
	d->check_aff = 1;
	i = -1;
	while (env[++i])
		if (env[i] == '=')
			d->check_aff = 0;
	if ((d->env[0] == '_' && d->env[1] == '='))
		d->check_aff = 2;
	if (env == p)
		d->check_aff = 3;
	d->i = 0;
	return (d);
}
