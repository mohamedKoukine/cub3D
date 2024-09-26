NAME = cub3D

CC = cc 

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRC = cub3D.c\
		get_next_line.c\
		get_next_line_utils.c\
		ft_strncmp.c\
		ft_strcmp.c\
		map_parc.c\
		ft_split.c

OBJ = $(SRC:.c=.o)

INCLUDE1 = cub3D.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ 

%.o: %.c $(INCLUDE1)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: clean