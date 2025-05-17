#include "test.h"

/*
 * centers vertically
 * reduces value if overflows viewport bottom or top
 */
void	adjust_y_for_viewport(t_data *data, double pro_height, t_vec *bottom, t_vec *top)
{
	int vertical_center;

	vertical_center = WIN_H * data->walls->ceiling_ratio;

	top->yd = vertical_center + pro_height / 2;
	bottom->yd = vertical_center - pro_height / 2;
	if (bottom->yd < 0)
		bottom->yd = 0;
	if (top->yd > WIN_H)
		top->yd = (double) WIN_H - 1;
}

int	get_direction(char side, t_vec *dir)
{
	if (side == 'x')
	{
		if (dir->xd < 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (dir->yd < 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

/*
 * viewport_x is the current x where we cast a ray
 * projected height = wall height * projected dist / wall dist
 * start painting from other texture extremity when raydir doesnt match the x or y axis
 */
void	cub_drawLine_wall(t_data *data, double dist, t_ray *ray, int viewport_x)
{
	double	pro_height;
	t_vec	bottom;
	t_vec	top;
	double	texture_x;
	int		dir;

	if (dist < 0.0001)
		dist = 0.0001;
	pro_height = WIN_H / dist;
	bottom.xd = viewport_x;
	top.xd = viewport_x;
	adjust_y_for_viewport(data, pro_height, &bottom, &top);
	texture_x = (int) (ray->wall_ratio * TEXTURE_SIZE);
	if ((ray->side == 'x' && ray->raydir->xd < 0) || (ray->side == 'y' && ray->raydir->yd > 0))
		texture_x = TEXTURE_SIZE - texture_x - 1;
	dir = get_direction(ray->side, ray->raydir);
	cub_apply_texture(data, texture_x, &bottom, top.yd, pro_height, dir);
}

void	cub_draw_walls(t_data *data)
{
	int	x;
	double	inc_degrees;
	double	degrees;
	t_vec	*ray_dirvector;
	double	distance;
	double	cam_x_vector;
	double	distorsion_corrector;

	x = 0;
	degrees = -(FOV_DEGREES / 2);
	inc_degrees = FOV_DEGREES / (double) WIN_W;
	while (x < WIN_W)
	{
		cam_x_vector = x * 2 / (double) WIN_W - 1.0;
		degrees += inc_degrees;
		ray_dirvector = ft_rotate_vector_new(data->cam->dir, ft_to_rad(degrees));
		distorsion_corrector = cosf(ft_to_rad(degrees));
		distance = cub_measure_dist_to_wall(data, ray_dirvector) * distorsion_corrector;
		cub_drawLine_wall(data, distance, data->ray, x);
		x++;
		free(ray_dirvector);
	}
}