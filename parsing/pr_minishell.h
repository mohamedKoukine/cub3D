/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouab <aelbouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:32:09 by aelbouab          #+#    #+#             */
/*   Updated: 2024/08/04 16:42:10 by aelbouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PR_MINISHELL_H
# define PR_MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

int	g_s;

size_t		ft_strlen(char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

typedef struct s_fd
{
	int			id;
	int			id1;
	int			id2;
	int			id3;
	int			id_ex;
	int			ex_c;
	char		*path;
	char		*av2;
	char		**env;
	char		*line;
}			t_fd;

typedef struct minishell
{
	char				*command;
	char				*first_comm;
	char				**d_com;
	char				**dup_com;
	char				**d_h;
	char				**file;
	void				*ptr_unset;
	int					p[2];
	int					w_h;
	int					r_h;
	struct minishell	*next;
}	t_m_list;

typedef struct s_list
{
	char			*env;
	char			*key;
	char			*ex;
	int				check_aff;
	int				i;
	struct s_list	*next;
}	t_list;

void		ft_lstadd_back_env(t_list **lst, t_list *new);
t_list		*ft_lstlast_env(t_list *lst);
char		**ft_split(char const *s, char c);
void		ft_lstadd_back(t_m_list **lst, t_m_list *new);
t_m_list	*ft_lstlast(t_m_list *lst);
t_m_list	*ft_lstnew(char *content, char **com);
char		*ft_strdup(const char *src);
int			is_empty(char *line);
t_list		*ft_lstnew1(char *env, int i, int k, char *p);
void		ft_env(char **env, t_list **lst, int j, char *p);
void		aff_env(char **line, t_list *lst, t_fd *fd);
int			ft_isalnum(int i);
char		*ft_strtrim(char *s1, char const *set, int fre);
int			quotes_nb(char *line);
void		*allocation(char *line);
char		*rm_space(char *line);
int			cases(char *line);
int			syntax_error(char *line);
char		*magic_hide2(char *line, int s);
char		*magic_hide(char *line);
char		*dollar(char *line, int i, int j, char *line2);
char		*duh(char *line, int i, int cp);
int			cp_hd(char *line);
char		*add_space(char *line, int ls, int i, int j);
char		*expanding(char *line, t_list *lst);
t_m_list	*en_s(t_m_list *lst, int cp);
t_m_list	*final_s(t_m_list *lst);
int			checkit(char *red);
int			ft_len(char **str);
long		ft_atoi(const char *str);
void		ft_echo(t_m_list *list, int s);
void		my_exit(t_m_list *list, t_fd *fd, int exit_code);
void		ft_cd(t_list *lst, t_m_list *list, t_fd *fd);
char		*ft_itoa(int n);
int			if_its_q(char q);
char		*get_home(t_list *lst);
char		*exit_code(char *line, char *code, int i, int k);
void		ft_handler(int sig);
void		free_env(t_list *lst);
void		freethis(char *env, char *ex);
char		*get_home(t_list *lst);
char		*is_pwd(t_list *lst);
char		*oldisgold(t_list *lst);
int			ft_posistion(char *line, char c);
size_t		ft_strlen_exp(const char *str, char c, int flag);
void		aff_export(t_list *lst);
void		print_export(t_list *lst, t_list *lst2, int i);
t_m_list	*split_all(char *line);
t_m_list	*clear_lst(t_m_list *list);
t_m_list	*list_to_exe(char *line);
char		*no_qutes(char *line, int fre, int i, int j);
void		garbag_find(char *arg);
t_m_list	*decript_stack(t_m_list *list);
char		*ambi_str(char *line, t_list *lst);
int			chek_ambi(char *line, t_list *lst);
char		*ambiguous(char *line, t_list *lst);
int			include_q(char *line);
char		*handel_here(char *line, int i, int j);
int			include_sq(char *line);
char		*handel_ambi(char *line, int i, int j);
char		*line_shower(char *line, t_list *lst, t_fd *fd);
void		fill_dfile(t_m_list *tmp);
int			cp_conter(t_m_list *tmp, int cp);
void		final_ss(t_m_list *tmp, int i, int j, int cp);
char		*here_dollar(char *line, t_list *lst, int i);
char		*ddhere(char *line, int i, int j, t_list *lst);
void		free_list(t_m_list *list);
int			d_cp(char *line, int j);
char		*place_key2(char *line, char *str, t_list *lst, int i);
int			here_expand(char **line, char *str, t_list *lst);
int			strchr_char(char *s, char c);
int			con_d(int *i, char *line, int *s);

#endif