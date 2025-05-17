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

enum e_dir
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_point
{
	int	x;
	int	y;
	double xd;
	double yd;
	double magnitude;
}	t_vec;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	t_vec	*location;
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
	double	tilesize;
	t_img	*map;
}	t_minimap;

typedef struct s_walls
{
	t_img	*img;
	float	ceiling_ratio;
}	t_walls;

typedef struct s_cam
{
	t_vec	*orig;
	t_vec	*plane;
	t_vec	*dir;
}	t_cam;

typedef struct s_ray
{
	t_vec	*raydir;
	t_vec	*delta;
	t_vec	*current_cell;
	t_vec	*step_cell;
	t_vec	*side_dist;
	double	wall_ratio;
	bool	has_hit;
	char	side;
	double	deg_from_dir;
	double	pro_dist;
}	t_ray;

typedef struct s_data
{
	t_mlx			*mlx;
	t_parsed_map	*parsed_map;
	t_minimap		*minimap;
	t_walls			*walls;
	t_cam			*cam;
	t_ray			*ray;
	int				**tex;
	t_vec			*player_pos;
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
	t_vec		*start;
} t_shape;

// ======== draw
// basic
void	cub_put_pix_to_img(t_img *img, double x, double y, unsigned int color);
void	cub_drawLine(t_img *img, t_vec *from, t_vec *to, int color);
void	cub_draw_rect(t_img *img, t_vec *from, double w, double h, unsigned int color);
// shapes
void	cub_drawLine_angle(t_data *data, t_img *img, t_vec *from, int degrees, double len);
void	cub_draw_fov(t_data *data, t_img *img, t_vec *from, int degrees, int bisectlen);
void	cub_draw_ceiling_and_floor(t_data *data);
// walls
void	cub_drawLine_wall(t_data *data, double dist, t_ray *ray, int screen_x);
void	cub_draw_walls(t_data *data);

// ========= hooks
// movements
# define FOV_DEGREES 66				// ensure coherent with FOV_SCALE
# define FOV_SCALE 0.649407f		// tan (FOV_DEGREES / 2)
# define ROTATION_SPEED 0.03f		// radians per frame
# define MOVEMENT_SPEED 0.03f		// cell per frame
# define MOVEMENT_SECURITY 0.2f		// min distance between wall and player center

void    cub_move_if_possible(t_data *data, t_vec *target, t_vec *move_vector);
void	cub_update_rotation(t_data *data);
void	cub_update_translation(t_data *data);

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

// ========= maps
// cam
void	cub_update_cam_vector(t_data *data);
void	cub_init_cam(t_data *data);
// coord
t_vec	*cub_get_topleftcoord_adjusted(t_parsed_map *map, t_minimap *mini, int index);
t_vec	*cub_get_centercoord_norm(t_parsed_map *map, t_minimap *mini, int index);
// minimap
void	cub_draw_minimap(t_data *data);
void    cub_draw_player(t_data *data);
// init
void    cub_init_graphics(t_data *data);

// ========= maths
# define PI  3.14159265358979323846f
// vectors
t_vec	*cub_init_vec(int x, int y);
t_vec	*cub_init_vec_double(double x, double y);
// angles
double	ft_to_rad(double degrees);
double	ft_to_deg(double radians);
double	ft_vector_len(t_vec *p);
double	ft_get_angle_between_vec(t_vec *u, t_vec *v);
// vector ops
void	ft_multiply_vector(t_vec *p, double factor);
t_vec	*ft_rotate_vector_new(t_vec *p, double angle_rad);
void	ft_rotate_vector(t_vec *p, double angle_rad);
double	ft_vector_scalar_product(t_vec *u, t_vec *v);
void	ft_normalize_vector(t_vec *p);
// matrix
void	multiply_matrix(t_vec *p, double **matrix);
double **get_zrotation_matrix(double angle_rad);
void	clean_3dmatrix(double **m, int size);
// ========= parse

// ========= raycast
double	cub_measure_dist_to_wall(t_data *data, t_vec *ray_dirvector);
// init
void	cub_init_ray(t_data *data, t_vec *ray_dirvector);
void	reinit_ray(t_data *data, t_vec *ray_dirvector);
// textures
# define TEXTURE_SIZE 1024
int   *cub_read_texture(t_data *data, char *file);
void	cub_apply_texture(t_data *data, int textureX, t_vec *from, double toY, double pro_height, int dir);


// ========= utils
// clean
void	cub_clean2d(void **array, int size, unsigned int bitmask, bool freeArr);
void	cub_clean_mlx_and_img(t_mlx *mlx, t_img *main_img);
void	cub_clean_data(t_data *data);
void	cub_clean_ray(t_ray *ray);
// colors
int		cub_rgb_to_int(double r, double g, double b);
// errors
# define MSG_USAGE "usage cub3D <map path> [optional debug level from 1 to 2]\n"
# define MSG_EMPTY_ENV "empty env var\n"
# define MSG_ALLOC "memory allocation error\n"
void    cub_handle_fatal(t_data *data, char *custom_msg);
// mlx utils
t_mlx	*cub_init_mlx( void );
t_img	*cub_init_img(t_data *data, int width, int height, t_vec *location);
int		cub_refresh(void *param);
void	cub_clear_img(t_img *img);

// debug -- TO DELETE
void	debug_data(t_data *data);
void	debug_ray(t_ray *ray);



#endif
