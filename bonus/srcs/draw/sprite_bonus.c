/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/27 20:24:16 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

unsigned int	get_sprite_pixel_color(t_data *data, int tex_x, int tex_y)
{
	int	anim_index;
	int	index;
	// Valider les coordonnées pour éviter les segfaults
	if (tex_x < 0 || tex_x >= CUP_SIZE || tex_y < 0 || tex_y >= CUP_SIZE)
		return (INVISIBLE); // Ou une autre couleur de débogage
	anim_index = data->goal->cup_anim_count / 10;
	// L'index dans un tableau 1D est `y * largeur + x`
	index = tex_y * CUP_SIZE + tex_x;
	return (data->cup->sprites[anim_index][index]);
}

void	debug2cam(t_data *data, t_vec *p, t_cam *cam)
{
	// if (data->goal->cup_anim_count != 0)
	// 	return ;
	(void) data;
	printf("dir x %f y %f\n", cam->dir->xd, cam->dir->yd);
	printf("plane x %f y %f\n", cam->plane->xd, cam->plane->yd);
	printf("pos 2 x %f y %f\n", p->xd, p->yd);
	printf("magnitude plane %f and dir %f\n",
		data->cam->plane->magnitude, data->cam->dir->magnitude);
	printf("\n\n");
}

void	cub_draw_sprite(t_data *data, t_sprite *sprite)
{
	int				stripe;
	int				tex_x;
	int				tex_y;
	int				d;
	int				y;
	int				index;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
	int				sprite_width;
	double			relative_x;
	double			relative_y;
	double			transform_x;
	double			transform_y;
	double			inv_det;
	unsigned int	color;

	debug2cam(data, data->player_pos, data->cam);
	index = ft_strchri(data->parsed_map->elems, sprite->elem);
	if (index == -1)
		return ;
	sprite->pos = cub_get_center_coord_from_index(data, index);
	printf("sprite y %f x %f\n", sprite->pos->yd, sprite->pos->xd);
	// t_vec *trans = cub_init_vec_double(-data->player_pos->xd,
	// -data->player_pos->yd);
	// t_vec *translated = ft_translate_vector_new(sprite->pos, trans);
	printf("data cam angle %f\n", data->cam->angle);
	// t_vec *rotated = ft_rotate_vector_new(translated,
	// ft_to_rad(- data->cam->angle - 90));
	relative_x = sprite->pos->xd - data->player_pos->xd;
	relative_y = sprite->pos->yd - data->player_pos->yd;
	printf("relative y %f and x %f\n", relative_y, relative_x);
	printf("with trans matrix => relative y %f and x %f\n", relative_y,
		relative_x);
	inv_det = 1.0 / (data->cam->plane->xd * data->cam->dir->yd
			- data->cam->dir->xd * data->cam->plane->yd);
	printf("inv det = %f\n", inv_det);
	transform_x = inv_det * (data->cam->dir->yd * relative_x
			- data->cam->dir->xd * relative_y);
	transform_y = inv_det * (-data->cam->plane->yd * relative_x
			+ data->cam->plane->xd * relative_y);
	if (transform_y <= 0.1)
		return ;
	printf("sprite in cam space y %f x %f\n", transform_y, transform_x);
	// printf("with rot matrix => sprite in cam space y %f x %f\n",
	// rotated->yd, rotated->xd);
	// int sprite_screen_x = (int)((WIN_W / 2)
	// * (1.0 + rotated->xd / rotated->yd));
	sprite_screen_x = (int)(((double) WIN_W / 2.0)
			* (1.0 + (transform_x / transform_y)));
	printf("screen x = %d\n", sprite_screen_x);
	sprite_height = abs((int)(WIN_H / transform_y));
	draw_start_y = -sprite_height / 2 + WIN_H / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + WIN_H / 2;
	if (draw_end_y >= WIN_H)
		draw_end_y = WIN_H - 1;
	sprite_width = abs((int)(WIN_H / transform_y));
	printf("sprite width %d\n", sprite_width);
	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_end_x >= WIN_W)
		draw_end_x = WIN_W - 1;
	printf("drawing from %d to %d\n\n", draw_start_x, draw_end_x);
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		// Calcul de la coordonnée X de la texture
		tex_x = (int)(CUP_SIZE * (stripe - (-sprite_width / 2
						+ sprite_screen_x))
				* CUP_SIZE / sprite_width) / CUP_SIZE;
		// Condition de dessin :
		// 1. Le sprite est sur l'écran.
		// 2. Il est plus proche que,
		// le mur déjà dessiné (vérification du z-buffer).
		if (transform_y > 0 && stripe > 0 && stripe < WIN_W
			&& transform_y < data->zbuffer[stripe])
		{
			y = draw_start_y;
			while (y < draw_end_y)
			{
				// Calcul de la coordonnée Y de la texture
				d = y * CUP_SIZE - WIN_H
					* CUP_SIZE / 2 + sprite_height * CUP_SIZE / 2;
				tex_y = ((d * CUP_SIZE) / sprite_height) / CUP_SIZE;
				// Récupérer la couleur de la texture
				// Note: J'ai simplifié l'indexation de la texture.
				// Adaptez-la à votre format.
				// data->cup->sprites[anim_index][tex_y * CUP_SIZE + tex_x]
				color = get_sprite_pixel_color(data, tex_x, tex_y);
				// Si la couleur n'est pas transparente, on dessine le pixel.
				if (color != INVISIBLE)
				// INVISIBLE est souvent 0x00000000 ou 0xFF0000FF
					cub_put_pix_to_img(data->walls->img, stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}
