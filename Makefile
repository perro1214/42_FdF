NAME = fdf

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

MLX_PATH = ./minilibx-linux
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -lmlx -lX11 -lXext -lm

SRCS = srcs/main.c \
       srcs/parse_map.c \
       srcs/draw.c \
       srcs/draw_utils.c \
       srcs/controls.c \
       srcs/memory.c \
       srcs/color.c \
       srcs/utils.c \
	   srcs/parse_map_utils.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes -I$(LIBFT_PATH) -I$(MLX_PATH)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_PATH) -lft -L$(MLX_PATH) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX):
	make -C $(MLX_PATH)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re