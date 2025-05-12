#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"

# define WIN_W 640
# define WIN_H 360
# define MINIMAP_SIZE 200

# define GREY 0x00A0A7A5
# define GRASS 0x00B1E1A1
# define RED 0x00FF0000
# define L_RED 0xAAFF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000

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

typedef struct s_point
{
	int	x;
	int	y;
	double xd;
	double yd;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	t_point	*location;
}	t_img;

typedef struct s_map
{
	int				width;
	int				heigth;
	int				nb_elems;
	char			*elems;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	char			*NOpath;
	char			*SOpath;
	char			*WEpath;
	char			*EApath;
	char			player_orientation;
	int				player_pos;
}	t_parsed_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_minimap
{
	int		max_pixels;
	float	tilesize;
	t_img	*map;
	t_img	*player;
}	t_minimap;

typedef struct s_data
{
	t_mlx			*mlx;
	t_parsed_map	*parsed_map;
	t_minimap		*minimap;
	t_point			*dir_vector;
	t_point			*cam_vector;
	t_point			*player_pos;
	bool			rotates_left;
	bool			rotates_right;
	bool			move_forward;
	bool			move_backward;
	bool			move_left;
	bool			move_right;
	char			debug;
}	t_data;

typedef enum e_shape
{
	LINE,
	TRIANGLE,
	RECTANGLE,
	CIRCLE
}	t_shapetype;

typedef struct s_shape
{
	t_shapetype type;
	t_img		*img;
	t_point		*start;
} t_shape;

typedef struct s_ray
{
	t_point	*raydir;
	t_point	*delta;
	t_point	*current_cell;
	t_point	*step_cell;
	t_point	*side_dist;
	bool	has_hit;
	char	side;
}	t_ray;

// mlx
t_mlx	*cub_init_mlx( void );
t_img	*cub_init_img(t_data *data, int width, int height, t_point *location);
int		cub_refresh(void *param);
void	cub_clear_img(t_img *img);

// utils
int		cub_rgb_to_int(double r, double g, double b);

// utils math
float   ft_to_rad(int degrees);
void	ft_normalize_vector(t_point *p);
void	ft_rotate_vector(t_point *p, double angle_rad);
t_point	*ft_rotate_vector_new(t_point *p, double angle_rad);
double	ft_vector_len(t_point *p);

// raycast
double	cub_measure_dist_to_wall(t_data *data, t_point *ray_dirvector);

// draw
void	cub_put_pix_to_img(t_img *img, int x, int y, unsigned int color);
void	cub_drawLine(t_img *img, t_point *from, t_point *to);
void	cub_draw_rect(t_img *img, t_point *from, int w, int h, unsigned int color);
void	cub_drawLine_angle(t_data *data, t_img *img, t_point *from, int degrees, double len);
void	cub_draw_cone(t_data *data, t_img *img, t_point *from, int degrees, int bisectlen);
t_point	*cub_init_point(int x, int y);
t_point	*cub_init_point_double(double x, double y);

// minimap
t_point	*cub_get_topleftcoord_adjusted(t_parsed_map *map, t_minimap *mini, int index);
t_point	*cub_get_centercoord_norm(t_parsed_map *map, t_minimap *mini, int index);
void	cub_draw_minimap(t_data *data);
void    cub_draw_player(t_data *data);
void	cub_init_dir_vector(t_data *data);
void	cub_init_player_pos(t_data *data);
void	cub_init_cam_vector(t_data *data);
void	cub_update_cam_vector(t_data *data);

// moves
void    move_if_possible(t_data *data, t_point *target, t_point *move_vector);

// errors
void    cub_handle_fatal(t_data *data, char *custom_msg);

// clean
void	cub_clean2d(void **array, int size, unsigned int bitmask, bool freeArr);
void	cub_clean_mlx_and_img(t_mlx *mlx, t_img *main_img);
void	cub_clean_data(t_data *data);
void	cub_clean_ray(t_ray *ray);

// debug -- TO DELETE
void	debug_data(t_data *data);
void	debug_ray(t_ray *ray);

// movements
# define FOV_SCALE 0.66
# define ROTATION_SPEED 0.001f		// radians per frame
# define MOVEMENT_SPEED 0.001f		// cell per frame
# define MOVEMENT_SECURITY 0.1f	// min distance between wall and player center

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

int		cub_handle_no_event(void *param);
int		cub_handle_keypress(int key, void *param);
int		cub_handle_keyrelease(int key, void *param);

#endif
