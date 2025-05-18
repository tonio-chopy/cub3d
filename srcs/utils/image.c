#include "test.h"

void	cub_update_img_info(t_img *img, int bpp, int line_length, int endian)
{
	img->bpp = bpp;
	img->line_length = line_length;
	img->endian = endian;
}

void	cub_update_img_coord(t_img *img, int width, int height, t_vec *location)
{
	img->width = width;
	img->height = height;
	img->location = location;
}
