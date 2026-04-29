NAME = parsing_test
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c \
	../srcs/parsing/parsing.c \
	../srcs/parsing/checking_file.c \
	../srcs/parsing/building_struct.c \
	../srcs/parsing/cubfile_check.c \
	../srcs/parsing/flood_fill.c \
	../srcs/parsing/map_parsing.c \
	../srcs/parsing/validating_coordinates.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I../includes -I$(LIBFT_DIR)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re