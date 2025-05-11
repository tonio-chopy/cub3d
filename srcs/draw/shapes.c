#include "test.h"

void	cub_put_pix_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->addr + (int) (y * img->line_length + x * (img->bpp / 8));
			*(unsigned int *) pixel = color;
	}
}

// bool	has_hit(t_parsed_map *map, t_point *ray)
// {
// 	(void)
// }

// double	measure_dist_to_wall(t_data *data, t_img *img, t_point *from, t_point *to, bool should_draw)
// {
// 	t_point	*ray;
// 	int		i;
// 	double	distance;
// 	// char 	side;

// 	distance = -1;
// 	cub_update_cam_vector(data);
// 	ray = cub_init_point_double(data->dir_vector->xd + data->player_pos->xd * data->cam_vector->xd, \
// 		data->dir_vector->yd + data->player_pos->yd * data->cam_vector->yd);
// 	return (distance);
// }

void	cub_drawLine(t_img *img, t_point *from, t_point *to)
{
	int		steps;
	t_point	delta;
	t_point	inc;
	t_point	draw;
	int		i;

	delta.xd = to->xd - from->xd;
	delta.yd = to->yd - from->yd;
	if (fabs(delta.xd) > fabs(delta.yd))
		steps = round(fabs(delta.xd));
	else
		steps = round(fabs(delta.yd));
	inc.xd = delta.xd / (double) steps;
	inc.yd = delta.yd / (double) steps;
	draw.xd = from->xd;
	draw.yd = from->yd;
	i = 0;
	while (i < steps)
	{
		cub_put_pix_to_img(img, round(draw.xd), round(draw.yd), L_RED);
		draw.xd += inc.xd;
		draw.yd += inc.yd;
		i++;
	}
}

// starting from topleftmost corner
void	cub_draw_rect(t_img *img, t_point *start, int w, int h, unsigned int color)
{
	int x;
	int	y;

	y = start->y;
	while ((double) y < start->yd + h)
	{
		x = start->x;
		while ((double) x < start->xd + w)
		{
			// printf("putting pix of color %x at x %d and y %d\n", color, x, y);
			cub_put_pix_to_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	cub_drawLine_angle(t_data *data, t_img *img, t_point *from, t_point *norm_vector, int degrees, double len)
{
	t_point	to;
	double	radians;
	t_point	*rot;
	double	distance;

	(void) data;
	radians = ft_to_rad(degrees);
	rot = ft_rotate_vector_new(norm_vector, -radians);
	// distance = measure_dist_to_wall(data, img, from, &to, true);
	// if (distance == -1)
	distance = len;
	to.xd = from->xd + rot->xd * distance;
	to.yd = from->yd + rot->yd * distance;
	cub_drawLine(img, from, &to);
	free(rot);
}

void	cub_draw_cone(t_data *data, t_img *img, t_point *from, t_point *norm_vector, int degrees, int bisectlen)
{
	// int		i;

	// i = -(degrees / 2);

	cub_drawLine_angle(data, img, from, norm_vector, -(degrees / 2), bisectlen);
	cub_drawLine_angle(data, img, from, norm_vector, (degrees / 2), bisectlen);
	// while (i < degrees / 2)
	// {
	// 	cub_drawLine_angle(img, from, norm_vector, i, bisectlen);
	// 	i++;
	// }
}

t_point	*cub_init_point(int x, int y)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	point->x = x;
	point->y = y;
	point->xd = (float)x;
	point->yd = (float)y;
	return (point);
}

t_point	*cub_init_point_double(double x, double y)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	point->xd = x;
	point->yd = y;
	point->x = round(x);
	point->y = round(y);
	return (point);
}