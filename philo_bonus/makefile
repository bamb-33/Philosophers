CC = cc
CFLAGS = 

SRC = main.c ft_atoi.c philos_life.c meals_time.c get_current_time.c ft_lstadd_back.c ft_lstclear.c ft_lstnew.c init.c processes.c wrappers.c lock_functions.c wrappers_v2.c

OBJ = $(SRC:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -lpthread -fsanitize=thread -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re