NAME			:= cub3d

CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror -g

MAKEFLAGS		:=	--no-print-directory

#================================COUNT============================#

NB_COMP		:=	1

ifndef RECURSION
TO_COMP 	:=	$(shell make RECURSION=1 -n | grep Compiling | wc -l)
else
TO_COMP		:=	1
endif

PERCENT		:= 0

#==============================COLORS==============================#
NOC			= \e[0m
BOLD		= \e[1m
DIM			= \e[2m
UNDERLINE	= \e[4m
BLACK		= \e[1;30m
RED			= \e[1m\e[38;5;196m
GREEN		= \e[1m\e[38;5;76m
YELLOW		= \e[1m\e[38;5;220m
BLUE		= \e[1m\e[38;5;33m
PURPLE		= \e[1;35m
CYAN		= \e[1;36m
WHITE		= \e[1;37m

BLACK_BG 	= \033[0;40m
RED_BG 		= \033[0;41m
GREEN_BG 	= \033[0;42m
YELLOW_BG	= \033[0;43m
BLUE_BG 	= \033[0;44m
MAGENTA_BG	= \033[0;45m
CYAN_BG 	= \033[0;46m
WHITE_BG 	= \033[0;47m
RESET_BG	= \033[0m

#================================DIRS============================#

SRC_DIR				:=  srcs
INCLUDES_DIR		:=	includes
BUILD_DIR			:=	.build
MLX_DIR				:=	mlx
LIBFT_DIR			:=	libft

#==============================SOURCES===========================#

# no duplicates

SRCS_FILES		:=	test.c\
					draw/shapes.c\
					minimap/minimap.c\
					mlx_init.c\
					clean.c\
					keyhooks.c\

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRCS_FILES))

#==============================MLX==============================#
LIBFT			:= $(LIBFT_DIR)/libft
LIBFTFLAGS		:= -L$(LIBFT_DIR) -l:libft.a

#==============================MLX==============================#

MLX				:= ${MLX_DIR}/libmlx_Linux.a
MLXFLAGS		:= -L${MLX_DIR} -lmlx_Linux -lXext -lX11 -lm -lz

#=============================OBJECTS===========================#

OBJS			:= ${SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o}

#===============================DEPS=============================#

DEPS			:= ${SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.d}

#=============================INCLUDES===========================#

INC				:= -I$(INCLUDES_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)

#================================DIR=============================#

DIRS			:=	$(sort $(shell dirname $(OBJS))) #no duplicates

#===============================RULES============================#

all: $(NAME)

$(DIRS):
	@mkdir -p $@

$(DIRS_BONUS):
	@mkdir -p $@

$(MLX_DIR):
	wget https://cdn.intra.42.fr/document/document/30137/minilibx-linux.tgz)
	tar -xzvf minilibx-linux.tgz
	mv minilibx-linux $(MLX_DIR)
	rm minilibx-linux

$(MLX): $(MLX_DIR)
	@echo "$(BLUE)Compiling MLX...$(NOC)"
	@make -C $(MLX_DIR)

$(LIBFT_DIR):
	@git clone https://github.com/codastream/libft.git $(LIBFT_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	@echo "\n$(GREEN)Create binaries$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFTFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS) $(LIBFT_DIR)
	@mkdir -p $(BUILD_DIR)
	@if [ $(NB_COMP) -eq 1 ]; then echo "$(BOLD)Compilation of source files :$(NOC)";fi
	$(eval PERCENT=$(shell expr $(NB_COMP)00 "/" $(TO_COMP)))
	@if [ $(PERCENT) -le 30 ]; then echo -n "$(RED)"; elif [ $(PERCENT) -le 66 ]; then echo -n "$(YELLOW)"; elif [ $(PERCENT) -gt 66 ]; then echo -n "$(GREEN)"; fi
	@echo -n "\r"; for i in $$(seq 1 $$(/usr/bin/tput cols)); do echo -n " "; done
	@echo -n "\r"; for i in $$(seq 1 25); do if [ $$(expr $$i "*" 4) -le $(PERCENT) ]; then echo -n "█"; else echo -n " "; fi; done; echo -n "";
	@printf " $(NB_COMP)/$(TO_COMP) - Compiling $<"
	@echo -n "$(NOC)"
	$(CC) $(CFLAGS) $(INC) -O3 -c $< -o $@
	$(eval NB_COMP=$(shell expr $(NB_COMP) + 1))

clean:
	@echo "$(RED)Remove objects$(NOC)"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo "$(RED)Remove binary$(NOC)"
	@rm -f $(NAME)
	@rm -rf $(LIBFT_DIR)

re: fclean
	@make

.PHONY: all clean fclean re

-include $(DEPS)
