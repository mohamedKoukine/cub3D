NAME = minishell

CC = cc 

FLAGS = -Wall -Wextra -Werror

SRC = ft_strlen.c\
		ft_strcmp.c\
		ft_strncmp.c\
		main.c\
		ft_calloc.c\
		ft_split.c\
		ft_bzero.c\
		ft_lstadd_back_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstnew_bonus.c\
		ft_strdup.c\
		parssing.c\
		parssing0.c\
		parssing1.c\
		is_empty.c\
		ft_strtrim.c\
		util.c\
		env.c

OBJ = $(SRC:.c=.o)

INCLUDE = minishell.h

all: $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@ -fsanitize=address -g

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(OBJ) -lreadline -o $(NAME) -fsanitize=address -g

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean