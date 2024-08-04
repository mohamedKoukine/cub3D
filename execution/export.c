/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:41:12 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/04 15:35:19 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	add_plus_export(char *line, t_list *lst, t_list *lst1)
{
	char	*tmp;

	tmp = ft_strjoin(lst1->key, "=", 1);
	if (!tmp)
		ft_exit(127, "minishell", "filed allocation", lst);
	free(lst1->env);
	lst1->env = ft_strjoin(tmp, lst1->ex, 0);
	tmp = ft_substr(line, ft_posistion(line, '='), ft_strlen(line), 0);
	if (!tmp || !lst1->env)
		ft_exit(127, "minishell", "filed allocation", lst);
	lst1->env = ft_strjoin(lst1->env, tmp, 0);
	if (!lst1->env)
		ft_exit(127, "minishell", "filed allocation", lst);
	free(tmp);
	free(lst1->ex);
	lst1->ex = ft_substr(lst1->env, ft_posistion(lst1->env, '='),
			ft_strlen(line), 0);
	if (!lst1->ex)
		ft_exit(127, "minishell", "filed allocation", lst);
	lst1->check_aff = 0;
}

void	add_egual_export(char *line, t_list *lst, t_list *lst1)
{
	if (line[ft_strlen_exp(lst1->env, '=', 1)] == '=')
	{
		free(lst1->env);
		free(lst1->ex);
		lst1->env = ft_strdup(line);
		lst1->ex = ft_substr(line, ft_posistion(line, '='), ft_strlen(line), 0);
		if (!lst1->ex || !lst1->env)
			ft_exit(127, "minishell", "filed allocation", lst);
		lst1->check_aff = 0;
	}
}

void	ft_export_cont1(char *line, t_list *lst, t_list *lst1)
{
	while (lst1)
	{
		if (ft_strncmp(lst1->env, line, ft_strlen_exp(line, '+', 1)) == 0
			&& ((lst1->env[ft_strlen_exp(line, '+', 1)] == '=')
				|| (lst1->env[ft_strlen_exp(line, '+', 1)] == '\0'))
			&& (line[ft_strlen_exp(line, '+', 1)] == '+'))
		{
			add_plus_export (line, lst, lst1);
			break ;
		}
		if (ft_strncmp(lst1->env, line, ft_strlen_exp(lst1->env, '=', 1)) == 0
			&& (line[ft_strlen_exp(lst1->env, '=', 1)] == '='
				|| line[ft_strlen_exp(lst1->env, '=', 1)] == '\0'))
		{
			puts ("ana hna");
			add_egual_export(line, lst, lst1);
			break ;
		}
		lst1 = lst1->next;
	}
	if (!lst1)
	{
		lst1 = ft_lstnew1(line, 0, 0, NULL);
		ft_lstadd_back_env(&lst, lst1);
	}
}

void	ft_export_cont(char *line, t_list *lst, t_fd *fd)
{
	int		i;
	t_list	*lst1;

	lst1 = lst;
	i = -1;
	while (line[++i])
	{
		if (!(line[i] == '=' || ft_isalnum(line[i])
				|| (line[i] == '+' && line[i + 1] == '='))
			|| (line[0] <= '9' && line[0] >= '0'))
		{
			printf ("minishell: export: `%s': not a valid identifier\n",
				line);
			fd->ex_c = 1;
			break ;
		}
		if (line[i] == '=')
			break ;
	}
	if (line[i] == '=' || line[i] == '\0')
		ft_export_cont1(line, lst, lst1);
}

void	ft_export(char **line, t_list *lst, t_fd *fd)
{
	int	i;

	i = 1;
	if (ft_strcmp(line[0], "export") == 0 && !line[1])
		aff_export(lst);
	else
	{
		while (line[i])
		{
			ft_export_cont(line[i], lst, fd);
			i++;
		}
	}
}
