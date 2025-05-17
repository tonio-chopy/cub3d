#include "test.h"

void	cub_draw_ceiling_and_floor(t_data *data)
{
	t_vec 	*coord;
	double	ceiling_h;

	ceiling_h = (double) WIN_H * data->walls->ceiling_ratio;
	coord = cub_init_vec_double(0, 0);
	cub_draw_rect(data->walls->img, coord, WIN_W, ceiling_h, data->parsed_map->ceiling_color);
	coord->yd = (double) ceiling_h;
	cub_draw_rect(data->walls->img, coord, WIN_W, WIN_H - ceiling_h, data->parsed_map->floor_color);
}

void	cub_drawLine_angle(t_data *data, t_img *img, t_vec *from, int degrees, double len)
{
	t_vec	to;
	double	radians;
	t_vec	*ray_dirvector;
	double	distance;

	(void) data;
	radians = ft_to_rad(degrees);
	ray_dirvector = ft_rotate_vector_new(data->cam->dir, -radians);
	distance = cub_measure_dist_to_wall(data, ray_dirvector) * data->minimap->tilesize;
	if (distance == -1)
		distance = len;
	to.xd = from->xd + ray_dirvector->xd * distance;
	to.yd = from->yd + ray_dirvector->yd * distance;
	cub_drawLine(img, from, &to, COL_FOV);
	free(ray_dirvector);
}

void	cub_draw_fov(t_data *data, t_img *img, t_vec *from, int degrees, int bisectlen)
{
	int		i;

	i = -(degrees / 2);
	while (i < degrees / 2)
	{
		cub_drawLine_angle(data, img, from, i, bisectlen);
		i += 2;
	}
}
