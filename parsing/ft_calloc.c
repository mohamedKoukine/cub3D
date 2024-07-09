/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:42:07 by aelbouab          #+#    #+#             */
/*   Updated: 2024/06/10 14:56:33 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pr_minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*i;

	if ((int)count < 0 && (int)size < 0)
		return (NULL);
	if (count * size > SIZE_MAX)
		return (NULL);
	i = malloc(count * size);
	if (!i)
		return (NULL);
	ft_bzero(i, count * size);
	return (i);
}
