/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:10:39 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/06/08 14:29:11 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_heredoc(m_list *lst)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (lst)
	{
		while (lst && lst->h_d[i])
		{
			if (lst->h_d[i][0] == '>' || lst->h_d[i][0] == '<')
			{
				if (lst->h_d[i][0] == '<' && lst->h_d[i][1] == '<')		
					j++;
			}
			i++;
		}
		i = 0;
		lst = lst->next;
	}
	return (j);
}
void	here_d(m_list *lst, int i, char *s)
{
	char	*line;

	lst->f_h = open (s, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (lst->f_h == -1)
		ft_exit(1, "Error\n");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			ft_exit(1, "ERROR\n");
		if (ft_strncmp(line, lst->h_d_f[i], ft_strlen(line, 1)) == 0)
		{
			free(line);
			break ;
		}
		write (lst->f_h, line, ft_strlen(line, 0));
		free (line);
		line = NULL;
	}
	close (lst->f_h);
	lst->f_h = open (s, O_RDWR | O_APPEND, 0777);
	if (lst->f_h == -1)
		ft_exit(1, "Error\n");
		
	// if (lst->command)
	// {
	// 	dup2(lst->f_h,STDIN_FILENO);
	// 	close(lst->f_h);
	// }
}

void	ft_redirection1(m_list *lst, t_fd *fd, int i)
{
	while (lst->h_d[i])
	{
		if (lst->h_d[i][0] == '>' || lst->h_d[i][0] == '<')
		{
			if (lst->h_d[i][0] == '>' && lst->h_d[i][1] == '>')
				fd->id2 = open(lst->h_d_f[i],O_CREAT | O_RDWR | O_APPEND, 0777);
			else if (lst->h_d[i][0] == '<' && lst->h_d[i][1] == '<')
				fd->id3 = lst->f_h;
			else if (lst->h_d[i][0] == '<')
				fd->id3 = open(lst->h_d_f[i], O_RDWR , 0777);
			else	
				fd->id2 = open(lst->h_d_f[i],O_CREAT | O_RDWR, 0777);
			if (fd->id2 == -1 || fd->id3 == -1)
				ft_exit(1, "ERROR fd");
		}
		i++;	
	}
}
// void	ft_redirection1(m_list *lst, t_fd *fd)
// {
// 	fd->id = 1;
// 	if (lst->h_d[0])// khasni nchecker hadi bash matb9ash tdkhol f ga3 l7alat
// 	{
// 		if (lst->h_d[0][0] == '>' || lst->h_d[0][0] == '<')
// 		{
// 			if (lst->h_d[0][0] == '>' && lst->h_d[0][1] == '>')
// 				fd->id2 = open(lst->h_d_f[0],O_CREAT | O_RDWR | O_APPEND, 0777);
// 			else if (lst->h_d[0][0] == '<' && lst->h_d[0][1] == '<')
// 				fd->id3 = lst->f_h;
// 			else if (lst->h_d[0][0] == '<')
// 				fd->id3 = open(lst->h_d_f[0], O_RDWR , 0777);
// 			else 	
// 				fd->id2 = open(lst->h_d_f[0],O_CREAT | O_RDWR, 0777);
// 			if (fd->id2 == -1 || fd->id3 == -1)
// 				ft_exit(1, "ERROR fd");
// 		}
// 		ft_redirection2(lst,fd,1);
// 	}
// }

void	ft_redirection(m_list *lst, t_fd *fd)
{	
	fd->id2 = -2;
	fd->id3 = -2;
	ft_redirection1(lst, fd, 0);
	
	if (fd->id2 != -2)
	{
		fd->id = 0;
		dup2(fd->id2, STDOUT_FILENO);
		close(fd->id2);
	}
	if (fd->id3 != -2)
	{
		dup2(fd->id3, STDIN_FILENO);
		close(fd->id3);
	}
}

void	ft_exit(int l, char *err)
{
	int	i;

	i = 0;
	if (l == 0)
		exit (0);
	else
	{
		while (err[i])
		{
			write(2, &err[i], 1);
			i++;
		}
		exit (1);
	}
}

void	command3(t_fd	*fd, m_list *lst, char **env)
{
	char	**cmd2;
	int		id;

	id = fork();
	if (id == -1)
		ft_exit(1, "Error Fork");
	if (id == 0)
	{
		ft_redirection(lst, fd);
		if (lst->command)
		{
			parsing_b(lst->command, env, fd);
			cmd2 = ft_split(lst->command, ' ');
			if (execve(fd->path1, cmd2, env) == -1)
				ft_exit(1, "ERROR IN CMD2\n");
		}
	}
	else
		wait(NULL);
}

// void	command1(t_fd	*fd, char *av, char **env)
// {
// 	char	**cmd1;
// 	int		p[2];

// 	parsing_b(av, env, fd);
// 	if (pipe(p) == -1)
// 		ft_exit(1, "ERROR PIPE\n");
// 	fd->id1 = fork();
// 	if (fd->id1 == -1)
// 		ft_exit(1, "ERROR FORK()\n");
// 	if (fd->id1 == 0)
// 	{
// 		close(p[0]);
// 		cmd1 = ft_split(av, ' ');
// 		dup2(p[1], STDOUT_FILENO);
// 		close(p[1]);
// 		if (execve(fd->path1, cmd1, env) == -1)
// 			ft_exit(1, "ERROR IN CMD1\n");
// 	}
// 	else
// 	{
// 		close(p[1]);
// 		dup2(p[0], STDIN_FILENO);
// 		close(p[0]);
// 		wait(NULL);
// 	}
// }
// void excute_c_heredoc(m_list *lst, t_fd *fd, char **env)
// {
// 	int	p[2];
// 	char **cmd1;

// 	if (pipe(p))
// 		ft_exit(1,"ERROR PIPE");
// 	fd->id1 = fork();
// 	if (fd->id1 == -1)
// 		ft_exit(1,"ERROR FORK");
// 	if (fd->id1 == 0)
// 	{
// 		ft_redirection(lst, fd);
// 		if (lst->command)
// 		{
// 			parsing_b(lst->command, env, fd);
// 			cmd1 = ft_split(lst->command ,' ');
// 			if (execve(fd->path1, cmd1, env) == -1)
// 				ft_exit(1, "ERROR IN CMD1\n");
// 		}
// 	}
// 	else
// 	{
// 		close(p[1]);
// 		dup2(p[0], STDIN_FILENO);
// 		close(p[0]);
// 		wait(NULL);
// 	}
// }

int	check_heredoc(m_list *lst)/////////
{
	int	i;
	m_list	*lst1;

	lst1 = lst->next;
	i = 0;
	while (lst1 && lst1->h_d[i])
	{
		if (lst1->h_d[i][0] == '>' || lst1->h_d[i][0] == '<')
		{
			if (lst1->h_d[i][0] == '<' && lst1->h_d[i][1] == '<')		
				return (1);
		}
		i++;
	}
	return (0);
}

void	command(t_fd	*fd, m_list *lst, char **env)
{
	char	**cmd1;
	int		p[2];

	if (pipe(p) == -1)
		ft_exit(1, "ERROR PIPE\n");
	fd->id1 = fork();
	if (fd->id1 == -1)
		ft_exit(1, "ERROR FORK()\n");
	if (fd->id1 == 0)
	{
		ft_redirection(lst, fd);
		if (lst->command)
		{
			if (fd->id == 1)
			{
				close(p[0]);
				dup2(p[1],STDOUT_FILENO);
				close(p[1]);
			}
			parsing_b(lst->command, env, fd);
			cmd1 = ft_split(lst->command ,' ');
			if (execve(fd->path1, cmd1, env) == -1)
				ft_exit(1, "ERROR IN CMD1\n");
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
	}
}
void	open_heredoc(m_list *lst)
{
	int		i;
	char	s[7] = "/tmp/a";

	i = 0;
	while (lst)
	{
		lst->f_h = 200;
		while (lst->h_d[i])
		{
			if (lst->h_d[i][0] == '>' || lst->h_d[i][0] == '<')
			{
				if (lst->h_d[i][0] == '<' && lst->h_d[i][1] == '<')
				{
					close(lst->f_h);
					here_d(lst, i, s);
					s[5] += 1;
				}
			}
			i++;
		}
		i = 0;
		lst = lst->next;
	}
}

void	ft_function1(int ac, m_list *lst, char **env, t_fd *fd)
{
	fd->i = 0;

	while (++fd->i < ac)
	{
			command(fd, lst, env);
		lst = lst->next;
	}
}

m_list	*ft_lstlastt(m_list *lst)
{
	m_list	*d;

	if (!lst)
		return (0);
	d = lst;
	while (d->next)
	{
		d = d->next;
	}
	return (d);
}

void func()
{
	system("lsof -c minishell");
}



void remove_f_h(m_list *lst)
{
	int		i;
	int		j;
	char	s[7] = "/tmp/a";
	
	i = 0;
	j = number_heredoc(lst);
	while (i < j)
	{
		unlink(s);
		s[5] += 1;
		i++;
	}
	while (lst)
	{
		close (lst->f_h);
		lst = lst->next;
	}
}

void	ft_pipex(int ac, m_list *lst, char **env)
{
	atexit(func);
	t_fd	fd;
	m_list *lst1;
	fd.fd = 0;
	(void) env;
	if (ac >=2)
	{
		open_heredoc(lst);
		ft_function1(ac, lst, env, &fd);
		// free (fd.path1);
		// unlink("/tmp/here_doc");
		lst1 = ft_lstlastt(lst);
		command3(&fd, lst1,env);
		remove_f_h(lst);
		
	}
	else if (ac == 1)
	{
		open_heredoc(lst);
		command3(&fd, lst, env);
		remove_f_h(lst);
	}
	else
		write (2, "Error_Argc\n", 11);
}
