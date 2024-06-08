# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 16:50:44 by mkaoukin          #+#    #+#              #
#    Updated: 2024/06/07 15:39:17 by mkaoukin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = CC

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRC =	ft_split.c\
		parsing_pipex.c\
		ft_strjoinn.c\
		ft_strncmp.c\
		ft_str.c\
		ft_lstadd_back_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstnew_bonus.c\
		get_next_line_utils.c\
		get_next_line.c\
		minishell.c\
		aff_env.c\
		pwd.c\
		pipex_bonus.c

OBJ = $(SRC:.c=.o)

INCLUDE = minishell.h

	
$(NAME): $(OBJ)
	$(CC) $(OBJ) -lreadline -o $(NAME) -fsanitize=address -g
%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

clean :
	rm -rf  $(OBJ)

fclean : clean
	rm -rf  $(NAME)

re : fclean all

.PHONY : clean