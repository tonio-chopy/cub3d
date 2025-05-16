#include "test.h"

void	cub_put_pix_to_img(t_img *img, double x, double y, unsigned int color)
{
	char	*pixel;
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->addr + (int) (y * img->line_length + x * (img->bpp / 8));
			*(unsigned int *) pixel = color;
	}
}

void	cub_drawLine(t_img *img, t_vec *from, t_vec *to, int color)
{
	int		steps;
	t_vec	delta;
	t_vec	inc;
	t_vec	draw;
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

/* 
 * starting from topleft corner
 */
void	cub_draw_rect(t_img *img, t_vec *start, double w, double h, unsigned int color)
{
	double x;
	double y;

	y = start->yd;
	while (y < start->yd + h)
	{
		x = start->xd;
		while ((double) x < start->xd + w)
		{
			cub_put_pix_to_img(img, (int) x, (int) y, color);
			x++;
		}
		y++;
	}
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

int	get_wall_color(char side, t_vec *dir)
{
	if (side == 'x')
	{
		if (dir->xd < 0)
			return (WALL_E);
		else
			return (WALL_W);
	}
	else
	{
		if (dir->yd < 0)
			return (WALL_S);
		else
			return (WALL_N);
	}
}

/*
 * centers vertically
 * reduces value if overflows viewport bottom or top
 */
void	adjust_y_for_viewport(double pro_height, t_vec *bottom, t_vec *top)
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


void	cub_apply_texture(t_data *data, int textureX, t_vec *from, double toY, double pro_height, int dir)
{
	double	step;
	double	pos;
	unsigned int color;
	double 	y;

	y = from->yd;
	step = (double) TEXTURE_SIZE / pro_height;
	pos = (y - WIN_H / 2 + pro_height / 2) * step;
	while (y < toY)
	{
		color = data->tex[dir][TEXTURE_SIZE * ((int)pos & (TEXTURE_SIZE - 1)) + textureX];
		pos += step;
		if (dir == NORTH || dir == SOUTH)
			color = (color >> 1) & 0x7F7F7F;
		cub_put_pix_to_img(data->field->display, (int) from->xd, (int) y, color);
		y++;
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
	adjust_y_for_viewport(pro_height, &bottom, &top);
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

void	cub_paint_ceiling_and_floor(t_data *data)
{
	t_vec *coord;

	coord = cub_init_vec_double(0, 0);
	cub_draw_rect(data->field->display, coord, WIN_W, WIN_H / 2, data->parsed_map->ceiling_color);
	coord->yd = (double) WIN_H / 2;
	cub_draw_rect(data->field->display, coord, WIN_W, WIN_H / 2, data->parsed_map->floor_color);
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

void	cub_draw_cone(t_data *data, t_img *img, t_vec *from, int degrees, int bisectlen)
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

t_vec	*cub_init_vec(int x, int y)
{
	t_vec	*point;

	point = ft_calloc(1, sizeof(t_vec));
	point->x = x;
	point->y = y;
	point->xd = (float)x;
	point->yd = (float)y;
	point->magnitude = 1;
	return (point);
}

t_vec	*cub_init_vec_double(double x, double y)
{
	t_vec	*point;

	point = ft_calloc(1, sizeof(t_vec));
	point->xd = x;
	point->yd = y;
	point->x = round(x);
	point->y = round(y);
	return (point);
}