#include "test.h"

void    copy_texture(t_data *data, void *img, int img_w, int img_h, int *tab)
{
    int    *img_data;
    int x;
    int y;
    int xsrc;
    int ysrc;
    int bpp;
    int size_line;
    int endian;
    double scaleX;
    double scaleY;

    (void) data;
    img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
    y = 0;
    if (bpp != 32)
    {
        ft_puterr("texture format not supported\n");
        return ;
    }
    scaleX = (double) img_w / TEXTURE_SIZE;
    scaleY = (double) img_h / TEXTURE_SIZE;
    while (y < TEXTURE_SIZE)
    {
        x = 0;
        while (x < TEXTURE_SIZE)
        {
            ysrc = y * scaleY;
            xsrc = x * scaleX;
            tab[y * TEXTURE_SIZE + x] = img_data[(int)ysrc * size_line / 4 + (int) xsrc];
            x++;
        }
        y++;
    }
}

int    *cub_read_texture(t_data *data, char *file)
{
    int    *tab;
    void   *img_ptr;
    int    img_w;
    int    img_h;

    tab = ft_calloc(TEXTURE_SIZE * TEXTURE_SIZE, sizeof(int));
    if (!tab)
        cub_handle_fatal(data, "error init texture tab\n");
    img_ptr = mlx_xpm_file_to_image(data->mlx->mlx, file, &img_w, &img_h);
    if (!img_ptr)
    {
        free(tab);
        cub_handle_fatal(data, "error creating texture img\n");   
    }

    copy_texture(data, img_ptr, img_w, img_h, tab);
    mlx_destroy_image(data->mlx->mlx, img_ptr);
    return (tab);
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
		cub_put_pix_to_img(data->walls->img, (int) from->xd, (int) y, color);
		y++;
	}
}
