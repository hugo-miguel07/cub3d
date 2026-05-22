NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRCS = srcs/main.c \
		srcs/exit.c \
		srcs/execution/cleanup.c \
		srcs/execution/game_utils.c \
		srcs/execution/frame_init.c \
		srcs/execution/zbuffer_init.c \
		srcs/execution/game_loop.c \
		srcs/execution/drawer.c \
		srcs/execution/drawer_utils.c \
		srcs/execution/drawmap.c \
		srcs/execution/raycasting.c \
		srcs/execution/raycasting_utils.c \
		srcs/execution/textures.c \
		srcs/execution/exec.c \
		srcs/execution/mini_map.c \
		srcs/execution/player_moves.c \
		srcs/parsing/building_struct.c \
		srcs/parsing/checking_file.c \
		srcs/parsing/cubfile_check.c \
		srcs/parsing/flood_fill.c \
		srcs/parsing/map_parsing.c \
		srcs/parsing/parsing.c \
		srcs/parsing/validating_coordinates.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lXext -lX11 -lm -o $(NAME)

clean:
	@rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	@echo 'objetos limpos'

fclean : clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY: all clean fclean re bonus
