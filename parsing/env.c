/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:16:12 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/02 11:56:27 by mkaoukin         ###   ########.fr       */
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

t_list	*ft_lstnew1(char *env, int i, int k, char *p)
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
	if ((d->env[0] == '_' && d->env[1] == '='))
		d->check_aff  = 2;
	if (env == p)
		d->check_aff = 3;
	d->i = 0;
	return (d);
}

void ft_empty_env1(char *env, char *key, char *ex, int j)
{
	int		i;
	
	i = 0;
	while (key[i])
		env[j++] = key[i++];
	i = 0;
	while (ex[i])
		env[j++] = ex[i++];
	env[j] = '\0';
}

char	**ft_empty_env()
{
	char	buff[PATH_MAX];
	char	**env;

	getcwd(buff, PATH_MAX);
	env = malloc(sizeof(char *) * 6);
	if (!env)
		exit(0);
	env[0] = malloc (49);
	env[1] = malloc (ft_strlen(buff) + 5);
	env[2] = malloc (8);
	env[3] = malloc (ft_strlen(buff) + 3);
	env[4] = malloc (7);
	if (!env[0] || !env[1] || !env[2] || !env[3] || !env[4])
		exit(0);
	ft_empty_env1(env[0], "PATH=", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0);
	ft_empty_env1(env[1], "PWD=", buff, 0);
	ft_empty_env1(env[2], "SHLVL=", "0", 0);
	ft_empty_env1(env[3], "_=", buff, 0);
	ft_empty_env1(env[4], "OLD", "PWD", 0);
	env[5] = NULL;
	return (env);
}

void	check_shlvl(t_list *lst1)
{
	char	*tmp;
	int		i;

	if (!ft_strncmp("SHLVL",lst1->env,5))
		{
			i = ft_atoi(&lst1->env[6]);
			if (i >= 1000)
				i = 0;
			else if (i < 0)
				i = -1;
			if (i == 999)
				tmp = ft_strdup("");
			else
				tmp = ft_itoa(++i);
			lst1->env = ft_strjoin(ft_substr(lst1->env, 0, 6, 1)
				, tmp, 0);
			free (tmp);
		}
}

void	ft_env(char **env, t_list **lst, int j, char *p)
{
	t_list	*lst1;

	if (!(*env))
	{
		env = ft_empty_env();
		p = *env;
	}
	*lst = ft_lstnew1(env[j++], 0, 0, p);
	while (env[j])
	{
		lst1 = ft_lstnew1(env[j++], 0, 0, NULL);
		check_shlvl(lst1);
		if (!ft_strncmp("OLDPWD",lst1->env,6))
		{
			free (lst1->env);
			free (lst1->ex);
			lst1->ex = NULL;
			lst1->env = ft_strjoin(lst1->key, NULL, 1);
			lst1->check_aff = 1;
		}
		ft_lstadd_back_env(lst, lst1);
	}
	if (j == 5)
		free_all (env);
}

void	aff_env(char **line, t_list *lst, t_fd *fd)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (ft_strcmp(line[i], "env"))
		{
			printf ("%s: %s: No such file or directory\n", line[0], line[i]);
			fd->ex_c = 1;
			return ;
		}
	}
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->check_aff != 1 && lst->check_aff != 3)
			printf ("%s\n", lst->env);
		lst = lst->next;
	}
}
