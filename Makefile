NAME			:= cub3D
BONUS_NAME		:= cub3D_bonus
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

COMMON_DIR		:=	common
MLX_DIR			:=	mlx
LIBFT_DIR		:=	libft

#==============================SOURCES===========================#

COMMON_SRCS		:=	raycast/init.c\
					raycast/raycast.c\
					raycast/textures.c\
					maths/angles.c\
					maths/matrix.c\
					maths/vectors.c\
					maths/vectors_ops.c\
					utils/clean_img.c\
					utils/clean.c\
					utils/color.c\
					utils/errors.c\
					utils/image.c\
					utils/mlx_utils.c\
					init.c\
					debug.c\

MANDATORY_SRCS	:=	main.c\
					raycast/hit.c\
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
					# init_game.c\

BONUS_SRCS		:=	parse/check_close.c\
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
					draw/flag_bonus.c\
					draw/door_bonus.c\
					draw/goal_bonus.c\
					draw/sprite_bonus.c\
					draw/sprite_size_bonus.c\
					draw/walls.c\
					hooks/keyhooks.c\
					hooks/moves.c\
					hooks/rotate.c\
					hooks/shoot_bonus.c\
					map/cam.c\
					map/init.c\
					map/init_tex_bonus.c\
					map/minimap.c\
					draw/help_bonus.c\
					map/coord_bonus.c\
					maths/vectors.c\
					raycast/hit_bonus.c\
					utils/utils_bonus.c\
					utils/clean_bonus.c\
					main_bonus.c\
					init_bonus.c\
					# main.c\
					# raycast/raycheck_bonus.c\
					# raycast/init.c\
					# raycast/textures.c\
					# raycast/raycast.c\
					# maths/angles.c\
					# maths/matrix.c\
					# maths/vectors_ops.c\
					# utils/errors.c\
					# utils/color.c\
					# utils/clean.c\
					# utils/clean_img.c\
					# utils/mlx_utils.c\
					# utils/image.c

SRCS_DIR		:= mandatory/srcs
SRCS_BONUS_DIR	:= bonus/srcs
SRCS			:= $(addprefix $(COMMON_DIR)/, $(COMMON_SRCS)) $(addprefix $(SRCS_DIR), $(MANDATORY_SRCS))
SRCS_BONUS		:= $(addprefix $(COMMON_DIR)/, $(COMMON_SRCS)) $(addprefix $(SRCS_BONUS_DIR), $(BONUS_SRCS))
INCLUDES_BONUS	:= bonus/includes
INCLUDES		:= srcs/includes
#==============================LIBFT=============================#

LIBFT			:= $(LIBFT_DIR)/libft.a
LIBFTFLAGS		:= -L$(LIBFT_DIR) -lft

#==============================MLX==============================#

MLX				:= ${MLX_DIR}/libmlx_Linux.a
MLXFLAGS		:= -L${MLX_DIR} -lmlx_Linux -lXext -lX11 -lm -lz

#=============================OBJECTS===========================#

OBJS			:= ${SRCS:$(SRCS_DIR)%.c=$(BUILD_DIR)/%.o}
OBJS_BONUS		:= ${SRCS:$(SRCS_BONUS_DIR)%.c=$(BUILD_DIR)/%.o}

#===============================DEPS=============================#

DEPS			:= ${SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/%.d}
OBJS_BONUS		:= ${SRCS:$(SRCS_BONUS_DIR)%.c=$(BUILD_DIR)/%.d}

#=============================INCLUDES===========================#

INC				:= -I$(INCLUDES) -I$(MLX_DIR) -I$(LIBFT_DIR)/includes
INC_BONUS		:= -I$(INCLUDES_BONUS) -I$(MLX_DIR) -I$(LIBFT_DIR)/includes

#================================DIR=============================#

DIRS			:=	$(sort $(shell dirname $(OBJS))) #no duplicates

#===============================RULES============================#

all: $(NAME)

bonus:
	@$(MAKE) MODE=bonus all

$(DIRS):
	@mkdir -p $@

$(MLX): | $(DIRS)
	@echo "$(BLUE)Compiling MLX...$(NOC)"
	@make -C $(MLX_DIR)

$(LIBFT_DIR):
	@git clone https://github.com/codastream/libft.git $(LIBFT_DIR)

$(LIBFT): $(LIBFT_DIR)
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
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	$(eval NB_COMP=$(shell expr $(NB_COMP) + 1))

clean:
	@echo "$(RED)Remove objects$(NOC)"
	@rm -rf $(BUILD_DIR)
	@rm -rf .build_mandatory .build_bonus
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Remove binary$(NOC)"
	@rm -f $(NAME) cub3D_bonus cub3D
	@rm -rf $(LIBFT_DIR)

re: fclean
	@make

rebonus: fclean
	@make bonus

.PHONY: all bonus clean fclean re re_bonus

-include $(DEPS)
