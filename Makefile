NAME			:= cub3D
BONUS_NAME		:= cub3D_bonus
CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror -g

MAKEFLAGS		:=	--no-print-directory

#================================COUNT============================#

NB_COMP		:=	1
ifndef RECURSION
TO_COMP		:=	$(shell make RECURSION=1 -n | grep Compiling | wc -l)
else
TO_COMP		:=	1
endif

NB_COMP_BONUS := 1
ifndef RECURSION
TO_COMP_BONUS := $(shell make bonus RECURSION=1 -n | grep Compiling | wc -l)
else
TO_COMP_BONUS := 1
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

BLACK_BG	= \033[0;40m
RED_BG		= \033[0;41m
GREEN_BG 	= \033[0;42m
YELLOW_BG	= \033[0;43m
BLUE_BG 	= \033[0;44m
MAGENTA_BG	= \033[0;45m
CYAN_BG 	= \033[0;46m
WHITE_BG 	= \033[0;47m
RESET_BG	= \033[0m

#================================DIRS============================#

MANDA_DIR		:= mandatory/srcs
BONUS_DIR		:= bonus/srcs
MLX_DIR			:=	mlx
LIBFT_DIR		:=	libft
BUILD_DIR		:=	.build_mandatory
BUILD_DIR_BONUS	:=	.build_bonus

#==============================SOURCES===========================#

MANDATORY_SRCS	:=	main.c\
					init.c \
					parse/check_close.c\
					parse/check_file.c\
					parse/check_player.c\
					parse/measure_map.c\
					parse/parse_cub.c\
					parse/parse_cub_utils.c\
					parse/parse_infos_check.c\
					parse/parse_infos_colors.c\
					parse/parse_infos_textures.c\
					parse/parse_infos.c\
					parse/parse_line.c\
					parse/parse_string_utils.c\
					parse/parse_color.c\
					parse/map_utils.c\
					draw/shapes.c\
					draw/basic_shapes.c\
					draw/walls.c\
					hooks/keyhooks.c\
					hooks/moves.c\
					hooks/rotate.c\
					map/cam.c\
					map/init.c\
					raycast/hit.c\
					raycast/init.c\
					raycast/raycast.c \
					raycast/textures.c \
					maths/angles.c \
					maths/matrix.c \
					maths/vectors.c \
					maths/vectors_ops.c \
					utils/clean_img.c \
					utils/clean.c \
					utils/color.c \
					utils/errors.c \
					utils/image.c\
					utils/mlx_utils.c \

BONUS_SRCS		:=	main_bonus.c\
					init_bonus.c\
					init_extra_bonus.c\
					parse/check_close_bonus.c\
					parse/check_file_bonus.c\
					parse/check_player_bonus.c\
					parse/measure_map_bonus.c\
					parse/parse_cub_bonus.c\
					parse/parse_cub_utils_bonus.c\
					parse/parse_infos_check_bonus.c\
					parse/parse_infos_colors_bonus.c\
					parse/parse_infos_textures_bonus.c\
					parse/parse_infos_bonus.c\
					parse/parse_line_bonus.c\
					parse/parse_string_utils_bonus.c\
					parse/parse_color_bonus.c\
					parse/map_utils_bonus.c\
					draw/basic_shapes_bonus.c\
					draw/door_bonus.c\
					draw/flag_bonus.c\
					draw/goal_bonus.c\
					draw/help_bonus.c\
					draw/shapes_bonus.c\
					draw/sprite_bonus.c\
					draw/sprite_size_bonus.c\
					draw/walls_bonus.c\
					hooks/keyhooks_bonus.c\
					hooks/moves_bonus.c\
					hooks/rotate_bonus.c\
					hooks/shoot_bonus.c\
					map/cam_bonus.c\
					map/init_bonus.c\
					map/init_tex_bonus.c\
					map/minimap_bonus.c\
					map/coord_bonus.c\
					maths/angles_bonus.c \
					maths/matrix_bonus.c \
					maths/vectors_ops_bonus.c \
					maths/vectors_bonus.c\
					raycast/hit_bonus.c\
					raycast/init_bonus.c\
					raycast/raycast_bonus.c \
					raycast/textures_bonus.c \
					utils/clean_img_bonus.c \
					utils/clean_bonus.c \
					utils/color_bonus.c \
					utils/errors_bonus.c \
					utils/image_bonus.c\
					utils/mlx_utils_bonus.c \
					utils/utils_bonus.c\
					utils/clean_extra_bonus.c\

SRCS			:= $(addprefix $(MANDA_DIR)/, $(MANDATORY_SRCS))
SRCS_BONUS		:= $(addprefix $(BONUS_DIR)/,$(BONUS_SRCS))
INCLUDES		:= mandatory/includes
INCLUDES_BONUS	:= bonus/includes


#==============================LIBFT=============================#

LIBFT			:= $(LIBFT_DIR)/libft.a
LIBFTFLAGS		:= -L$(LIBFT_DIR) -lft

#==============================MLX==============================#

MLX				:= ${MLX_DIR}/libmlx_Linux.a
MLXFLAGS		:= -L${MLX_DIR} -lmlx_Linux -lXext -lX11 -lm -lz

#=============================OBJECTS===========================#

OBJS			:= ${SRCS:$(MANDA_DIR)%.c=$(BUILD_DIR)%.o}
OBJS_BONUS		:= ${SRCS_BONUS:$(BONUS_DIR)%.c=$(BUILD_DIR_BONUS)%.o}

#===============================DEPS=============================#

DEPS			:= ${SRCS:$(MANDA_DIR)/%.c=$(BUILD_DIR)%.d}
DEPS_BONUS		:= ${SRCS_BONUS:$(BONUS_DIR)%.c=$(BUILD_DIR_BONUS)%.d}

#=============================INCLUDES===========================#

INC				:= -I$(INCLUDES) -I$(MLX_DIR) -I$(LIBFT_DIR)/includes
INC_BONUS		:= -I$(INCLUDES_BONUS) -I$(MLX_DIR) -I$(LIBFT_DIR)/includes

#================================DIR=============================#

DIRS			:=	$(sort $(shell dirname $(OBJS))) #no duplicates
DIRS_BONUS		:=	$(sort $(shell dirname $(OBJS_BONUS))) #no duplicates

#===============================RULES============================#


all: $(NAME)

bonus: $(BONUS_NAME)

$(DIRS) $(DIRS_BONUS):
	@echo $(DIRS)
	@mkdir -p $@

$(MLX): $(MLX_DIR)
	@echo "$(BLUE)Compiling MLX...$(NOC)"
	@make -C $(MLX_DIR)

$(LIBFT_DIR):
	@git clone https://github.com/codastream/libft.git $(LIBFT_DIR)

$(LIBFT): $(LIBFT_DIR)
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	@echo "\n$(GREEN)Create binaries$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(LIBFTFLAGS) -o $@

$(BONUS_NAME): $(OBJS_BONUS) $(MLX) $(LIBFT)
	@echo "\n$(GREEN)Create bonus binaries$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLXFLAGS) $(LIBFTFLAGS) -o $@

$(BUILD_DIR)/%.o: $(MANDA_DIR)/%.c | $(DIRS) $(LIBFT_DIR)
	@mkdir -p $(BUILD_DIR)
	@if [ $(NB_COMP) -eq 1 ]; then echo "$(BOLD)Compilation of source files :$(NOC)";fi
	$(eval PERCENT=$(shell expr $(NB_COMP)00 "/" $(TO_COMP)))
	@if [ $(PERCENT) -le 30 ]; then echo -n "$(RED)"; elif [ $(PERCENT) -le 66 ]; then echo -n "$(YELLOW)"; elif [ $(PERCENT) -gt 66 ]; then echo -n "$(GREEN)"; fi
	@echo -n "\r"; for i in $$(seq 1 $$(/usr/bin/tput cols)); do echo -n " "; done
	@echo -n "\r"; for i in $$(seq 1 25); do if [ $$(expr $$i "*" 4) -le $(PERCENT) ]; then echo -n "█"; else echo -n " "; fi; done; echo -n "";
	@printf " $(NB_COMP)/$(TO_COMP) - Compiling $<"
	@echo -n "$(NOC)"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	$(eval NB_COMP=$(shell expr $(NB_COMP) + 1))

$(BUILD_DIR_BONUS)/%.o: $(BONUS_DIR)/%.c | $(DIRS_BONUS) $(LIBFT_DIR)
	@mkdir -p $(BUILD_DIR_BONUS)
	@if [ $(NB_COMP) -eq 1 ]; then echo "$(BOLD)Compilation of source files :$(NOC)";fi
	$(eval PERCENT=$(shell expr $(NB_COMP_BONUS)00 "/" $(TO_COMP_BONUS)))
	@if [ $(PERCENT) -le 30 ]; then echo -n "$(RED)"; elif [ $(PERCENT) -le 66 ]; then echo -n "$(YELLOW)"; elif [ $(PERCENT) -gt 66 ]; then echo -n "$(GREEN)"; fi
	@echo -n "\r"; for i in $$(seq 1 $$(/usr/bin/tput cols)); do echo -n " "; done
	@echo -n "\r"; for i in $$(seq 1 25); do if [ $$(expr $$i "*" 4) -le $(PERCENT) ]; then echo -n "█"; else echo -n " "; fi; done; echo -n "";
	@printf " $(NB_COMP_BONUS)/$(TO_COMP_BONUS) - Compiling $<"
	@echo -n "$(NOC)"
	@$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@
	$(eval NB_COMP=$(shell expr $(NB_COMP_BONUS) + 1))

clean:
	@echo "$(RED)Remove objects$(NOC)"
	@rm -rf $(BUILD_DIR) $(BUILD_BONUS_DIR)
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Remove binary$(NOC)"
	@rm -f $(NAME) $(BONUS_NAME)
	@rm -rf $(LIBFT_DIR)

re: fclean
	@make

rebonus: fclean
	@make bonus

.PHONY: all bonus clean fclean re rebonus

-include $(DEPS)
-include $(DEPS_BONUS)