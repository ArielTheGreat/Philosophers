SRC_DIR = srcs
OBJ_DIR = objs

SRCS = $(SRC_DIR)/initialize_file.c $(SRC_DIR)/main.c $(SRC_DIR)/monitor_functions.c \
        $(SRC_DIR)/philo_routine.c $(SRC_DIR)/utils.c $(SRC_DIR)/utils2.c \
		$(SRC_DIR)/philo_routine2.c $(SRC_DIR)/monitor_functions2.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean