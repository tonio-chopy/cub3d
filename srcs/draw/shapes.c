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

/*
 * centers vertically
 * reduces value if overflows viewport bottom or top
 */
void	adjust_y_for_viewport(double pro_height, t_point *bottom, t_point *top)
{
	int vertical_center;

	vertical_center = WIN_H / 2 + UPWARD_MODIFIER;

	top->yd = vertical_center + pro_height / 2;
	bottom->yd = vertical_center - pro_height / 2;
	if (bottom->yd < 0)
		bottom->yd = 0;
	if (top->yd > WIN_H)
		top->yd = (double) WIN_H - 1;
}

/*
 * viewport_x is the current x where we cast a ray
 * projected height = wall height * projected dist / wall dist
 * TODO ajust with orthogonal distance to correct fisheye effect
 */
void	cub_drawLine_wall(t_data *data, double dist, t_ray *ray, int viewport_x)
{
	double	pro_height;
	int		color;
	t_point	bottom;
	t_point	top;

	if (dist < 0.0001)
		dist = 0.0001;
	pro_height = ray->pro_dist / dist;
	// printf("projected height is %f\n", pro_height);
	bottom.xd = viewport_x;
	top.xd = viewport_x;
	adjust_y_for_viewport(pro_height, &bottom, &top);
	color = get_wall_color(ray->side, ray->raydir);
	cub_drawLine(data->field->display, &bottom, &top, color);
}

void	cub_draw_walls(t_data *data)
{
	int	x;
	double	radians;
	double	inc_degrees;
	double	degrees;
	t_point	*ray_dirvector;
	double	distance;

	x = 0;
	degrees = -(FOV_DEGREES / 2);
	inc_degrees = FOV_DEGREES / (double) WIN_W;
	while (x < WIN_W)
	{
		degrees += inc_degrees;
		radians = ft_to_rad(degrees);
		ray_dirvector = ft_rotate_vector_new(data->dir_vector, radians);
		distance = cub_measure_dist_to_wall(data, ray_dirvector, -inc_degrees);
		// printf("distance at pix %d is %f\n", x, distance);
		cub_drawLine_wall(data, distance, data->ray, x);
		x++;
		free(ray_dirvector);
	}
}

void	cub_drawLine_angle(t_data *data, t_img *img, t_point *from, int degrees, double len)
{
	t_point	to;
	// t_point from_resized;
	double	radians;
	t_point	*ray_dirvector;
	// t_point	*ray_camvector;
	double	distance;

	(void) data;
	radians = ft_to_rad(degrees);
	ray_dirvector = ft_rotate_vector_new(data->dir_vector, -radians);
	// ray_camvector = ft_rotate_vector_new(data->cam_vector, -radians);
	distance = cub_measure_dist_to_wall(data, ray_dirvector, degrees) * data->minimap->tilesize;
	if (distance == -1)
		distance = len;
	to.xd = from->xd + ray_dirvector->xd * distance;
	to.yd = from->yd + ray_dirvector->yd * distance;
	cub_drawLine(img, from, &to, COL_FOV);
	// free(ray_camvector);
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