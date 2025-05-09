#include "test.h"

void	cub_put_pix_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = img->addr + (int) (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *) pixel = color;
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
void	cub_draw_rect(t_img *img, int xstart, int ystart, int w, int h, unsigned int color)
{
	int x;
	int	y;

	y = ystart;
	while (y < ystart + h)
	{
		x = xstart;
		while (x < xstart + w)
		{
			cub_put_pix_to_img(img, x, y, color);
			x++;
		}
		y++;
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