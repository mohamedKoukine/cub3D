NAME = cub3D

CC = cc 

FLAGS = -Wall -Wextra -Werror -Imlx #-fsanitize=address -g

SRC = cub3D.c\
		get_next_line.c\
		get_next_line_utils.c\
		ft_strncmp.c\
		ft_strcmp.c\
		map_parc.c\
		draw.c\
		ft_strtrim.c\
		ft_atoi.c\
		main.c\
		utils1.c\
		utils2.c\
		utils3.c\
		utils4.c\
		utils5.c\
		utils6.c\
		parsing1.c\
		ft_split.c

OBJ = $(SRC:.c=.o)

INCLUDE1 = cub3D.h
INCLUDE2 = ./MLX42/MLX42.h
MLX42 = ./MLX42/libmlx42.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLX42)  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit -o $@

%.o: %.c $(INCLUDE1) $(INCLUDE2)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: clean