/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:41:32 by aelbouab          #+#    #+#             */
/*   Updated: 2024/09/16 15:50:35 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
	{
		i++;
	}
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
