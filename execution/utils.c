/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:09:11 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/07/28 12:16:21 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

size_t	ft_strlen1(const char *str, int flag)
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
		while (str[i] && str[i] != '\n')
			i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, int l)
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
	d = malloc(sizeof(char) * (ft_strlen1(s1, 0) + ft_strlen1(s2, 0) + 1));
	if (!d)
		return (NULL);
	j = 0;
	while (s1[i])
		d[i++] = s1[j++];
	j = 0;
	while (s2[j])
		d[i++] = s2[j++];
	d[i] = '\0';
	if (l == 0)
		free(s1);
	return (d);
}

char	*ft_substr(char *s, unsigned int start, size_t len, int fre)
{
	char			*d;
	unsigned int	l;
	unsigned int	i;

	l = len;
	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen1(s, 0) || l == 0)
		return (ft_strdup(""));
	if (start + l > ft_strlen1(s, 0))
	{
		l = ft_strlen1(s, 0) - start;
	}
	d = (char *)malloc(sizeof(char) * l + 1);
	if (!d)
		return (0);
	while (s[start] && i < l)
	{
		d[i] = s[start];
		i++;
		start++;
	}
	d[i] = '\0';
	if (fre == 1)
		free (s);
	return (d);
}