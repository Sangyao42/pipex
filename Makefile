NAME := pipex
CC := gcc
CFLAGS := -Wall -Wextra -Werror
SRC_DIR := ./src/
OBJ_DIR := ./obj/
HEADER := -I ./include/ -I ./lib/Libft/
LIBFT := ./lib/Libft/
SRCS = pipex.c \
		processes.c \
		parser.c \
		error_handler.c
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all:
	@$(MAKE) $(NAME) -j

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) libft
	$(CC) $(CFLAGS) -L $(LIBFT) -lft $(OBJS) -o $(NAME)
	@echo "pipex is ready"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(HEADER) -c $^ -o $@

libft:
	@make -C $(LIBFT)

clean:
	rm -f $(OBJS)
	make fclean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.phony: all clean fclean re
