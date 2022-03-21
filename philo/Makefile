NAME = philo

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread -g

SRC =	main.c \
		ft_itoa.c \
		ft_calloc_bzero.c \
		ft_strlen.c \
		ft_strjoin.c \
		time_management.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I ./

./%.o: ./%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

clean:
	rm -rfd $(OBJ)

fclean: clean
	rm -rfd $(NAME)

re: fclean all