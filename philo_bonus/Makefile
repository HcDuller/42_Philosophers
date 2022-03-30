NAME = philo_bonus

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread -g

RAW =	main.c \
		eval_input.c \
		ft_calloc_bzero.c \
		parse_params.c \
		semaphores.c \
		table_management.c \
		fork_management.c \
		get_elapsed_time.c \
		print_msg.c \
		dinner_management.c \
		actions.c


SRC_DIR	= src
OBJ_DIR	= obj

SRC =	$(addprefix $(SRC_DIR)/,$(RAW))
OBJ =	$(addprefix $(OBJ_DIR)/,$(RAW:.c=.o))


.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I ./src/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./src/

clean:
	rm -rfd $(OBJ)

fclean: clean
	rm -rfd $(NAME)

re: fclean all

bonus: all