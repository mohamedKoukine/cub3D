/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:11:28 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/07/18 16:23:23 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	free_all(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free (p[i]);
		p[i] = NULL;
		i++;
	}
	free(p);
	p = NULL;
}

static int	ft_position(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (i);
}

static void	cont_access_cmd(char **path, t_fd *fd)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoinn(path[i], "/");
		if (!path[i])
			ft_exit(1, "error", "allocation\n");
		path[i] = ft_strjoinn(path[i], fd->av2);
		if (!path[i])
			ft_exit(1, "error", "allocation\n");
		if (access(path[i], F_OK | X_OK) != -1)
		{
			fd->path = ft_substr(path[i], 0, ft_strlen1(path[i], 0));
		}
		i++;
	}
	// if (!fd->path1)
	// 	ft_exit(127, fd->av2, "command not found\n");
	free_all(path);
	free (fd->av2);
	fd->av2 = NULL;
	free (fd->line);
	fd->line = NULL;
}

static void	access_cmd(char **path, t_fd *fd, char *av)
{
	int	i;
	int	j;

	j = 0;
	while (path[j])
	{
		if (ft_strncmp(path[j], av, ft_strlen1(path[j], 0)) == 0)
		{
			i = ft_position(path[j], av);
			fd->av2 = ft_substr(av, i, ft_strlen1(av, 0) - i);
			if (!fd->av2)
				ft_exit(1, "error", "allocation\n");
		}
		j++;
	}
	if (!fd->av2)
		fd->av2 = ft_substr(av, 0, ft_strlen1(av, 0));
	if (!fd->av2)
		ft_exit(1, "error", "allocation\n");
	cont_access_cmd(path, fd);
}

void	parsing_b(char *av, char **env, t_fd *fd)
{
	char	**path;
	int		i;

	fd->line = NULL;
	fd->path = NULL;
	fd->av2 = NULL;
	i = 0;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			fd->line = ft_strdup((*env + 5));
			break ;
		}
		env++;
	}
	path = ft_split1(fd->line, ':');
	if (!path)
		ft_exit(1, "error", "ERROR_IN_SPLIT\n");
	while (av[i])
	{
		if (av[i] == ' ')
			ft_exit(1, av, "command not found\n");
		i++;
	}
	access_cmd(path, fd, av);
}
