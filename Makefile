CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -Isources -I/usr/X11/include -Ilib/mlx_linux

LDFLAGS = -L/usr/X11/lib -lX11 -lXext -Llib/mlx_linux -lmlx -Llib/libft -lft -lm

SRC_DIR = src

OBJ_DIR = obj

SRC =	main.c \
		initialise.c \
		parser/parse.c \
		parser/parse_utils.c \
		parser/parse_strconversions.c \
		parser/new_element.c \
		parser/lights_camera.c \
		parser/shapes.c \
		parser/file.c \
		miniRT.c \
		math/math_utils.c \
		colour/colour.c \
		input_handler.c \
		error.c \
		free/free.c \
		free/free_lights_camera.c \
		free/free_shapes.c \
		quit.c \
		utils.c \
		printer/printer.c

OBJ =	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

MLX_DIR = lib/mlx_linux

LIBFT_DIR = lib/libft

LIB = $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a

CFLAGS +=	-I./lib \
			-I./src/colour \
			-I./src/free \
			-I./src/math \
			-I./src/parser \
			-I./src/printer

NAME = miniRT

all: $(NAME)

$(NAME): $(DEP) $(OBJ)
	@make -sC $(MLX_DIR)
	@make bonus -sC $(LIBFT_DIR)
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
