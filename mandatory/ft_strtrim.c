/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:44:00 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/11/09 12:24:53 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_strd(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (set[0] == '\0')
		return (i);
	while (s1[i] && k == 0)
	{
		j = 0;
		while (set[j])
		{
			k = 1;
			if (s1[i] == set[j])
			{
				k = 0;
				break ;
			}
			j++;
		}
		if (k == 0)
			i++;
	}
	return (i);
}

static int	strm(char const *s1, char const *set)
{
	int		j;
	int		k;
	int		l;

	k = 0;
	l = ft_strlen(s1, 0) - 1;
	if (set[0] == '\0')
		return (l);
	while (s1[l] && k == 0)
	{
		j = 0;
		while (set[j])
		{
			k = 1;
			if (s1[l] == set[j])
			{
				k = 0;
				break ;
			}
			j++;
		}
		if (k == 0)
			l--;
	}
	return (l);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*d;
	int		i;
	int		k;
	int		l;

	if (!s1 || !set)
		return (NULL);
	i = ft_strd(s1, set);
	if (s1[0] == '\0' || (size_t)i == ft_strlen(s1, 0))
		return (free (s1), ft_strdup(""));
	l = strm(s1, set);
	k = 0;
	d = (char *)malloc(sizeof(char) * (l - i + 2));
	if (!d)
		return (NULL);
	while (i <= l)
	{
		d[k] = s1[i];
		k++;
		i++;
	}
	d[k] = '\0';
	free (s1);
	return (d);
}
