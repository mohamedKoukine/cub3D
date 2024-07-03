NAME = minishell

CC = cc 

FLAGS = -Wall -Wextra -Werror -fsanitize=address
READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

SRC = ./parsing/ft_strlen.c\
		./parsing/ft_strcmp.c\
		./parsing/ft_strncmp.c\
		./parsing/main.c\
		./parsing/ft_calloc.c\
		./parsing/ft_split.c\
		./parsing/ft_bzero.c\
		./parsing/ft_lst.c\
		./parsing/parssing.c\
		./parsing/parssing0.c\
		./parsing/parssing1.c\
		./parsing/is_empty.c\
		./parsing/ft_strtrim.c\
		./parsing/util.c\
		./parsing/env.c\
		./parsing/echo.c\
		./execution/parsing_pipex.c\
		./execution/ft_strjoinn.c\
		./execution/ft_split.c\
		./execution/ft_str.c\
		./execution/get_next_line_utils.c\
		./execution/get_next_line.c\
		./execution/pwd.c\
		./execution/ft_lstsize_bonus.c\
		./execution/pipex_bonus.c

OBJ = $(SRC:.c=.o)

INCLUDE1 = ex_minishell.h
INCLUDE2 = pr_minishell.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ -L $(READLINE_L) -lreadline 

%.o: %.c
	$(CC) $(FLAGS) -I $(READLINE_I) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean