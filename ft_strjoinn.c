/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:17:09 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/05/14 16:28:15 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinn(char *s1, char *s2)
{
	char	*d;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	while (s2[i] && s2[i] != ' ')
		i++;
	d = malloc(sizeof(char) * (ft_strlen(s1, 0) + i + 1));
	if (!d)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
		d[i++] = s1[j++];
	j = 0;
	while (s2[j] && s2[j] != ' ')
		d[i++] = s2[j++];
	d[i] = '\0';
	free(s1);
	return (d);
}
