CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = philo

SRC = src/main.c src/parse.c src/routine.c src/init.c src/thread.c src/utils.c

HEADER = -I ./

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
		$(CC) $(CFLAGS) -pthread -o $@ -c $< $(HEADER)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJ) $(HEADER)

clean: 
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re