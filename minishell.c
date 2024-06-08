/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:10:06 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/06/08 14:14:25 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void ft_mlst(m_list *lst)
// {
// 	m_list mlst;

// 	lst->command = "cat";
// 	lst->d_com[0] = "cat";
	
// 	lst->next = &mlst;

// 	mlst.command = "wc -l";
// 	mlst.d_com[0] = "wc";
// 	mlst.d_com[1] = "-l";
	
// 	// printf("%s\n", lst->command);
// 	// printf("%s\n", lst->d_com[0]);

// 	// printf("%s\n", lst->next->command);
// }
int	ft_lstsize(m_list *lst)
{
	int		i;
	m_list	*d;

	d = lst;
	i = 0;
	while (d)
	{
		d = d->next;
		i++;
	}
	return (i);
}
int main (int ac, char **av, char **env)
{
	char	*input = NULL;
	char	*tmp = NULL;
	t_list	*lst = NULL;
	m_list	mlst;
	(void) ac;
	(void) av;

	ft_env(env, &lst);
	mlst.p[1] = dup(STDOUT_FILENO);
	mlst.p[0] = dup(STDIN_FILENO);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			exit(0);
		if (input && input[0] && ft_strcmp(input, tmp))
		{
			add_history(input);
			tmp = ft_strdup(input);
		}
		if (ft_strcmp(input, "env") == 0)
			aff_env(lst);
		else if (ft_strcmp(input, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(input, "pipex") == 0)
		{
			
			mlst.command = "cat";
			// mlst.d_com[1] = "";
			mlst.h_d[0] = "<<";
			mlst.h_d[1] = "<<";
			mlst.h_d[2] = "<";
			mlst.h_d[3] = "<<";
			mlst.h_d[4] = "t";
			mlst.h_d[5] = NULL;
			mlst.h_d_f[0] = "a";
			mlst.h_d_f[1] = "a";
			mlst.h_d_f[2] = "pwd.c";
			mlst.h_d_f[3] = "aa";
			mlst.h_d_f[4] = "a";
			mlst.next = NULL;

			// m_list mmlst;
			// mlst.next = &mmlst;
			// mmlst.command = "grep p";
			// mmlst.h_d[0] = "t";
			// mmlst.h_d[1] = "t";
			// mmlst.h_d[2] = "t";
			// mmlst.h_d[3] = NULL;
			// mmlst.h_d_f[0] = "a";
			// mmlst.h_d_f[1] = "a";
			// mmlst.h_d_f[2] = "aaa";
			// mmlst.next = NULL;
			
			// m_list mmmlst;
			// mmlst.next = &mmmlst;
			
			// mmmlst.command = "cat";
			// mmmlst.h_d[0] = "tt";
			// mmmlst.h_d[1] ="tt";
			// mmmlst.h_d[2] = "t";
			// mmmlst.h_d[3] = NULL;
			// mmmlst.h_d_f[0] = "c..";
			// mmmlst.h_d_f[1] = "cc";
			// mmmlst.h_d_f[2] = "ccc..";
			// mmmlst.next = NULL;
			ft_pipex(ft_lstsize(&mlst), &mlst,env);
		}
		free(input);
		input = NULL;
		dup2(mlst.p[1], STDOUT_FILENO);
		dup2(mlst.p[0], STDIN_FILENO);
	}
}