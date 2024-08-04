/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:15:21 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 14:31:43 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

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
