NAME = philo

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread -g

SRC =	main.c \
		ft_itoa.c \
		ft_calloc_bzero.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I ./

./%.o: ./%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

clean:
	@echo $(OBJ)
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: all fclean