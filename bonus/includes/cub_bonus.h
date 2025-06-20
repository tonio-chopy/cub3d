/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:16 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/20 20:45:11 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include "../../mlx/mlx.h"
# include "../libft/includes/libft.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define WIN_W 1024
# define WIN_H 768
# define MINIMAP_SIZE 200

# define GREY 0x00A0A7A5
# define GRASS 0x00B1E1A1
# define RED 0x00FF0000
# define L_RED 0xAAFF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000
# define YELLOW 0x00DCE600
# define INVISIBLE 0x00FF00FF

# define WALL_N RED
# define WALL_S GRASS
# define WALL_E BLUE
# define WALL_W GREY

# define COL_FOV RED

# define MAP_EMPTY GRASS
# define MAP_WALL GREY
# define MAP_OUT BLACK

# define E_WALL '1'
# define E_INSIDE '0'
# define E_EMPTY ' '
# define E_NORTH 'N'
# define E_SOUTH 'S'
# define E_WEST 'W'
# define E_EAST 'E'
# define E_GOAL_LEFT 'G'
# define E_GOAL_CENTER 'H'
# define E_GOAL_OPENED 'O'
# define E_GOAL_RIGHT 'I'
# define E_BALL 'B'

# define BONUS_NAME "cub3D_bonus"

typedef enum e_dir
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}					t_dir;

typedef enum e_target
{
	WALL,
	BALL
}					t_target;

typedef enum e_goal
{
	GOAL_LEFT = 4,
	GOAL_CENTER = 5,
	GOAL_RIGHT = 6,
	CENTER_WAIT = 7,
	LEFT_FAIL = 8,
	CENTER_FAIL = 9,
	RIGHT_FAIL = 10,
	LEFT_CATCH = 11,
	CENTER_CATCH = 12,
	RIGHT_CATCH = 13,
	RIGHT_PASS_1 = 14,
	RIGHT_PASS_2 = 15,
	RIGHT_PASS_3 = 16,
	RIGHT_PASS_4 = 17,
	RIGHT_PASS_5 = 18,
	LEFT_PASS_1 = 19,
	LEFT_PASS_2 = 20,
	LEFT_PASS_3 = 21,
	LEFT_PASS_4 = 22,
	LEFT_PASS_5 = 23,
	NONE = 24
}					t_goal_tex;

typedef enum e_wall
{
	WEST_HIT = 25,
	EAST_HIT = 26,
	TROPHY = 27
}					t_wall_tex;

typedef struct s_point
{
	int				x;
	int				y;
	double			xd;
	double			yd;
	double			magnitude;
}					t_vec;

typedef struct s_color
{
	int				value;
	int				r;
	int				g;
	int				b;
}	t_color;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				*int_addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	t_vec			*location;
}					t_img;

typedef struct s_map
{
	int				width;
	int				heigth;
	int				nb_elems;
	char			*elems;
	char			**elems2d;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	bool			has_ceiling;
	bool			has_floor;
	char			**paths;
	int				fd;
	bool			is_started;
	bool			is_ended;
	char			*codes[4];
	char			player_orientation;
	int				player_pos;
	int				opened_door_index;
}					t_parsed_map;

typedef struct s_goal
{
	t_goal_tex		position;
	int				sprite_index;
	bool			can_see_ball;
	bool			can_see_goal;
	bool			has_catched;
	bool			has_shot;
	bool			can_shoot;
	int				score;
	bool			win;
	int				anim_count;
	int				ball_anim_count;
}					t_goal;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
}					t_mlx;

typedef struct s_minimap
{
	int				max_pixels;
	double			tilesize;
	double			x_offset;
	double			y_offset;
	t_img			*map;
}					t_minimap;

typedef struct s_walls
{
	t_img			*img;
	float			ceiling_ratio;
}					t_walls;

typedef struct s_cam
{
	t_vec			*orig;
	t_vec			*plane;
	t_vec			*dir;
}					t_cam;

typedef struct s_ray
{
	t_vec			*raydir;
	t_vec			*delta;
	t_vec			*current_cell;
	t_vec			*step_cell;
	t_vec			*side_dist;
	t_vec			*check_cell;
	int				prev_elem;
	double			wall_ratio;
	bool			has_hit;
	char			side;
	double			deg_from_dir;
	double			pro_dist;
	double			pro_height;
	int				hit_dir;
}					t_ray;

typedef struct s_sprite
{
	int				screenx;
	int				startx;
	int				endx;
	int				starty;
	int				endy;
	int				sprite_size;
	double			distance;
	int				uncutx;
	int				uncutxend;
	int				uncuty;
	int				uncutyend;
	int				drawstartx;
	int				drawendx;
	int				drawstarty;
	int				drawendy;
}	t_sprite;

typedef struct s_data
{
	t_mlx			*mlx;
	t_parsed_map	*parsed_map;
	t_minimap		*minimap;
	t_walls			*walls;
	t_goal			*goal;
	t_cam			*cam;
	t_ray			*ray;
	t_sprite		*sprite;
	int				**tex;
	int				**sprites;
	int				flag_frame;
	double			flag_wave_offset;
	int				ball_h;
	int				ball_w;
	t_vec			*ball_pos;
	double			*zbuffer;
	t_vec			*player_pos;
	bool			rotates_left;
	bool			rotates_right;
	bool			move_forward;
	bool			move_backward;
	bool			move_left;
	bool			move_right;
	bool			show_help;
	bool			is_bonus;
	char			debug;
}					t_data;

typedef enum e_shape
{
	LINE,
	TRIANGLE_ISO,
	RECTANGLE,
	CIRCLE
}					t_shapetype;

typedef struct s_shape
{
	t_shapetype		type;
	t_img			*img;
	t_vec			*start;
	double			angle;
	double			width;
	double			heigth;
	unsigned int	color;
}					t_shape;

typedef struct s_map_state
{
	bool			map_started;
	bool			map_ended;
	int				y;
}					t_map_state;

void				handle_shoot(t_data *data, int key);
void				handle_open(t_data *data, int key);
void				handle_close(t_data *data, int key);
void				init_random(void);

double				cub_measure_dist_to_opened_door(t_data *data,
						t_vec *ray_dirvector);
int					cub_merge_goal_col(t_data *data, t_ray *ray, double pos,
						double texture_x);
int					cub_get_ball_col(t_data *data, t_ray *ray, double pos,
						double texture_x);
void				cub_apply_ball(t_data *data, t_vec *from, double toY,
						t_ray *ray);
void				cub_draw_ball(t_data *data);

// ======== draw
// basic
void				cub_drawline(t_img *img, t_vec *from, t_vec *to, int color);
void				cub_draw_rect(t_img *img, t_shape *rect);
void				init_shape(t_vec *start, double width, t_shapetype type,
						t_shape *shape);
// shapes
void				cub_draw_fov(t_data *data, t_vec *from, int degrees,
						int bisectlen);
void				cub_draw_ceiling_and_floor(t_data *data);
// walls
void				cub_drawline_wall(t_data *data, double dist, t_ray *ray,
						int screen_x);
void				cub_draw_walls(t_data *data);
// sprite ball
void				cub_draw_ball(t_data *data);
void				cub_compute_sprite_size(t_data *data, int *code);
void				cub_compute_sprite_dist(t_data *data, t_vec *ball_dist);

// goal anim
void				cub_update_goal_anim(t_data *data);

// help
# define HELP_X 30
# define HELP_Y 600
# define HELP_W 200
# define HELP_H 130
# define HELP_COL 0xEE000000
# define HELP_TEXT 0x00FFFFFF

void				cub_draw_help(t_data *data);

// flag
# define FR_BLUE 0x002395ED
# define FR_WHITE 0x00FFFFFF
# define FR_RED 0x00FF5050
# define ES_RED 0x00FF5050
# define ES_YELLOW 0x00FFCC00

void	cub_draw_flags(t_data *data);

// ========= hooks
// movements
# define FOV_DEGREES 66 // ensure coherent with FOV_SCALE
# define FOV_SCALE 0.649407f // tan (FOV_DEGREES / 2)
# define ROTATION_SPEED 0.03f // radians per frame
# define MOVEMENT_SPEED 0.13f // cell per frame
# define MOVEMENT_SECURITY 0.2f // min distance between wall and player

void				cub_move_if_possible(t_data *data, t_vec *target,
						t_vec *move_vector);
void				cub_update_rotation(t_data *data);
void				cub_update_translation(t_data *data);
// rotate
int					handle_stop_rotate(t_data *data, int key);
int					handle_rotate(t_data *data, int key);
int					handle_mouse_rotate(int x, int y, void *param);
// hooks
# define K_ESCAPE 65307
# define K_LEFT 65361
# define K_UP 65362
# define K_RIGHT 65363
# define K_DOWN 65364
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_H 104

int					handle_click_on_close(void *param);
int					cub_handle_no_event(void *param);
int					cub_handle_keypress(int key, void *param);
int					cub_handle_keyrelease(int key, void *param);

// ========= maps
// cam
void				cub_update_cam_vector(t_data *data);
void				cub_init_cam(t_data *data);
// coord
t_vec				*cub_get_topleftcoord_adjusted(t_parsed_map *map,
						t_minimap *mini, int index);
t_vec				*cub_get_centercoord_norm(t_parsed_map *map, int index);
// minimap
void				cub_draw_minimap(t_data *data);
void				cub_draw_player(t_data *data);
// init
void				cub_init_graphics(t_data *data);
// init tex bonus
void				cub_get_goal_tex(t_data *data);

// ========= maths
# define PI 3.14159265358979323846f
// vectors
t_vec				*cub_init_vec(int x, int y);
t_vec				*cub_init_vec_double(double x, double y);
// angles
double				ft_to_rad(double degrees);
double				ft_to_deg(double radians);
double				ft_vector_len(t_vec *p);
double				ft_get_angle_between_vec(t_vec *u, t_vec *v);
// vector ops
void				ft_multiply_vector(t_vec *p, double factor);
t_vec				*ft_rotate_vector_new(t_vec *p, double angle_rad);
void				ft_rotate_vector(t_vec *p, double angle_rad);
double				ft_vector_scalar_product(t_vec *u, t_vec *v);
void				ft_normalize_vector(t_vec *p);
// matrix
void				multiply_matrix(t_vec *p, double **matrix);
double				**get_zrotation_matrix(double angle_rad);
void				clean_3dmatrix(double **m, int size);

// ========= parse
# define VISITED 'X'
// check file
void				cub_check_file(t_data *data, char *filename);
// check player
void				cub_find_player(t_data *data, t_parsed_map *parsed_map);
// check close
void				check_map_closed(t_data *data, t_parsed_map *map);
// measure map
void				cub_measure_map(t_data *data, char *filename);
// infos
bool				cub_are_infos_filled(t_data *data);
void				cub_try_add_texture_paths_and_colors(t_data *data,
						char *line);
// line
char				*cub_trim_map(char *line);
char				*cub_trim_full(char *line);
bool				cub_is_map_line(char *line, bool is_bonus);
void				cub_add_map_line(t_data *data, t_parsed_map *parsed_map,
						char *line, int i);
// colors
int					cub_parse_color(char *str, unsigned int *color);

// utils
bool				cub_is_valid_number(char *str);
void				cub_compute_adjacent_indexes_x(t_parsed_map *map, int i,
						int *left_i, int *right_i);
void				cub_compute_adjacent_indexes_y(t_parsed_map *map, int i,
						int *up_i, int *down_i);
void				cub_check_info_filled(t_data *data, char *line);
// parse
int					cub_parse_file(char *filename, t_data *data);

// ========= raycast
void				cub_iter_ray(t_data *data, t_ray *ray);
void				compute_increments(t_ray *ray, t_vec *player);
double				cub_measure_dist_to_wall(t_data *data,
						t_vec *ray_dirvector);
double				cub_measure_dist_to_ball(t_data *data,
						t_vec *ray_dirvector);
double				compute_dist(t_data *data, t_ray *ray, char side);
// check
int					get_direction(char side, t_vec *dir);
// init
void				cub_init_ray(t_data *data, t_vec *ray_dirvector);
void				reinit_ray(t_data *data, t_vec *ray_dirvector);
// textures
# define TEXTURE_SIZE	1024
# define BALL_SIZE		1024

int					*cub_read_texture(t_data *data, char *file);
void				cub_apply_texture(t_data *data, t_vec *from, double toY,
						t_ray *ray);
t_vec				*cub_get_coord_from_index(t_data *data, int index);
t_vec				*cub_get_center_coord_from_index(t_data *data, int index);
void				cub_get_goal_tex(t_data *data);

// ========= init
t_data				*cub_init_data(char **av);
void				cub_init_sprite(t_data *data);
void				cub_init_bonus(t_data *data);
void				cub_init_hooks(t_data *data);

// ========= utils
// clean
void				cub_clean2d(void **array, int size, unsigned int bitmask,
						bool freeArr);
void				cub_clean_data(t_data *data);

// images
void				cub_clear_img(t_img *img);
void				cub_draw_help(t_data *data);
void				cub_update_img_info(t_img *img, int bpp, int line_length,
						int endian);
void				cub_update_img_coord(t_img *img, int width, int height,
						t_vec *location);

// clean bonus
void				cub_clean_minimap(t_data *data, t_minimap *minimap);
void				cub_clean_goal(t_goal *goal);
void				cub_clean_sprites(t_data *data);
void				cub_clean_bonus(t_data *data);

// clean img
void				cub_clean_ray(t_ray *ray);
void				cub_clean_img(t_data *data, t_img *img);
void				cub_clean_field(t_data *data, t_walls *walls);
void				cub_clean_mlx(t_mlx *mlx);
// colors
int					cub_rgb_to_int(double r, double g, double b);
void				cub_cpy_with_transparency(t_img *dest, t_img *from,
						int x_offset, int y_offset);
void				cub_put_pix_to_img(t_img *img, double x, double y,
						unsigned int color);

// File validation
void				cub_check_file(t_data *data, char *filename);

// Player validation
void				cub_find_player(t_data *data, t_parsed_map *parsed_map);

// Map closure validation
void				check_map_closed(t_data *data, t_parsed_map *map);

// Map measurement
void				cub_measure_map(t_data *data, char *filename);

// Info parsing
bool				cub_are_infos_filled(t_data *data);
void				cub_try_add_texture_paths_and_colors(t_data *data,
						char *line);

// Info validation utilities
void				cub_init_cardinal_codes(char **codes);
void				cub_set_ceiling_color(t_data *data, char *line,
						unsigned int color);
void				cub_set_floor_color(t_data *data, char *line,
						unsigned int color);

// Color parsing
void				cub_add_ceiling_or_floor_color(t_data *data, char *trimmed,
						char *line, bool *has_matched);

// Texture parsing
void				cub_handle_matching_code(t_data *data, int i, char *line,
						char *trimmed);

// Line processing
char				*cub_trim_map(char *line);
char				*cub_trim_full(char *line);
void				cub_add_map_line(t_data *data, t_parsed_map *parsed_map,
						char *line, int i);

// Parsing validation utilities
bool				is_valid_number(char *str);
bool				is_only_whitespace(char *line);
bool				has_consecutive_commas(char *str);
int					count_commas(char *str);
int					count_elements(char **split);

// String utilities
char				*trim_whitespace(char *str);

// Color parsing
int					cub_parse_color(char *str, unsigned int *color);

// Map utilities
void				cub_compute_adjacent_indexes_x(t_parsed_map *map, int i,
						int *left_i, int *right_i);
void				cub_compute_adjacent_indexes_y(t_parsed_map *map, int i,
						int *up_i, int *down_i);
void				cub_check_info_filled(t_data *data, char *line);

// Main parsing function
int					cub_parse_file(char *filename, t_data *data);
// errors
# define MSP_OPEN "error opening file"
# define MSP_INVALID_COLOR "invalid color"
# define MSP_INVALID_FILENAME "invalid filename"
# define MSP_IVL "invalid configuration line"
# define MSP_IVM "invalid map line"
# define MSP_IVC "invalid content after configuration"
# define MSP_UNK "Unknown or misplaced element in .cub file"
# define MSP_ELM "empty line in map content"
# define MSP_MISSING "missing informations"
# define MSP_NOT_CLOSED "map is not closed"
# define MSG_USAGE "usage cub3D <map path> [optional debug level from 1 to 2]"
# define MSG_EMPTY_ENV "empty env var"
# define MSG_ALLOC "memory allocation error"
# define MSG_DFC "duplicate floor color"
# define MSG_DCC "duplicate ceiling color"
# define MSG_DTP "duplicate texture path"
# define MSG_MTP "missing texture path"
# define MSG_DCC "duplicate ceiling color"
# define MSG_EXC "extra content after texture path"

void				cub_handle_fatal(t_data *data, char *custom_msg);
void				cub_parse_error(t_data *data, char *msg);
void				cub_handle_fatal_parse(t_data *data, int fd, char *line,
						char *msg);
// mlx utils
t_mlx				*cub_init_mlx(void);
t_img				*cub_init_img_from_xpm(t_data *data, int width, int height,
						char *filename);
t_img				*cub_init_img(t_data *data, int width, int height,
						t_vec *location);
int					cub_refresh(void *param);
void				cub_clear_img(t_img *img);

// utils bonus
int					cub_refresh_bonus(void *param);

// ================= init

bool				check_args(int ac, char **env);
void	debug_elems(t_parsed_map *map, char *elems);

#endif
