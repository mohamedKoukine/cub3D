/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:11:28 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/04 12:56:28 by mkaoukin         ###   ########.fr       */
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

static int	ft_check_slash(const char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	cont_access_cmd(char **path, t_fd *fd)
{
	int	i;

	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoinn(path[i], "/");
		if (!path[i])
			ft_exit(1, "error", "allocation\n", NULL);
		path[i] = ft_strjoinn(path[i], fd->av2);
		if (!path[i])
			ft_exit(1, "error", "allocation\n", NULL);
		if (access(path[i], F_OK | X_OK) != -1)
			fd->path = ft_substr(path[i], 0, ft_strlen1(path[i], 0), 0);
		i++;
	}
	free_all(path);
	free (fd->av2);
	fd->av2 = NULL;
	free (fd->line);
	fd->line = NULL;
}

static void	access_cmd(char **path, t_fd *fd, char *av)
{
	int	j;

	j = 0;
	if (ft_check_slash(av))
	{
		if (opendir(av))
			ft_exit(126, av, "is a directory\n", NULL);
		else if (access(av, F_OK | X_OK) == 0)
		{
			fd->path = ft_substr(av, 0, ft_strlen1(av, 0), 0);
			if (!fd->path)
				ft_exit(1, "error", "allocation\n", NULL);
		}
		else
			ft_exit(126, av, "Permission denied\n", NULL);
	}
	else
	{
		fd->av2 = ft_substr(av, 0, ft_strlen1(av, 0), 0);
		if (!fd->av2)
			ft_exit(1, "error", "allocation\n", NULL);
		cont_access_cmd(path, fd);
	}
}

void	parsing_b(char *av, char **env, t_fd *fd)
{
	char	**path;
	int		i;

	fd->line = NULL;
	fd->path = NULL;
	fd->av2 = NULL;
	i = -1;
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
		ft_exit(127, av, "No such file or directory\n", NULL);
	while (av[++i])
	{
		if (av[i] == ' ')
			ft_exit(127, av, "command not found\n", NULL);
	}
	access_cmd(path, fd, av);
}
