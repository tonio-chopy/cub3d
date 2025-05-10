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
void	cub_drawLine(t_img *img, t_point *from, t_point *to)
{
	int		steps;
	t_point	delta;
	t_point	inc;
	t_point	draw;
	int		i;

	delta.x = to->x - from->x;
	delta.y = to->y - from->y;
	if (abs(delta.x) > abs(delta.y))
		steps = abs(delta.x);
	else
		steps = abs(delta.y);
	inc.xf = delta.x / (float) steps;
	inc.yf = delta.y / (float) steps;
	draw.xf = (float) from->x;
	draw.yf = (float) from->y;
	i = 0;
	while (i < steps)
	{
		cub_put_pix_to_img(img, round(draw.xf), round(draw.yf), L_RED);
		draw.xf += inc.xf;
		draw.yf += inc.yf;
		i++;
	}
}

// starting from topleftmost corner
void	cub_draw_rect(t_img *img, t_point *start, int w, int h, unsigned int color)
{
	int x;
	int	y;

	y = start->y;
	while ((float) y < start->yf + h)
	{
		x = start->x;
		while ((float) x < start->xf + w)
		{
			// printf("putting pix of color %x at x %d and y %d\n", color, x, y);
			cub_put_pix_to_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	cub_drawLine_angle(t_img *img, t_point *from, t_point *norm_vector, int degrees, float len)
{
	t_point	to;
	float	radians;
	float	rotx;
	float	roty;

	radians = to_rad(degrees);
	rotx = norm_vector->xf * cos(radians) - norm_vector->yf * sin(radians);
	roty = norm_vector->xf * sin(radians) - norm_vector->yf * cos(radians);
	to.x = round(from->x + rotx * len);
	to.y = round(from->y + roty * len);
	cub_drawLine(img, from, &to);
}

void	cub_draw_cone(t_img *img, t_point *from, t_point *norm_vector, int degrees, int bisectlen)
{
	int		i;

	i = -(degrees / 2);
	while (i < degrees / 2)
	{
		cub_drawLine_angle(img, from, norm_vector, i, bisectlen);
		i++;
	}
}

t_point	*init_point(int x, int y)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	point->x = x;
	point->y = y;
	point->xf = (float)x;
	point->yf = (float)y;
	return (point);
}

t_point	*init_pointf(float x, float y)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	point->xf = x;
	point->yf = y;
	point->x = round(x);
	point->y = round(y);
	return (point);
}