SRC_DIR = srcs
OBJ_DIR = objs

SRCS = $(SRC_DIR)/initialize_file.c $(SRC_DIR)/main.c $(SRC_DIR)/monitor_functions.c \
        $(SRC_DIR)/philo_routine.c $(SRC_DIR)/utils.c $(SRC_DIR)/program_destroy.c \
		$(SRC_DIR)/philo_actions.c $(SRC_DIR)/monitor_functions2.c $(SRC_DIR)/wait_functions.c \
		$(SRC_DIR)/output_functions.c $(SRC_DIR)/thread_creator.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = philo

# ANSI Color Codes
GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
CYAN = \033[1;36m
RESET = \033[0m

all: $(NAME)
	@echo "$(GREEN)✔ Build complete!$(RESET)"

$(NAME): $(OBJS)
	@echo "$(CYAN)🔨 Linking...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)🛠 Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@echo "$(CYAN)📁 Creating object directory...$(RESET)"
	mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)🚮 Removing executable...$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean