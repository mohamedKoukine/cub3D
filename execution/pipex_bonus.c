/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:10:39 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/01 14:11:15 by mkaoukin         ###   ########.fr       */
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

void	ft_handler0(int sig)
{
	if (sig == SIGINT)
		close(0);
}

void	here_d(t_m_list *lst, int i, t_list *list)
{
	char	*line;

	unlink("here_doc");
	lst->w_h = open ("here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	lst->r_h = open ("here_doc", O_RDONLY, 0777);
	unlink("here_doc");
	if (lst->w_h == -1 ||lst->r_h == -1)
		ft_exit(1, "error,", "Error_F_H\n", list);
	signal(SIGINT, ft_handler0);
	while (1)
	{
		line = readline("> ");
		if(!ttyname(0))
		{
			g_s = 1;
			open(ttyname(2),O_RDWR);
			break ;
		}
		if (!line)
			break ;
		if ((ft_strlen1(line, 1) == ft_strlen1(lst->file[i], 0))
			&& (ft_strncmp(line, lst->file[i], ft_strlen1(line, 1)) == 0))
		{
			free(line);
			break ;
		}
		if (!ft_strcmp(lst->d_h[i], "<<"))
			line = expanding(line,list);
		// ft_putendl(line, lst->w_h);
		write (lst->w_h, line, ft_strlen1(line, 0));
		write (lst->w_h, "\n", 1);
		free (line);
		line = NULL;
	}
	close (lst->w_h );
	signal(SIGINT, ft_handler);
	
}

void check_$(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '$')
			
		i++;
	}
}
void	ft_redirection2(t_m_list *lst, t_fd *fd, int i)
{
	int j;

	while (lst->d_h[i])
	{
		if (lst->d_h[i][0] == '>' || lst->d_h[i][0] == '<')
		{
			if (lst->d_h[i][0] == '>' && lst->d_h[i][1] == '>')
			{
				j = 0;
				while(lst->file[i][j])
				{
					if (lst->file[i][j] == '$' && lst->file[i][j + 1] != '\0')
						ft_exit(1, lst->file[i],"ambiguous redirect\n", NULL);
					j++;
				}
				fd->id2 = open(lst->file[i],O_CREAT | O_RDWR | O_APPEND, 0777);
			}
			else if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')
				fd->id3 = lst->r_h;
			else if (lst->d_h[i][0] == '<')
				fd->id3 = open(lst->file[i], O_RDWR , 0777);
			else
			{
				j = 0;
				while(lst->file[i][j])
				{
					if (lst->file[i][j] == '$' && lst->file[i][j + 1] != '\0')
						ft_exit(1, lst->file[i],"ambiguous redirect\n", NULL);
					j++;
				}
				fd->id2 = open(lst->file[i],O_CREAT | O_RDWR  | O_TRUNC, 0777);
			}
			if (fd->id2 == -1 || fd->id3 == -1)
				ft_exit(1, lst->file[i],"No such file or directory\n", NULL);
		}
		i++;	
	}
}
void	ft_redirection1(t_m_list *lst, t_fd *fd, int i)
{
	int j;

	while (lst->d_h[i])
	{
		if (lst->d_h[i][0] == '>' || lst->d_h[i][0] == '<')
		{
			if (lst->d_h[i][0] == '>' && lst->d_h[i][1] == '>')
			{
				j = 0;
				while(lst->file[i][j])
				{
					if (lst->file[i][j] == '$' && lst->file[i][j + 1] != '\0')
					{
						fd->id3 = -5;
						printf ("minishell: %s: ambiguous redirect\n", lst->file[i]);
						break ;
					}
					j++;
				}
				fd->id2 = open(lst->file[i],O_CREAT | O_RDWR | O_APPEND, 0777);
			}
			else if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')
				fd->id3 = lst->r_h;
			else if (lst->d_h[i][0] == '<')
				fd->id3 = open(lst->file[i], O_RDWR , 0777);
			else
			{
				j = 0;
				while(lst->file[i][j])
				{
					if (lst->file[i][j] == '$' && lst->file[i][j + 1] != '\0')
					{
						fd->id3 = -5;
						printf ("minishell: %s: ambiguous redirect\n", lst->file[i]);
						break;
					}
					j++;
				}
				fd->id2 = open(lst->file[i],O_CREAT | O_RDWR | O_TRUNC, 0777);
			}
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

void	ft_exit(int l, char *s, char *err, t_list *lst)
{
	int	i;

	i = 0;
	if (l == 0)
	{
		if (lst)
			free_env(lst);
		exit (0);
	}
	else
	{
		if (lst)
			free_env(lst);
		printf("minishell: ");
		printf("%s: ",s);
		printf("%s",err);
		exit (l);
	}
}

int	check_heredoc(t_m_list *lst)
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
	else if (ft_strcmp(line[0], "unset") == 0)
		return(0);
	else
		return (1);
}
int	ft_builtins(char **line, t_list *list, t_m_list *lst, t_fd *fd)
{
	if (ft_strcmp(line[0], "export") == 0)
		ft_export(line, list);
	else if (ft_strcmp(line[0], "env") == 0)
	{
		if (line[1])
			printf ("%s: %s: No such file or directory\n", line[0], line[1]);
		else
			aff_env(list);
	}
	else if (ft_strcmp(line[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(line[0], "echo") == 0)
		ft_echo(lst, 0);
	else if (ft_strcmp(line[0], "exit") == 0)
		my_exit(lst, fd);
	else if (ft_strcmp(line[0], "cd") == 0)
		ft_cd(list, lst, fd);
	else if (ft_strcmp(line[0], "unset") == 0)
		ft_unset(list, lst, line);
	else
		return (1);
	return (fd->ex_c = 0, 0);
}

void ft_handler1(int sig)
{
    if (sig == SIGINT)
        printf("");
}

void	command(t_fd	*fd, t_m_list *lst, t_list *list)
{
	int		p[2];

	if (pipe(p) == -1)
		ft_exit(1, "pipe","ERROR PIPE\n", NULL);
	fd->id1 = fork();
	if (fd->id1 == -1)
	{
		printf ("minishell: fork: Resource temporarily unavailable\n");
		return ;
	}
	signal(SIGINT, ft_handler1);
	if (fd->id1 == 0)
	{
		g_s = 1;
		signal(SIGQUIT, SIG_DFL);
		g_s = 0;
		ft_redirection(lst, fd, 0);
		if (lst->first_comm)
		{
			parsing_b(lst->first_comm, fd->env, fd);
			if (fd->id == 1 && lst->next)
			{
				close(p[0]);
				dup2(p[1],STDOUT_FILENO);
				close(p[1]);
			}
			if (ft_builtins(lst->dup_com, list, lst, fd) == 0)
				exit(0);
			else if (execve(fd->path, lst->dup_com, fd->env) == -1)
			{
				write (2, "minishell: ", 11);
				write (2, lst->first_comm, ft_strlen(lst->first_comm));
				write (2, ": ", 2);
				write (2, "command not found\n", 18);
				exit (127);
			}
		}
		exit(0);
	}
	else
	{
		if (lst->next == NULL)
			fd->id_ex = fd->id1;
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
	}
}
void	open_heredoc(t_m_list *lst, t_list *list)
{
	int		i;
	char	s[7] = "/tmp/a";

	i = 0;
	while (lst->d_h[i])
		i++;
	if (i > 16)
		ft_exit(2, "maximum here-document count exceeded\n", "\0", list);
	while (lst)
	{
		i = 0;
		lst->r_h = 200;
		while (lst->d_h[i])
		{
			if ((!ft_strcmp(lst->d_h[i], "<<")) || (!ft_strcmp(lst->d_h[i], "<<<")))
			{
				close(lst->r_h);
				here_d(lst, i, list);
				s[5] += 1;
			}
			i++;
		}
		lst = lst->next;
	}
}

void	convert_env(t_list *list, t_fd *fd)
{
	int i;
	int j;
	
	i = 0;
	fd->env = malloc (sizeof(char *) * (ft_lstsize1(list) + 1));
	if (!fd->env)
		return ;
	while (list)
	{
		j = 0;
		fd->env[i] = malloc(ft_strlen(list->env) + 1);
		if (!fd->env[i])
			return ;
		while (list->env[j])
		{
			fd->env[i][j] = list->env[j];
			j++;
		}
		fd->env[i][j] = '\0';
		i++;
		list = list->next;
	}
	fd->env[i] = NULL;
}
void	update_env_(t_m_list *lst, t_list *list)
{
	int	i;
	
	i = 0;
	while (lst->dup_com[i])
		i++;
	if (i)
		i--;
	while (list)
	{
		if (list->env[0] == '_' && list->env[1] == '=')
		{
			free (list->env);
			free (list->ex);
			list->env = ft_strjoin(list->key, "=", 1);
			list->ex = ft_substr(lst->dup_com[i], 0, ft_strlen(lst->dup_com[i]), 0);
			if (!list->ex)
				list->ex = ft_strdup("");
			list->env = ft_strjoin(list->env, list->ex, 0);
		}
		list = list->next;
	}
}

void	ft_function1(int ac, t_m_list *lst, t_fd *fd, t_list *list)
{
	int		i;

	update_env_(lst, list);
	i = 0;
	fd->id1 = 1;
	fd->id3 = 1;
	while (++i <= ac && fd->id1 != -1)
	{
			if (lst->dup_com[0] && ft_check_builtins(lst->dup_com) == 0 && ac == 1)
			{
				ft_redirection(lst, fd, 1);
				if (fd->id3 != -1 && fd->id3 != -5)
					ft_builtins(lst->dup_com, list, lst, fd);
			}
			else
			{
				convert_env(list, fd);
				command(fd, lst, list);
				free_all(fd->env);
			}
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
		d = d->next;
	return (d);
}

void remove_f_h(t_m_list *lst)////////////////////////////////////
{
	int		i;
	int		j;
	// char	s[7] = "/tmp/a";
	
	i = 0;
	j = number_heredoc(lst);
	while (lst)
	{
		close (lst->r_h);
		lst = lst->next;
	}
}

void	ft_pipex(t_m_list *lst, t_list *list, t_fd *fd)
{
	struct termios    state;
	int			ex;

	fd->id_ex = 0;
	open_heredoc(lst, list);
	tcgetattr(STDOUT_FILENO, &state);
	ft_function1(ft_lstsize(lst), lst, fd, list);
	if (fd->id3 == 1)
	{
		waitpid(fd->id_ex, &ex, 0);
		if (WIFSIGNALED(ex))
		{
			if (WTERMSIG(ex) == 3)
			{
				fd->ex_c = 131;
				write (1, "quit 3\n", 8);
			}
			if (WTERMSIG(ex) == 2)
			{
				g_s = 0;
				fd->ex_c = 130;
			}
		}
		else
			fd->ex_c = WEXITSTATUS(ex);
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	tcsetattr(STDOUT_FILENO, TCSANOW, &state);
	signal(SIGINT, ft_handler);
	remove_f_h(lst);
}
