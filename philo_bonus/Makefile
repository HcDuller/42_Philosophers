NAME = philo_bonus

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread

RAW =	main_bonus.c \
		eval_input_bonus.c \
		ft_calloc_bzero_bonus.c \
		parse_params_bonus.c \
		semaphores_bonus.c \
		table_management_bonus.c \
		fork_management_bonus.c \
		get_elapsed_time_bonus.c \
		print_msg_bonus.c \
		dinner_management_bonus.c \
		actions_bonus.c \
		simulation_management_bonus.c \
		check_hungry_state_bonus.c \
		try_wait_bonus.c


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