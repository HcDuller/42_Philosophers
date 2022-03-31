NAME = philo

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread

RAW =	main.c \
		ft_calloc_bzero.c \
		actions.c \
		start_philosophers.c \
		philosophers_are_dinning.c \
		eval_input.c \
		phi_thread.c \
		ft_strlen.c \
		ft_strjoin.c \
		time_management.c \
		table_management.c \
		dinner_is_over.c \
		try_lock.c \
		pick_forks.c \
		release_forks.c \
		print_msg.c \
		get_next_in_line.c \
		watcher.c

SRC_DIR	= src
OBJ_DIR	= obj

SRC =	$(addprefix $(SRC_DIR)/,$(RAW))
OBJ =	$(addprefix $(OBJ_DIR)/,$(RAW:.c=.o))


.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

clean:
	rm -rfd $(OBJ)

fclean: clean
	rm -rfd $(NAME)

re: fclean all