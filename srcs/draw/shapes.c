#include "test.h"

void	cub_draw_ceiling_and_floor(t_data *data)
{
	t_vec	*coord;
	double	ceiling_h;

	ceiling_h = (double) WIN_H * data->walls->ceiling_ratio;
	coord = cub_init_vec_double(0, 0);
	cub_draw_rect(data->walls->img, coord, WIN_W, ceiling_h, \
data->parsed_map->ceiling_color);
	coord->yd = (double) ceiling_h;
	cub_draw_rect(data->walls->img, coord, WIN_W, WIN_H - ceiling_h, \
data->parsed_map->floor_color);
	free(coord);
}

void	cub_draw_fov(t_data *data, t_vec *from, int degrees, \
int len)
{
	int		deg;
	t_vec	to;
	double	radians;
	t_vec	*ray_dirvector;
	double	distance;

	deg = -(degrees / 2);
	while (deg < degrees / 2)
	{
		radians = ft_to_rad(deg);
		ray_dirvector = ft_rotate_vector_new(data->cam->dir, -radians);
		distance = cub_measure_dist_to_wall(data, ray_dirvector) * \
data->minimap->tilesize;
		if (distance == -1)
			distance = len;
		to.xd = from->xd + ray_dirvector->xd * distance;
		to.yd = from->yd + ray_dirvector->yd * distance;
		cub_drawLine(data->minimap->map, from, &to, COL_FOV);
		free(ray_dirvector);
		deg += 2;
	}
}
