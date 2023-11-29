CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -Isources -I/usr/X11/include -Ilib/mlx_linux

LDFLAGS = -L/usr/X11/lib -lX11 -lXext -Llib/mlx_linux -lmlx -Llib/libft -lft

SRC_DIR = src

OBJ_DIR = obj

SRC =	main.c \
		initialise.c \
		parser/parse.c \
		parser/file.c \
		miniRT.c \
		input_handler.c \
		error.c \
		quit.c

OBJ =	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

MLX_DIR = lib/mlx_linux

LIBFT_DIR = lib/libft

LIB = $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a

NAME = miniRT

all: $(NAME)

$(NAME): $(DEP) $(OBJ)
	@make -sC $(MLX_DIR)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm $(OBJ)
	@make clean -sC $(MLX_DIR)
	@make fclean -sC $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
