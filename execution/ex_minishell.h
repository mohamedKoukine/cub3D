#ifndef MINISHELL_H
# define MINISHELL_H


# include "../parsing/pr_minishell.h"
# include <limits.h>
# include <fcntl.h>
# include <termios.h>
#include <dirent.h>


char	*ft_strdup(const char *src);
int		ft_strcmp1(const char *s1, const char *s2);
void	ft_pwd();

char	*ft_strjoinn(char *s1, char *s2);
void	ft_exit(int l, char *s, char *err, t_list *lst);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	parsing_b(char *av, char **env, t_fd *fd);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2, int l);
size_t	ft_strlen1(const char *str, int flag);
void	free_all(char **p);
char	**ft_split1(char const *s, char c);
void	ft_pipex(t_m_list *lst, t_list *list, t_fd *fd);
int		ft_lstsize(t_m_list *lst);
int		ft_lstsize1(t_list *lst);
void	ft_export(char **line, t_list *lst);
int		ft_builtins(char **line, t_list *list, t_m_list *lst, t_fd *fd);
char	*ft_substr(char *s, unsigned int start, size_t len, int fre);
t_list	*ft_unset(t_list *lst, t_m_list *list, char **line);
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif


#endif

