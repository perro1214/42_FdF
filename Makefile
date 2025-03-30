NAME = fdf

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# ライブラリへのパス
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

GET_NEXT_LINE_PATH = ./get_next_line/
GET_NEXT_LINE = $(GET_NEXT_LINE_PATH)/get_next_line.a

MLX_PATH = ./minilibx-linux
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -lmlx -lX11 -lXext -lm

# 必須のソースファイル
SRCS = srcs/main.c \
       srcs/parse_map.c \
       srcs/draw.c \
       srcs/draw_utils.c \
       srcs/controls.c \
       srcs/memory.c \
       srcs/color.c \
       srcs/utils.c \
	   srcs/parse_map_utils.c

# オブジェクトファイル
OBJS = $(SRCS:.c=.o)

# ヘッダーファイル
INCLUDES = -I./includes -I$(LIBFT_PATH) -I$(MLX_PATH) -I$(GET_NEXT_LINE_PATH)

# コンパイルとリンク
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