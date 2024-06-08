#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <limits.h>
# include <fcntl.h>


typedef struct s_list
{
	char			*env;
	struct s_list	*next;
}			t_list;

typedef struct minishell
 {
    char            *command;
    char            *d_com[10];
	char			*h_d[7];
	char			*h_d_f[7];
	int				p[2];
	int				f_h;
    struct minishell    *next;
 } m_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
char	*ft_strdup(const char *src);
int	ft_strcmp(const char *s1, const char *s2);
void ft_env(char **env, t_list **lst);
void aff_env(t_list *lst);
void ft_pwd();

char	**ft_split(char const *s, char c);
char	*ft_strjoinn(char *s1, char *s2);
// char	*ft_strjoin(char *s1, char *s2);
void	ft_exit(int l, char *err);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

typedef struct s_fd
{
	int			id3;
	int			id1;
	int			id2;
	int			idhe;
	int			id;
	int			i;
	int			fd;
	int			*f_h;
	char		*path1;
	char		*path2;
	char		*av2;
	char		*av3;
	char		*line;
}			t_fd;

void	parsing_b(char *av, char **env, t_fd *fd);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjo_or_cat(char *s1, char *s2);
int		ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str, int flag);
void	free_all(char **p);
void	ft_pipex(int ac, m_list *lst, char **env);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif


#endif

