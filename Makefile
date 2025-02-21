CC = cc

CFLAGS = -Wall -Wextra -Werror -g -Isources -I/usr/X11/include -Ilib/mlx_linux

LDFLAGS = -L/usr/X11/lib -lX11 -lXext -Llib/mlx_linux -lmlx -Llib/libft -lft -lm

SRC_DIR = src

OBJ_DIR = obj

SRC =	main.c \
		initialise.c \
		parser/parse.c parser/parse_utils.c parser/parse_strconversions.c \
		parser/new_element.c \
		parser/lights_camera.c parser/shapes.c parser/shapes_bonus.c parser/shapes_utils.c \
		parser/file.c \
		miniRT.c \
		raytrace/draw_scene.c raytrace/draw_pixel.c raytrace/draw_utils.c \
		raytrace/msaa.c raytrace/msaa_colour.c \
		raytrace/bounce.c \
		lighting/lighting.c lighting/lighting_utils.c lighting/normal.c \
		intersect/intersect.c intersect/intersection_checks.c \
		intersect/closest_shape.c intersect/closest_shape_bonus.c \
		intersect/intersect_plane.c intersect/intersect_sphere.c intersect/intersect_cylinder.c \
		intersect/intersect_cone.c intersect/intersect_triangle.c \
		intersect/transform.c \
		intersect/intersect_cylinder_utils.c \
		maths/vector.c maths/vector_basic.c maths/point.c \
		maths/matrix.c maths/matrix_utils.c \
		colour/colour.c \
		input_handler.c \
		error.c \
		free/free.c free/free_lights_camera.c free/free_shapes.c \
		quit.c \
		utils.c \
		bonus/draw_multithreaded.c \
		bonus/multithread_utils.c


TOTAL_FILES := $(words $(SRC))
CURR_FILE = 0
GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
RESET = \033[0m


OBJ =	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

MLX_DIR = lib/mlx_linux

LIBFT_DIR = lib/libft

LIB = $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a

CFLAGS +=	-I./lib \
			-I./src/parser \
			-I./src/raytrace \
			-I./src/lighting \
			-I./src/maths \
			-I./src/intersect \
			-I./src/colour \
			-I./src/free \
			-I./src/printer

NAME = miniRT

all: $(NAME)

$(NAME): $(DEP) $(OBJ)
	@echo "\n$(GREEN)Building libraries...$(RESET)"
	@make -sC $(MLX_DIR)
	@make bonus -sC $(LIBFT_DIR)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Build complete!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval CURR_FILE=$(shell echo $$(($(CURR_FILE)+1))))
	@printf "$(GREEN)Compiling [%3d%%] %-50s$(RESET)\r" $(shell echo $$(($(CURR_FILE)*100/$(TOTAL_FILES)))) "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(YELLOW)Cleaning MLX library...$(RESET)"
	@make clean -sC $(MLX_DIR)
	@echo "$(YELLOW)Cleaning LibFT...$(RESET)"
	@make fclean -sC $(LIBFT_DIR)
	@echo "$(GREEN)Clean complete!$(RESET)"

fclean: 
	@echo "$(RED)Deep cleaning project...$(RESET)"
	@$(MAKE) --no-print-directory clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)Project fully cleaned!$(RESET)"

re: fclean all

bonus: CFLAGS += -DBONUS
bonus: all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus
