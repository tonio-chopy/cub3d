#include "test.h"

void	draw_map_elem(t_data *data, t_img *img, int index, char value)
{
	int		color;
	t_vec	*start;
	double	tilesize;
	t_shape	rect;

	tilesize = data->minimap->tilesize;
	if (value == ' ')
		color = INVISIBLE;
	else if (value == '1')
		color = MAP_WALL;
	else
		color = MAP_EMPTY;
	start = cub_get_topleftcoord_adjusted(data->parsed_map, data->minimap, \
index);
	if (data->debug == 'd')
		printf("drawing elem #%d (value %c) at x %d and y %d\n", index, value, \
start->x, start->y);
	init_shape(start, roundf(tilesize) - 1, RECTANGLE, &rect);
	rect.color = color;
	rect.heigth = roundf(tilesize) - 1;
	cub_draw_rect(img, &rect);
	free(start);
}

void	cub_draw_minimap(t_data *data)
{
	int		i;
	char	map_value;

	map_value = ' ';
	i = 0;
	while (i < data->parsed_map->nb_elems)
	{
		map_value = data->parsed_map->elems[i];
		draw_map_elem(data, data->minimap->map, i, map_value);
		i++;
	}
}

void	cub_draw_player(t_data *data)
{
	t_vec	player;

	if (data->debug == 'v')
		debug_data(data);
	player.xd = data->minimap->x_offset + data->player_pos->xd * \
data->minimap->tilesize;
	player.yd = data->minimap->y_offset + data->player_pos->yd * \
data->minimap->tilesize;
	cub_draw_fov(data, &player, 60, 100);
	cub_draw_player_cursor(data);
}

static void	fill_triangle(t_img *img, t_vec a, t_vec b, t_vec c, int color)
{
    int min_x = fmin(fmin(a.xd, b.xd), c.xd);
    int max_x = fmax(fmax(a.xd, b.xd), c.xd);
    int min_y = fmin(fmin(a.yd, b.yd), c.yd);
    int max_y = fmax(fmax(a.yd, b.yd), c.yd);

    for (int y = min_y; y <= max_y; y++)
    {
        for (int x = min_x; x <= max_x; x++)
        {
            double denom = ((b.yd - c.yd) * (a.xd - c.xd) + (c.xd - b.xd) * (a.yd - c.yd));
            double alpha = ((b.yd - c.yd) * (x - c.xd) + (c.xd - b.xd) * (y - c.yd)) / denom;
            double beta  = ((c.yd - a.yd) * (x - c.xd) + (a.xd - c.xd) * (y - c.yd)) / denom;
            double gamma = 1.0 - alpha - beta;

            if (alpha >= 0 && beta >= 0 && gamma >= 0)
                cub_pixel_put(img, x, y, color);
        }
    }
}

void	cub_draw_player_cursor(t_data *data)
{
    t_vec	center;
    t_vec	dir;
    t_vec	left, right, tip;
    double	angle;
    double	size;
    double	theta;

    center.xd = data->minimap->x_offset + data->player_pos->xd * data->minimap->tilesize;
    center.yd = data->minimap->y_offset + data->player_pos->yd * data->minimap->tilesize;

    dir.xd = data->cam->dir->xd;
    dir.yd = data->cam->dir->yd;
    ft_normalize_vector(&dir);


    size = data->minimap->tilesize * 0.7; 
    angle = atan2(dir.yd, dir.xd);        
    theta = 0.7;                          

   
    tip.xd = center.xd + cos(angle) * size;
    tip.yd = center.yd + sin(angle) * size;

    left.xd = center.xd + cos(angle + PI - theta) * (size * 0.7);
    left.yd = center.yd + sin(angle + PI - theta) * (size * 0.7);

    right.xd = center.xd + cos(angle + PI + theta) * (size * 0.7);
    right.yd = center.yd + sin(angle + PI + theta) * (size * 0.7);

	fill_triangle(data->minimap->map, tip, left, right, 0x0000FF);

    cub_drawline(data->minimap->map, &tip, &left, 0x0000FF);  
    cub_drawline(data->minimap->map, &left, &right, 0x0000FF);
    cub_drawline(data->minimap->map, &right, &tip, 0x0000FF);
}
