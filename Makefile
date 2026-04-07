NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c init.c routine.c monitor.c utils.c actions.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all
