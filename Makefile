# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 20:48:10 by fmesa-or          #+#    #+#              #
#    Updated: 2025/10/22 20:25:21 by fmesa-or         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#Name
NAME		:= cub3D

#Compile
CC			:= cc

#Flags
CFLAGS		:= -Wall -Wextra -Werror -g

#MLX42
MLX42_DIR	:= ./lib/MLX42
MLX42		:= $(MLX42_DIR)/build/libmlx42.a
MLX42_FLAGS	:= -ldl -lglfw -pthread -lm

#Clean
CLEAN		:= rm -Rf

#Sources
SRCS_DIR	:= src
SRCS		:= $(SRCS_DIR)/cub3d.c \
			   $(SRCS_DIR)/execute/draw/picasso.c \
			   $(SRCS_DIR)/execute/movement/key_hooks.c \
			   $(SRCS_DIR)/execute/movement/move_functions.c \
			   $(SRCS_DIR)/execute/movement/move_hooks.c \
			   $(SRCS_DIR)/execute/movement/move_utils2.c \
			   $(SRCS_DIR)/execute/movement/move_utils.c \
			   $(SRCS_DIR)/execute/player/player.c \
			   $(SRCS_DIR)/execute/ray/raycasting.c \
			   $(SRCS_DIR)/libft/ft_isspace.c \
			   $(SRCS_DIR)/libft/ft_sfree_split.c \
			   $(SRCS_DIR)/libft/ft_split.c \
			   $(SRCS_DIR)/libft/ft_strchr.c \
			   $(SRCS_DIR)/libft/ft_strlcpy.c \
			   $(SRCS_DIR)/libft/ft_strlen.c \
			   $(SRCS_DIR)/libft/ft_strncmp.c \
			   $(SRCS_DIR)/mem/mem_man.c \
			   $(SRCS_DIR)/mem/mem_tabl2.c \
			   $(SRCS_DIR)/mem/mem_tabl.c \
			   $(SRCS_DIR)/mem/mem_utils.c \
			   $(SRCS_DIR)/parse/error.c \
			   $(SRCS_DIR)/parse/filer/check_file.c \
			   $(SRCS_DIR)/parse/filer/readfile.c \
			   $(SRCS_DIR)/parse/gnl/gnl.c \
			   $(SRCS_DIR)/parse/gnl/gnl_utils.c \
			   $(SRCS_DIR)/parse/maper/checkmap.c \
			   $(SRCS_DIR)/parse/maper/fillmap.c \
			   $(SRCS_DIR)/parse/maper/get_colors.c \
			   $(SRCS_DIR)/parse/maper/get_hex_colors.c \
			   $(SRCS_DIR)/parse/maper/get_textures.c \
			   $(SRCS_DIR)/parse/maper/get_textures_utils.c \
			   $(SRCS_DIR)/parse/maper/init_textures.c \
			   $(SRCS_DIR)/parse/maper/load_textures.c \
			   $(SRCS_DIR)/parse/maper/parse_map.c \
			   $(SRCS_DIR)/parse/whole_parse.c

#Objects
OBJS_DIR	:= obj
OBJS		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

#Headers
HEADERS		:= -I ./include -I $(MLX42_DIR)/include

#Colors
COLOR_INFO = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m
COLOR_PROGRESS = \033[1;35m
COLOR_HEADER = \033[1;35m

# Progress bar variables
TOTAL_FILES := $(words $(SRCS))
BAR_LENGTH := 30
COUNTER_FILE := .build_counter

# Header art
define HEADER_ART
$(COLOR_HEADER)
   ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ 
  ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
  ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
  ██║     ██║   ██║██╔══██╗ ╚═══██║██║  ██║
  ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
   ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ 
$(COLOR_RESET)
endef
export HEADER_ART

all: $(NAME)

header:
	@echo "$$HEADER_ART"

$(NAME): $(MLX42) $(OBJS)
	@printf "\n$(COLOR_INFO)Building executable...$(COLOR_RESET)"; \
	$(CC) $(OBJS) $(MLX42) $(HEADERS) $(MLX42_FLAGS) -o $(NAME) -lreadline; \
	printf "\r\033[K$(COLOR_SUCCESS)✅ $(NAME) is ready!$(COLOR_RESET)\n"; \
	rm -f $(COUNTER_FILE)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@if [ ! -f $(COUNTER_FILE) ]; then echo "0" > $(COUNTER_FILE); fi
	@CURRENT=$$(cat $(COUNTER_FILE)); \
	CURRENT=$$((CURRENT + 1)); \
	echo $$CURRENT > $(COUNTER_FILE); \
	PROGRESS=$$((CURRENT * $(BAR_LENGTH) / $(TOTAL_FILES))); \
	PERCENT=$$((CURRENT * 100 / $(TOTAL_FILES))); \
	printf "\r$(COLOR_INFO) Building CUB3D: [$(COLOR_PROGRESS)"; \
	for i in $$(seq 1 $$PROGRESS); do printf "█"; done; \
	for i in $$(seq 1 $$(($(BAR_LENGTH) - PROGRESS))); do printf " "; done; \
	printf "$(COLOR_INFO)] %3d%%$(COLOR_RESET)" $$PERCENT
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(MLX42):
	@printf "$(COLOR_INFO) Building MLX: [                    ] 0/2$(COLOR_RESET)"
	@cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR) -DDEBUG=OFF > /dev/null 2>&1
	@printf "\r$(COLOR_INFO) Building MLX: [████████            ] 1/2$(COLOR_RESET)"
	@cmake --build $(MLX42_DIR)/build -j4 > /dev/null 2>&1
	@printf "\r$(COLOR_INFO) Building MLX: [████████████████████] 2/2$(COLOR_RESET)\n"


clean:
	@printf "$(COLOR_INFO)Cleaning object files...$(COLOR_RESET)"
	@$(CLEAN) $(OBJS_DIR)
	@rm -f $(COUNTER_FILE)
	@printf "\r$(COLOR_SUCCESS)✅ Object files cleaned successfully!$(COLOR_RESET)\n"

clean_mlx:
	@printf "$(COLOR_INFO)Cleaning MLX42...$(COLOR_RESET)"
	@rm -rf $(MLX42_DIR)/build
	@printf "\r$(COLOR_SUCCESS)✅ MLX42 cleaned successfully!$(COLOR_RESET)\n"

fclean: clean clean_mlx
	@printf "$(COLOR_INFO)Deleting $(NAME)...$(COLOR_RESET)"
	@$(CLEAN) $(NAME)
	@rm -f $(COUNTER_FILE)
	@printf "\r$(COLOR_SUCCESS)✅ $(NAME) deleted successfully!$(COLOR_RESET)\n"

re: fclean all

.PHONY: all clean fclean re header clean_mlx