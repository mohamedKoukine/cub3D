/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:32:09 by aelbouab          #+#    #+#             */
/*   Updated: 2024/07/08 15:22:57 by mkaoukin         ###   ########.fr       */
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

size_t		ft_strlen(char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

typedef struct minishell
{
	char				*command;
	char				*first_comm;
	char				**d_com;
	char				**dup_com;
	char				**d_h;
	char				**file;
	int					p[2];
	int					f_h;
	struct minishell	*next;
}	t_m_list;

int	e_code;

typedef struct s_list
{
	char			*env;
	char			*key;
	char			*ex;
	int				check_aff;
	int				i;
	int				e_code;
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
t_list		*ft_lstnew1(char *env, int i, int k);
void		ft_env(char **env, t_list **lst);
void		aff_env(t_list *lst);
int			ft_isalnum(int i);
char		*ft_strtrim(char const *s1, char const *set);
int			quotes_nb(char *line);
void		*allocation(char *line);
char		*rm_space(char *line);
int			cases(char *line);
int			syntax_error(char *line);
char		*magic_hide2(char *line);
char		*magic_hide(char *line);
char		*dollar(char *line, int i, int j, char *line2);
char		*duh(char *line, int i, int cp);
int			cp_hd(char *line);
char		*add_space(char *line);
char		*place_key(char *line, char *str, t_list *lst);
char		*expanding(char *line, t_list *lst);
t_m_list	*en_s(t_m_list *lst, int cp);
t_m_list	*final_s(t_m_list *lst);
int			checkit(char *red);
int			ft_len(char **str);
int			ft_atoi(const char *str);
void		ft_echo(t_m_list *list, int s);
void		my_exit(t_m_list *list);
void		ft_cd(t_list *lst, t_m_list *list);

#endif