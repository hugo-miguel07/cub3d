NAME = exec_test
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c \
		../srcs/exit.c \
		../srcs/execution/cleanup.c \
		../srcs/execution/game_utils.c \
		../srcs/execution/frame_init.c \
		../srcs/execution/zbuffer_init.c \
		../srcs/execution/game_loop.c \
		../srcs/execution/drawer.c \
		../srcs/execution/drawer_utils.c \
		../srcs/execution/raycasting.c \
		../srcs/execution/player_moves.c \
		../srcs/execution/mini_map.c \
		../srcs/execution/exec.c \

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ../minilibx
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I../includes -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	@echo 'objetos limpos'

fclean : clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

hugo : fclean all
	@rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

.PHONY: all clean fclean re hugo