/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:05:37 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/09/25 12:14:14 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*free_and_join(char *line, char *rest)
{
	char	*tmp;

	tmp = ft_strdup(line);
	free(line);
	if (!tmp && !rest)
		return (NULL);
	if (!rest)
		line = ft_strdup(tmp);
	else
		line = ft_strjo_or_cat(tmp, rest);
	free(tmp);
	return (line);
}

static char	*free_and_sub(char *rest)
{
	char	*tmp;

	if (ft_strchr(rest, '\n') == -1)
	{
		free(rest);
		rest = NULL;
	}
	else
	{
		tmp = ft_strdup(rest);
		free(rest);
		rest = ft_substr(tmp, ft_strchr(tmp, '\n') + 1, ft_strlen(tmp, 0));
		free(tmp);
	}
	return (rest);
}

static char	*ft_read(char *rest, int fd)
{
	int		i;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (free(rest), NULL);
	i = 1;
	while (i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (free(buff), free(rest), NULL);
		buff[i] = '\0';
		rest = ft_strjoin(rest, buff);
		if (ft_strchr(buff, '\n') > -1)
			break ;
	}
	free(buff);
	buff = NULL;
	return (rest);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s || *s == '\0')
		return (-1);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = free_and_join(line, rest);
	if (ft_strchr(rest, '\n') == -1 && rest)
	{
		free(rest);
		rest = NULL;
	}
	if (ft_strchr(line, '\n') == -1)
	{
		rest = ft_read(rest, fd);
		if (!rest)
			return (free(line), NULL);
		line = free_and_join(line, rest);
	}
	rest = free_and_sub(rest);
	if (*line == '\0')
		return (free (line), free(rest), line = NULL, NULL);
	return (line);
}
