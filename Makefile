# Program Name
NAME = fdf

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS += -g # Optional: for debugging with valgrind/lldb/gdb

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft
GNL_DIR = get_next_line
MLX_DIR = mlx # Adjust if your mlx location is different

# Libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_LIB = $(GNL_DIR)/libgnl.a
MLX_LIB = $(MLX_DIR)/libmlx.a

# MiniLibX Flags (macOS Example - MODIFY FOR YOUR SYSTEM)
# Check the MiniLibX documentation/Makefile for your OS!
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd # macOS
# MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd # Linux Example (check!)

# Math Library
LDFLAGS = -lm $(MLXFLAGS) # Link math library (-lm) and MiniLibX

# Source Files
SRCS_FILES = main.c parse.c parse_utils.c init.c draw.c hooks.c utils.c cleanup.c utils2.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))

# Object Files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Include Paths
INC = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR) # Include mlx dir

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL_LIB) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL_LIB):
	$(MAKE) -C $(GNL_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)



# Phony Rules
.PHONY: all clean fclean re libft norm bonus

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean
	rm -f $(NAME)

re: fclean all

libft:
	$(MAKE) -C $(LIBFT_DIR) all

norm:
	norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_DIR) # Check norm for src, include, libft

# Optional Bonus Rule (as per subject, even if not implemented now)
bonus: # Define bonus sources/objects if you were doing them
	# Example: $(MAKE) WITH_BONUS=1 all