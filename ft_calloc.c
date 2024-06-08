/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:42:07 by aelbouab          #+#    #+#             */
/*   Updated: 2024/05/10 11:29:09 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
