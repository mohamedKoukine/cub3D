/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:16:12 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/08 12:30:17 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"
#include "../execution/ex_minishell.h"

void	ft_empty_env1(char *env, char *key, char *ex, int j)
{
	int	i;

	i = 0;
	while (key[i])
		env[j++] = key[i++];
	i = 0;
	while (ex[i])
		env[j++] = ex[i++];
	env[j] = '\0';
}

char	**ft_empty_env(void)
{
	char	buff[PATH_MAX];
	char	**env;

	getcwd(buff, PATH_MAX);
	env = malloc(sizeof(char *) * 6);
	if (!env)
		ft_mallocerr(NULL, NULL, NULL, NULL);
	env[0] = malloc (49);
	env[1] = malloc (ft_strlen(buff) + 5);
	env[2] = malloc (8);
	env[3] = malloc (ft_strlen(buff) + 3);
	env[4] = malloc (7);
	if (!env[0] || !env[1] || !env[2] || !env[3] || !env[4])
		ft_mallocerr(NULL, NULL, NULL, env);
	ft_empty_env1(env[0], "PATH=",
		"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0);
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

	if (!ft_strncmp("SHLVL", lst1->env, 5))
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
		lst1->env = ft_strjoin(ft_substr(lst1->env, 0, 6, 1),
				tmp, 0);
		if (!lst1->env || !tmp)
			ft_mallocerr(NULL, lst1, tmp, NULL);
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
	*lst = ft_lstnew1(env[j++], 0, p);
	while (env[j])
	{
		lst1 = ft_lstnew1(env[j++], 0, NULL);
		check_shlvl(lst1);
		if (!ft_strncmp("OLDPWD", lst1->env, 6))
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
