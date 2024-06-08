/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:18:21 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/06/04 12:26:25 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	if (!src)
		return (ft_strdup(""));
	while (src[i])
		i++;
	dest = (char *)malloc(sizeof (char) * (i + 1));
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
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	i = 0;
	if (!s2 || !s1)
	return (-1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}