/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mian.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:03:56 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/06/07 12:55:08 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main ()
{
	m_list lst;
	lst.f_h = malloc(sizeof(int) * 3);
	lst.f_h[0] = 1;
	lst.f_h[1] = 2;
	lst.f_h[2] = 3;
	int j;
	int k;
	printf("%d\n",*lst.f_h);
	j = ++*lst.f_h;
	k = ++*lst.f_h;
	printf("%d\n",j);
	printf("%d\n",k);
}