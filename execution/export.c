/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:41:12 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/07/08 13:47:55 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

// t_list	*ft_lstnew_exp(char *env)
// {
// 	t_list	*d;
// 	int		i;

// 	i = -1;
// 	d = (t_list *)malloc(sizeof(t_list));
// 	d->env = malloc (ft_strlen(env) + 1);
// 	if (!d || !d->env)
// 		return (0);
// 	// while (env[++i])
// 	// 	d->env[i] = env[i];
// 	// d->env[i] = '\0';
// 	// i = -1;
// 	d->check_aff = 1;
// 	while (env[++i])
// 	{
// 		if (env[i] == '=')
// 			d->check_aff = 0;
// 	}
// 	d->i = 0;
// 	d->next = NULL;
// 	return (d);
// }

void	print_ex(t_list *lst, t_list *lst2, int i)
{
	while (lst->next)
	{
		if (ft_strcmp(lst2->env, lst->next->env) > 0
			&& lst2->i == 0 && lst->next->i == 0)
			lst2 = lst->next;
		lst = lst->next;
	}
	if (lst2->i == 0)
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
		lst2->i = 1;
	}
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
			print_ex(lst, lst2, 0);
		else
			lst2 = lst2->next;
	}
	while (lst3)
	{
		lst3->i = 0;
		lst3 = lst3->next;
	}
}

size_t	ft_strlen_exp(const char *str, int flag)
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
		while (str[i] && str[i] != '=')
			i++;
	}
	return (i);
}
int	ft_posistion(char *line)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

void	ft_export_cont1(char *line, t_list *lst, t_list *lst1, int i)
{
	while (lst1)
	{
		if (ft_strncmp(lst1->env, line, ft_strlen_exp(lst1->env, 1)) == 0
			&& (line[ft_strlen_exp(lst1->env, 1)] == '='
				|| line[ft_strlen_exp(lst1->env, 1)] == '\0'))
		{
			if (line[ft_strlen_exp(lst1->env, 1)] == '=')
			{
				free(lst1->env);
				free(lst1->ex);
				lst1->env = ft_strdup(line);
				lst1->ex = ft_substr(line,ft_posistion(line), ft_strlen(line));
				lst1->check_aff = 0;
			}
			i = -1;
			break ;
		}
		lst1 = lst1->next;
	}
	if (i > -1)
	{
		lst1 = ft_lstnew1(line, 0, 0);
		ft_lstadd_back_env(&lst, lst1);
	}
}

void	ft_export_cont(char *line, t_list *lst)
{
	int		i;
	t_list	*lst1;

	lst1 = lst;
	i = -1;
	if ((line[0] == '_' || (line[0] >= 'a' && line[0] <= 'z')
			|| (line[0] >= 'A' && line[0] <= 'Z')))
	{
		while (line[++i])
		{
			if (!(line[i] == '=' || line[i] == '_'
					|| (line[i] >= 'a' && line[i] <= 'z')
					|| (line[i] >= 'A' && line[i] <= 'Z')
					|| (line[i] >= '0' && line[i] <= '9')))
			{
				printf ("minishell: export: '%s': not a valid identifier\n",
					line);
				break ;
			}
		}
		if (line[i] == '\0' )
			ft_export_cont1(line, lst, lst1, i);
	}
	else
		printf ("minishell: export: '%s': not a valid identifier\n", line);
}

void	ft_export(char **line, t_list *lst)
{
	int	i;

	i = 1;
	if (ft_strcmp(line[0], "export") == 0 && !line[1])
		aff_export(lst);
	else
	{
		while (line[i])
		{
			ft_export_cont(line[i], lst);
			i++;
		}
	}
}
