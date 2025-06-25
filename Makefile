
# 🛠️ Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I include -I lib/MLX42/include -I get_next_line -I ft_printf

# 🧱 Object folders
OBJ_DIR         = obj
OBJ_SUBDIRS     = $(OBJ_DIR)/src $(OBJ_DIR)/utils

# 📁 Paths
SRC_DIR         = src
GNL_DIR         = get_next_line
PRINTF_DIR      = ft_printf
MLX_DIR         = lib/MLX42

# 🧩 Source files
SRC_FILES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/render_map.c \
	$(SRC_DIR)/moves.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/libft_utils.c \
	$(SRC_DIR)/parsing.c \
	$(SRC_DIR)/bonus.c \
	$(SRC_DIR)/validate_playability.c \
	$(SRC_DIR)/validate_utils.c \
	$(SRC_DIR)/read_map.c

UTILS_FILES = \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c \
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

# 🧱 Object files
OBJ_FILES_SRC   = $(patsubst %.c, $(OBJ_DIR)/src/%.o, $(notdir $(SRC_FILES)))
OBJ_FILES_UTILS = $(patsubst %.c, $(OBJ_DIR)/utils/%.o, $(notdir $(UTILS_FILES)))
OBJS            = $(OBJ_FILES_SRC) $(OBJ_FILES_UTILS)

# 🕹️ Executable
NAME        = so_long
MLX_FLAGS   = -L$(MLX_DIR) -lmlx42 -ldl -lglfw -pthread

# 🚀 Default rule
all: check_changes $(NAME)

# ℹ️ Compilation banner
check_changes:
	@if ! $(MAKE) --question $(NAME); then \
		echo "========================="; \
		echo " 🕹️  Building SO_LONG"; \
		echo " 🔧  Using MLX42"; \
		echo " 🗓️  $(shell date +'%d-%m-%Y %H:%M:%S')"; \
		echo "========================="; \
	else \
		echo "✅ No changes detected. Everything is up to date."; \
	fi

# 🔨 Linking
$(NAME): $(OBJ_DIR) $(OBJS)
	@$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)
	@echo "✅ Compilation finished: $(NAME)"

# 📁 Create object folder structure
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/src $(OBJ_DIR)/utils

# 🔧 Compile src files
$(OBJ_DIR)/src/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 🔧 Compile utils files (gnl and printf)
$(OBJ_DIR)/utils/%.o: $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/utils/%.o: $(PRINTF_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 🧽 Cleanup
clean:
	@echo "🧹 Removing object files..."
	@rm -f $(OBJS)
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "✅ Objects cleaned."

fclean: clean
	@echo "🗑️ Removing executable and object folders..."
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "✅ Full clean completed."

re: fclean all

.PHONY: all clean fclean re check_changes