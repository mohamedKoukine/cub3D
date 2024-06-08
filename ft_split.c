/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:50:02 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/05/14 15:59:35 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cw(char const *s, char c)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			j++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i])
			i++;
	}
	return (j);
}

static char	**ft_free(int index, char **s)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	**ft_scpy(char const *s, char **d, char c)
{
	int	j;
	int	l;
	int	i;

	j = 0;
	i = 0;
	while (s[i])
	{
		l = 0;
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				d[j][l++] = s[i++];
			d[j][l] = '\0';
			j++;
		}
		if (s[i])
			i++;
	}
	return (d);
}

static char	**ft_spa(char const *s, char **d, char c, int i)
{
	int	j;
	int	p;

	j = 0;
	while (s[i])
	{
		p = 0;
		while (s[i] && s[i] != c)
		{
			p++;
			i++;
		}
		if (p != 0)
		{
			d[j] = (char *)malloc(sizeof(char) * (p + 1));
			if (!d[j])
				return (ft_free(j, d));
			j++;
		}
		if (s[i])
			i++;
	}
	d[j] = NULL;
	return (d);
}

char	**ft_split(char const *s, char c)
{
	char	**d;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	d = (char **)malloc(sizeof(char *) * (ft_cw(s, c) + 1));
	if (!d)
		return (NULL);
	d = ft_spa(s, d, c, 0);
	if (d != NULL)
		d = ft_scpy(s, d, c);
	return (d);
}
