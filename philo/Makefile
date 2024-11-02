NAME = philo

CC = cc

FLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c\
		ft_strlen.c\
		ft_split.c\
		pars.c\
		pars1.c\
		philo.c\
		philo1.c\
		ft_strtrim.c\
		ft_strdup.c\
		main.c

OBJ = $(SRC:.c=.o)

INCLUDE = philo.h

all: $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(INCLUDE)
	cc $(OBJ) $(FLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean