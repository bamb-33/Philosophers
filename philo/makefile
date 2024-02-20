CC = cc
CFLAGS = -Wall -Wextra -Werror -lpthread

SRC = main.c ft_atoi.c philos_life.c

OBJ = $(SRC:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re