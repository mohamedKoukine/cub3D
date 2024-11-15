NAME = cub3D

B_NAME = cub3D_B

CC = cc 

FLAGS = -Wall -Wextra -Werror -Imlx -fsanitize=address -g

SRC = ./mandatory/cub3D.c ./mandatory/get_next_line.c ./mandatory/get_next_line_utils.c\
		./mandatory/ft_strncmp.c ./mandatory/ft_strcmp.c ./mandatory/map_parc.c\
		./mandatory/draw.c ./mandatory/ft_strtrim.c ./mandatory/ft_atoi.c\
		./mandatory/main.c ./mandatory/utils1.c ./mandatory/utils2.c\
		./mandatory/utils3.c ./mandatory/utils4.c ./mandatory/utils5.c\
		./mandatory/utils6.c ./mandatory/parsing1.c ./mandatory/ft_split.c

B_SRC = ./bonus/cub3D.c ./bonus/get_next_line.c ./bonus/get_next_line_utils.c\
		./bonus/ft_strncmp.c ./bonus/ft_strcmp.c ./bonus/map_parc.c\
		./bonus/draw.c ./bonus/ft_strtrim.c ./bonus/ft_atoi.c\
		./bonus/main.c ./bonus/utils1.c ./bonus/utils2.c\
		./bonus/utils3.c ./bonus/utils4.c ./bonus/utils5.c\
		./bonus/utils6.c ./bonus/parsing1.c ./bonus/ft_split.c ./bonus/mini_map.c

OBJ = $(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

INCLUDE1 = ./mandatory/cub3D.h

INCLUDE2 = ./bonus/cub3D.h

INCLUDE3 = ./MLX42/MLX42.h

MLX42 = ./MLX42/libmlx42.a

all: $(NAME)

bonus: $(B_NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLX42)  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit -o $@

$(B_NAME): $(B_OBJ)
	$(CC) $(FLAGS) $(B_OBJ) $(MLX42)  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit -o $@

%.o: %.c $(INCLUDE1) 
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(B_OBJ)

fclean: clean
	rm -rf $(NAME) $(B_NAME)

re: fclean all

.PHONY: clean