
# Compilador y flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude -Ilib/MLX42/include -Iget_next_line -Ift_printf



# Paths
MLX_DIR     = lib/MLX42
GNL_DIR     = get_next_line
PRINTF_DIR  = ft_printf
SRC_DIR     = src

# Archivos fuente por módulo
SRCS_MAIN   = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/render_map.c \
	$(SRC_DIR)/moves.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/parsing.c \
	$(SRC_DIR)/bonus.c \
	$(SRC_DIR)/validate_playability.c \
	$(SRC_DIR)/read_map.c 
SRCS_GNL    = \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c 
SRCS_PRINTF = \
	$(PRINTF_DIR)/ft_printf.c \
	$(PRINTF_DIR)/ft_print_char.c \
	$(PRINTF_DIR)/ft_print_hex.c \
	$(PRINTF_DIR)/ft_print_int.c \
	$(PRINTF_DIR)/ft_print_percent.c \
	$(PRINTF_DIR)/ft_print_pointer.c \
	$(PRINTF_DIR)/ft_print_string.c \
	$(PRINTF_DIR)/ft_print_uint.c \
	$(PRINTF_DIR)/ft_putnbr_fd.c \
	$(PRINTF_DIR)/ft_putchar_fd.c

# Archivos finales
SRC = $(SRCS_MAIN) $(SRCS_GNL) $(SRCS_PRINTF)
OBJ = $(SRC:.c=.o)

# Ejecutable
NAME = so_long

# Librerías
MLX_FLAGS = -Llib/MLX42 -lmlx42 -ldl -lglfw -pthread



# **************************************************************************** #
#                                   REGLAS                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
