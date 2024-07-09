/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:10:39 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/07/08 16:00:42 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

int	number_heredoc(t_m_list *lst)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (lst)
	{
		while (lst && lst->d_h[i])
		{
			if (lst->d_h[i][0] == '>' || lst->d_h[i][0] == '<')
			{
				if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')		
					j++;
			}
			i++;
		}
		i = 0;
		lst = lst->next;
	}
	return (j);
}
void	here_d(t_m_list *lst, int i, char *s)
{
	char	*line;

	lst->f_h = open (s, O_CREAT | O_RDWR, 0777);
	if (lst->f_h == -1)
		ft_exit(1, "error,","Error_F_H\n");
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			ft_exit(1, "error","ERROR\n");
		if ((ft_strlen1(line, 1) == ft_strlen1(lst->file[i], 0))
			&& (ft_strncmp(line, lst->file[i], ft_strlen1(line, 1)) == 0))
		{
			free(line);
			break ;
		}
		write (lst->f_h, line, ft_strlen1(line, 0));
		free (line);
		line = NULL;
	}
	close (lst->f_h);
	lst->f_h = open (s, O_RDWR | O_APPEND, 0777);
	if (lst->f_h == -1)
		ft_exit(1, "error,","Error_F_H\n");
}

void	ft_redirection2(t_m_list *lst, t_fd *fd, int i)
{
	while (lst->d_h[i])
	{
		if (lst->d_h[i][0] == '>' || lst->d_h[i][0] == '<')
		{
			if (lst->d_h[i][0] == '>' && lst->d_h[i][1] == '>')
				fd->id2 = open(lst->file[i],O_CREAT | O_RDWR | O_APPEND, 0777);
			else if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')
				fd->id3 = lst->f_h;
			else if (lst->d_h[i][0] == '<')
				fd->id3 = open(lst->file[i], O_RDWR , 0777);
			else	
				fd->id2 = open(lst->file[i],O_CREAT | O_RDWR, 0777);
			if (fd->id2 == -1 || fd->id3 == -1)
				ft_exit(1, lst->file[i],"No such file or directory\n");
		}
		i++;	
	}
}
void	ft_redirection1(t_m_list *lst, t_fd *fd, int i)
{
	while (lst->d_h[i])
	{
		if (lst->d_h[i][0] == '>' || lst->d_h[i][0] == '<')
		{
			if (lst->d_h[i][0] == '>' && lst->d_h[i][1] == '>')
				fd->id2 = open(lst->file[i],O_CREAT | O_RDWR | O_APPEND, 0777);
			else if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')
				fd->id3 = lst->f_h;
			else if (lst->d_h[i][0] == '<')
				fd->id3 = open(lst->file[i], O_RDWR , 0777);
			else	
				fd->id2 = open(lst->file[i],O_CREAT | O_RDWR, 0777);
			if (fd->id2 == -1 || fd->id3 == -1)
			{
				printf ("minishell: %s: No such file or directory\n", lst->file[i]);
				break;
			}
		}
		i++;	
	}
}

void	ft_redirection(t_m_list *lst, t_fd *fd, int i)
{	
	fd->id = 1;
	fd->id2 = -2;
	fd->id3 = -2;
	if (i == 0)
		ft_redirection2(lst, fd, 0);
	else
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

void	ft_exit(int l, char *s, char *err)
{
	int	i;

	i = 0;
	if (l == 0)
		exit (0);
	else
	{
		printf("minishell: ");
		printf("%s: ",s);
		printf("%s",err);
		exit (l);
	}
}

// void	command3(t_fd	*fd, t_m_list *lst, char **env)
// {
// 	int		id;

// 	id = fork();
// 	if (id == -1)
// 		ft_exit(1, "error","Error Fork\n");
// 	if (id == 0)
// 	{
// 		ft_redirection(lst, fd);
// 		if (lst->first_comm)
// 		{
// 			parsing_b(lst->first_comm, env, fd);
// 			if (execve(fd->path1, lst->dup_com, env) == -1)
// 				ft_exit(1, lst->first_comm, "command not found\n"); 
// 		}
// 		exit(0);
// 	}
// }

int	check_heredoc(t_m_list *lst)/////////
{
	int	i;
	t_m_list	*lst1;

	lst1 = lst->next;
	i = 0;
	while (lst1 && lst1->d_h[i])
	{
		if (lst1->d_h[i][0] == '>' || lst1->d_h[i][0] == '<')
		{
			if (lst1->d_h[i][0] == '<' && lst1->d_h[i][1] == '<')		
				return (1);
		}
		i++;
	}
	return (0);
}

int ft_check_builtins(char **line)
{
	if (ft_strcmp(line[0], "export") == 0)
		return(0);
	else if (ft_strcmp(line[0], "env") == 0)
		return(0);
	else if (ft_strcmp(line[0], "pwd") == 0)
		return(0);
	else if (ft_strcmp(line[0], "echo") == 0)
		return(0);
	else if (ft_strcmp(line[0], "exit") == 0)
		return(0);
	else if (ft_strcmp(line[0], "cd") == 0)
		return(0);
	else
		return (1);
}
int ft_builtins(char **line, t_list *list, t_m_list *lst)
{
	if (ft_strcmp(line[0], "export") == 0)
		ft_export(line, list);
	else if (ft_strcmp(line[0], "env") == 0)
	{
		if (line[1])
			printf ("%s: %s: No such file or directory", line[0], line[1]);
		else
			aff_env(list);
	}
	else if (ft_strcmp(line[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(line[0], "echo") == 0)
		ft_echo(lst, 0);
	else if (ft_strcmp(line[0], "exit") == 0)
		my_exit(lst);
	else if (ft_strcmp(line[0], "cd") == 0)
		ft_cd(list, lst);
	else
		return (1);
	return (0);
}
void	command(t_fd	*fd, t_m_list *lst, char **env, t_list *list)
{
	int		p[2];

	if (pipe(p) == -1)
		ft_exit(1, "pipe","ERROR PIPE\n");
	fd->id1 = fork();
	if (fd->id1 == -1)
		ft_exit(1, "error","ERROR FORK()\n");
	if (fd->id1 == 0)
	{
		ft_redirection(lst, fd, 0);
		if (lst->first_comm)
		{
			parsing_b(lst->first_comm, env, fd);
			if (fd->id == 1 && lst->next)
			{
				close(p[0]);
				dup2(p[1],STDOUT_FILENO);
				close(p[1]);
			}
			if (ft_builtins(lst->dup_com, list, lst) == 0)
				exit(0);
			else if (execve(fd->path1, lst->dup_com, env) == -1)
				ft_exit(1, lst->first_comm, "command not found\n");
		}
		exit(0);
	}
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
	}
}
void	open_heredoc(t_m_list *lst)
{
	int		i;
	char	s[7] = "/tmp/a";////////////////////////////////////////////////////

	i = 0;
	while (lst)
	{
		lst->f_h = 200;
		while (lst->d_h[i])
		{
			if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')
			{
				close(lst->f_h);
				here_d(lst, i, s);
				s[5] += 1;
			}
			i++;
		}
		i = 0;
		lst = lst->next;
	}
}

void	ft_function1(int ac, t_m_list *lst, char **env, t_fd *fd, t_list *list)
{
	fd->i = 0;

	while (++fd->i <= ac)
	{
			if (lst->dup_com[0] && ft_check_builtins(lst->dup_com) == 0 && ac == 1)
			{
				ft_redirection(lst, fd, 1);
				if (fd->id3 != -1)
					ft_builtins(lst->dup_com, list, lst);
			}
			else
				command(fd, lst, env, list);
		lst = lst->next;
	}

}

t_m_list	*ft_lstlastt(t_m_list *lst)
{
	t_m_list	*d;

	if (!lst)
		return (0);
	d = lst;
	while (d->next)
	{
		d = d->next;
	}
	return (d);
}

void remove_f_h(t_m_list *lst)////////////////////////////////////
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

void	ft_pipex(int ac, t_m_list *lst, char **env, t_list *list)
{
	t_fd		fd;
	int			ex;
	if (ac >= 1)
	{
		open_heredoc(lst);
		ft_function1(ac, lst, env, &fd, list);
		while (waitpid(-1, &ex, 0) != -1)
			;
		fd.ex_c = WEXITSTATUS(ex);
		remove_f_h(lst);
	}
	else
		write (2, "Error_Argc\n", 11);
}
