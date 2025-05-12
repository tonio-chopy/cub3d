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

void	cub_drawLine(t_img *img, t_point *from, t_point *to, int color)
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
		cub_put_pix_to_img(img, round(draw.xd), round(draw.yd), color);
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
			cub_put_pix_to_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

int	get_wall_color(char side, t_point *dir)
{
	if (side == 'x')
	{
		if (dir->xd < 0) // goes left
			return (WALL_E);
		else
			return (WALL_W);
	}
	else
	{
		if (dir->yd < 0) // goes up
			return (WALL_S);
		else
			return (WALL_N);
	}
}

void	cub_drawLine_wall(t_data *data, double dist, t_ray *ray, int screen_x)
{
	int	line_height;
	// int	start;
	// int	end;
	double	x;
	t_point	from;
	t_point to;

	from.x = screen_x;
	to.x = screen_x;

	line_height = (int) (WIN_H / dist); // ex 640 / 2cells = 320
	from.y = -line_height / 2 + WIN_H / 2; // ex -160 + 320 = 160
	if (from.y < 0)
		from.y = 0;
	to.y = line_height / 2 + WIN_H / 2;
	if (to.y >= WIN_H)
		to.y = WIN_H - 1;
	if (ray->side == 'y')
		x = data->player_pos->yd + dist + ray->raydir->yd;
	else
		x = data->player_pos->xd + dist + ray->raydir->xd;
	x -= floor(x);
	cub_drawLine(data->field->display, &from, &to, get_wall_color(ray->side, ray->raydir));
}

void	draw_walls(t_data *data)
{
	int	x;
	double	radians;
	t_point	*ray_dirvector;
	// t_point	*ray_camvector;
	double	distance;
	double	degrees;
	t_ray	ray;

	x = 0;
	while (x < WIN_W)
	{
		radians = ft_to_rad(x / WIN_W * 60);
		ray_dirvector = ft_rotate_vector_new(data->dir_vector, -radians);
		// ray_camvector = ft_rotate_vector_new(data->cam_vector, -radians);
		distance = cub_measure_dist_to_wall(data, ray_dirvector);
		cub_drawLine_wall(data, distance, x);
		x++;
	}
}

void	cub_drawLine_angle(t_data *data, t_img *img, t_point *from, int degrees, double len)
{
	t_point	to;
	// t_point from_resized;
	double	radians;
	t_point	*ray_dirvector;
	t_point	*ray_camvector;
	double	distance;

	(void) data;
	radians = ft_to_rad(degrees);

	ray_dirvector = ft_rotate_vector_new(data->dir_vector, -radians);
	ray_camvector = ft_rotate_vector_new(data->cam_vector, -radians);
	distance = cub_measure_dist_to_wall(data, ray_dirvector) * data->minimap->tilesize;
	if (distance == -1)
		distance = len;
	to.xd = from->xd + ray_dirvector->xd * distance;
	to.yd = from->yd + ray_dirvector->yd * distance;
	cub_drawLine(img, from, &to, COL_FOV);
	free(ray_camvector);
	free(ray_dirvector);
}

void	cub_draw_cone(t_data *data, t_img *img, t_point *from, int degrees, int bisectlen)
{
	int		i;

	(void) from;
	i = -(degrees / 2);
	while (i < degrees / 2)
	{
		cub_drawLine_angle(data, img, from, i, bisectlen);
		i += 2;
	}
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