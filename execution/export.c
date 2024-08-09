/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:41:12 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/09 10:35:53 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	add_plus_export(char *line, t_list *lst1, t_m_list *list)
{
	char	*tmp;

	tmp = ft_strjoin(lst1->key, "=", 1);
	if (!tmp)
		ft_mallocerr (list, lst1, NULL, NULL);
	free(lst1->env);
	lst1->env = ft_strjoin(tmp, lst1->ex, 0);
	tmp = ft_substr(line, ft_posistion(line, '='), ft_strlen(line), 0);
	if (!tmp || !lst1->env)
		ft_mallocerr (list, lst1, NULL, NULL);
	lst1->env = ft_strjoin(lst1->env, tmp, 0);
	if (!lst1->env)
		ft_mallocerr (list, lst1, NULL, NULL);
	free(tmp);
	free(lst1->ex);
	lst1->ex = ft_substr(lst1->env, ft_posistion(lst1->env, '='),
			ft_strlen(lst1->env), 0);
	if (!lst1->ex)
		ft_mallocerr (list, lst1, NULL, NULL);
	lst1->check_aff = 0;
}

void	add_egual_export(char *line, t_list *lst1, t_m_list *list)
{
	if (line[ft_strlen_exp(lst1->env, '=', 1)] == '=')
	{
		free(lst1->env);
		free(lst1->ex);
		lst1->env = ft_strdup(line);
		lst1->ex = ft_substr(line, ft_posistion(line, '='), ft_strlen(line), 0);
		if (!lst1->ex || !lst1->env)
			ft_mallocerr (list, lst1, NULL, NULL);
		lst1->check_aff = 0;
	}
}

void	ft_export_cont1(char *line, t_list *lst, t_list *lst1, t_m_list *list)
{
	while (lst1)
	{
		if (ft_strncmp(lst1->env, line, ft_strlen_exp(line, '+', 1)) == 0
			&& ((lst1->env[ft_strlen_exp(line, '+', 1)] == '=')
				|| (lst1->env[ft_strlen_exp(line, '+', 1)] == '\0'))
			&& (line[ft_strlen_exp(line, '+', 1)] == '+'))
		{
			add_plus_export (line, lst1, list);
			break ;
		}
		if (ft_strncmp(lst1->env, line, ft_strlen_exp(lst1->env, '=', 1)) == 0
			&& (line[ft_strlen_exp(lst1->env, '=', 1)] == '='
				|| line[ft_strlen_exp(lst1->env, '=', 1)] == '\0'))
		{
			add_egual_export(line, lst1, list);
			break ;
		}
		lst1 = lst1->next;
	}
	if (!lst1)
	{
		lst1 = ft_lstnew1(line, 0, NULL);
		ft_lstadd_back_env(&lst, lst1);
	}
}

void	ft_export_cont(char *line, t_list *lst, t_fd *fd, t_m_list *list)
{
	fd->i = -1;
	if ((line[0] == '_' || (line[0] >= 'a' && line[0] <= 'z')
			|| (line[0] >= 'A' && line[0] <= 'Z')))
	{
		while (line[++fd->i])
		{
			if (!(line[fd->i] == '=' || ft_isalnum(line[fd->i])
					|| (line[fd->i] == '+' && line[fd->i + 1] == '=')))
			{
				printf ("minishell: export: '%s': not a valid identifier\n",
					line);
				fd->ex_c = 1;
				break ;
			}
			if (line[fd->i] == '=')
				break ;
		}
		if (line[fd->i] == '=' || line[fd->i] == '\0')
			ft_export_cont1(line, lst, lst, list);
	}
	else
	{
		printf ("minishell: export: '%s': not a valid identifier\n", line);
		fd->ex_c = 1;
	}
}

void	ft_export(char **line, t_list *lst, t_fd *fd, t_m_list *list)
{
	int	i;

	i = 1;
	if (ft_strcmp(line[0], "export") == 0 && !line[1])
		aff_export(lst);
	else
	{
		while (line[i])
		{
			ft_export_cont(line[i], lst, fd, list);
			i++;
		}
	}
}
