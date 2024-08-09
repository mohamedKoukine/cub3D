/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:36:51 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/06 12:32:26 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	ft_pwd(void)
{
	char	buff[PATH_MAX];

	ft_bzero(buff, PATH_MAX);
	getcwd(buff, PATH_MAX);
	printf("%s\n", buff);
}
