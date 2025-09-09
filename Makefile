# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 20:48:10 by fmesa-or          #+#    #+#              #
#    Updated: 2025/09/09 14:02:34 by fmesa-or         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#Name
NAME		:= cub3D

#Compile
CC			:= cc

#Flags
CFLAGS		:= -Wall -Wextra -Werror -g

#MLX42
#MLX42_DIR	:= ./lib/MLX42
#MLX42		:= $(MLX42_DIR)/build/libmlx42.a
#MLX42_FLAGS	:= -ldl -lglfw -pthread -lm

#Clean
CLEAN		:= rm -Rf

#Sources
SRCS_DIR	:= src
SRCS		:= $(shell find $(SRCS_DIR) -name "*.c")

#Objects
OBJS_DIR	:= obj
OBJS		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

#Headers
#HEADERS		:= -I ./include -I $(MLX42_DIR)/include
HEADERS		:= -I ./include

#Colors
COLOR_INFO = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m
COLOR_PROGRESS = \033[1;35m
COLOR_HEADER = \033[1;35m

# Progress bar variables
TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE := 0
BAR_LENGTH := 30

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

all: header $(NAME)

header:
	@echo "$$HEADER_ART"

#$(NAME): $(MLX42) $(OBJS)
#	@printf "\n$(COLOR_INFO)Building executable...$(COLOR_RESET)"; \
#	$(CC) $(OBJS) $(MLX42) $(HEADERS) $(MLX42_FLAGS) -o $(NAME) -lreadline; \
#	printf "\r\033[K$(COLOR_SUCCESS)✅ $(NAME) is ready!$(COLOR_RESET)\n"
$(NAME): $(OBJS)
	@printf "\n$(COLOR_INFO)Building executable...$(COLOR_RESET)"; \
	$(CC) $(OBJS) $(HEADERS) -o $(NAME) -lreadline; \
	printf "\r\033[K$(COLOR_SUCCESS)✅ $(NAME) is ready!$(COLOR_RESET)\n"



$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@printf "$(COLOR_INFO) Building CUB3D $(COLOR_RESET) [                    ] 0%%"
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@$(eval PROGRESS=$(shell echo $$(($(CURRENT_FILE)*$(BAR_LENGTH)/$(TOTAL_FILES)))))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT_FILE)*100/$(TOTAL_FILES)))))
	@printf "\r$(COLOR_INFO) Building CUB3D: [$(COLOR_PROGRESS)"
	@for i in $$(seq 1 $(PROGRESS)); do printf "█"; done
	@for i in $$(seq 1 $$(($(BAR_LENGTH)-$(PROGRESS)))); do printf " "; done
	@printf "$(COLOR_INFO)] %3d%%$(COLOR_RESET)" $(PERCENT)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

#$(MLX42):
#	@printf "$(COLOR_INFO) Building MLX: [                    ] 0/2$(COLOR_RESET)"
#	@cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR) -DDEBUG=OFF > /dev/null 2>&1
#	@printf "\r$(COLOR_INFO) Building MLX: [████████            ] 1/2$(COLOR_RESET)"
#	@cmake --build $(MLX42_DIR)/build -j4 > /dev/null 2>&1
#	@printf "\r$(COLOR_INFO) Building MLX: [████████████████████] 2/2$(COLOR_RESET)\n"


clean:
	@printf "$(COLOR_INFO)Cleaning object files...$(COLOR_RESET)"
	@$(CLEAN) $(OBJS_DIR)
	@printf "\r$(COLOR_SUCCESS)✅ Object files cleaned successfully!$(COLOR_RESET)\n"

#clean_mlx:
#	@printf "$(COLOR_INFO)Cleaning MLX42...$(COLOR_RESET)"
#	@rm -rf $(MLX42_DIR)/build
#	@printf "\r$(COLOR_SUCCESS)✅ MLX42 cleaned successfully!$(COLOR_RESET)\n"

#fclean: clean clean_mlx
fclean: clean
	@printf "$(COLOR_INFO)Deleting $(NAME)...$(COLOR_RESET)"
	@$(CLEAN) $(NAME)
	@printf "\r$(COLOR_SUCCESS)✅ $(NAME) deleted successfully!$(COLOR_RESET)\n"

re: fclean all

#.PHONY: all clean fclean re header clean_mlx
.PHONY: all clean fclean re header