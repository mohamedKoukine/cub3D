/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:36:51 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/06/08 14:06:19 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd()
{
	char	*pwd;
	char	buff[PATH_MAX];

	pwd = getcwd(buff, PATH_MAX);
	printf("%s\n", pwd);
}