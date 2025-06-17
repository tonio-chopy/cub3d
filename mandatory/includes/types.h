/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/17 19:32:26 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

typedef enum e_dir
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}					t_dir;

typedef enum e_shape
{
	LINE,
	TRIANGLE_ISO,
	RECTANGLE,
	CIRCLE
}					t_shapetype;

typedef struct s_point
{
	int				x;
	int				y;
	double			xd;
	double			yd;
	double			magnitude;
}					t_vec;

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
	bool			is_started;
	bool			is_ended;
	int				fd;
	char			player_orientation;
	int				player_pos;
}					t_parsed_map;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
}					t_mlx;

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
	double			wall_ratio;
	bool			has_hit;
	char			side;
	double			deg_from_dir;
	double			pro_dist;
	double			pro_height;
	int				hit_dir;
}					t_ray;

typedef struct s_data
{
	t_mlx			*mlx;
	t_parsed_map	*parsed_map;
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
}					t_data;

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

#endif
