#include "test.h"

void	cub_put_pix_to_img_inv(t_img *img, double x, double y, unsigned int color)
{
	char	*pixel;
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->addr + (int) (y * img->line_length + x * (img->bpp / 8));
		if (color != INVISIBLE)
			*(unsigned int *) pixel = color;
	}
}

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
		cub_put_pix_to_img_inv(img, round(draw.xd), round(draw.yd), color);
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
			cub_put_pix_to_img_inv(img, (int) x, (int) y, color);
			x++;
		}
		y++;
	}
}