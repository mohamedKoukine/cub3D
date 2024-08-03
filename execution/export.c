/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:41:12 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/02 11:43:56 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	print_export(t_list *lst, t_list *lst2, int i)
{
	while (lst->next)
	{
		if (ft_strcmp(lst2->env, lst->next->env) > 0
			&& lst2->i == 0 && lst->next->i == 0)
			lst2 = lst->next;
		lst = lst->next;
	}
	if (lst2->i == 0 && lst2->check_aff != 2 && lst2->check_aff != 3)
	{
		i = -1;
		write(1, "declare -x ", 11);
		while (lst2->env[++i])
		{
			write(1, &lst2->env[i], 1);
			if (lst2->env[i] == '=' && lst2->i == 0)
			{
				write(1, "\"", 1);
				lst2->i = 1;
			}
		}
		if (lst2->i == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
		lst2->i = 1;

}

void	aff_export(t_list *lst)
{
	t_list	*lst2;
	t_list	*lst3;

	lst2 = lst;
	lst3 = lst;
	while (lst2)
	{
		if (lst2->i == 0) 
			print_export(lst, lst2, 0);
		else
			lst2 = lst2->next;
	}
	while (lst3)
	{
		lst3->i = 0;
		lst3 = lst3->next;
	}
}

size_t	ft_strlen_exp(const char *str, char c, int flag)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (flag == 0)
	{
		while (str[i])
			i++;
	}
	else
	{
		while (str[i] && str[i] != c)
			i++;
	}
	return (i);
}
int	ft_posistion(char *line, char c)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			return (i + 1);
		i++;
	}
	return (i);
}

void	ft_export_cont1(char *line, t_list *lst, t_list *lst1, int i)
{
	char *tmp;
	while (lst1)
	{
		
		if (ft_strncmp(lst1->env, line, ft_strlen_exp(line, '+', 1)) == 0
			&& ((lst1->env[ft_strlen_exp(line, '+', 1)] == '=')
			|| (lst1->env[ft_strlen_exp(line, '+', 1)] == '\0'))
			&& (line[ft_strlen_exp(line, '+', 1)] == '+'))
		{
			tmp = ft_strjoin(lst1->key, "=", 1);
			free(lst1->env);
			lst1->env = ft_strjoin(tmp, lst1->ex, 0);
			tmp = ft_substr(line, ft_posistion(line, '='), ft_strlen(line), 0);
			lst1->env = ft_strjoin(lst1->env, tmp, 0);
			free(tmp);
			free(lst1->ex);
			lst1->ex = ft_substr(lst1->env, ft_posistion(lst1->env, '='), ft_strlen(line), 0);
			lst1->check_aff = 0;
			i = -1;
				break ;
		}
		if (ft_strncmp(lst1->env, line, ft_strlen_exp(lst1->env, '=', 1)) == 0
			&& (line[ft_strlen_exp(lst1->env, '=', 1)] == '='
				|| line[ft_strlen_exp(lst1->env, '=', 1)] == '\0'))
		{
			if (line[ft_strlen_exp(lst1->env, '=', 1)] == '=')
			{
				free(lst1->env);
				free(lst1->ex);
				lst1->env = ft_strdup(line);
				lst1->ex = ft_substr(line,ft_posistion(line, '='), ft_strlen(line), 0);
				lst1->check_aff = 0;
			}
			i = -1;
			break ;
		}
		lst1 = lst1->next;
	}
	if (i > -1)
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
			printf ("minishell: export: '%s': not a valid identifier\n",
				line);
			fd->ex_c = 1;
			break ;
		}
		if (line[i] == '=')
			break ;
	}
	if (line[i] == '=' || line[i] == '\0')
		ft_export_cont1(line, lst, lst1, i);
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
