/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/26 16:35:11 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

unsigned int get_sprite_pixel_color(t_data *data, int tex_x, int tex_y)
{
    // Valider les coordonnées pour éviter les segfaults
    if (tex_x < 0 || tex_x >= CUP_SIZE || tex_y < 0 || tex_y >= CUP_SIZE)
        return (INVISIBLE); // Ou une autre couleur de débogage

    int anim_index = data->goal->cup_anim_count / 10;
    // L'index dans un tableau 1D est `y * largeur + x`
    int index = tex_y * CUP_SIZE + tex_x;
    return (data->cup->sprites[anim_index][index]);
}

void	debug2cam(t_cam *cam)
{
	printf("dir x %f y %f - %d %d\n", cam->dir->xd, cam->dir->yd, cam->dir->x, cam->dir->y);
	printf("plane x %f y %f - %d %d\n", cam->plane->xd, cam->plane->yd, cam->plane->x, cam->plane->y);
	printf("pos x %f y %f - %d %d\n", cam->orig->xd, cam->orig->yd, cam->orig->x, cam->orig->y);
}

void	cub_draw_sprite(t_data *data, t_sprite *sprite)
{
	int	index;
	debug2cam(data->cam);
	index = ft_strchri(data->parsed_map->elems, sprite->elem);
	if (index == -1)
		return ;
	sprite->pos = cub_get_center_coord_from_index(data, index);
	double relative_x = sprite->pos->xd - data->player_pos->xd;
	double relative_y = sprite->pos->yd - data->player_pos->yd;
	double inv_det = 1.0 / (data->cam->plane->xd * data->cam->dir->yd - data->cam->dir->xd * data->cam->plane->yd);
double transform_x = inv_det * (data->cam->dir->yd * relative_x - data->cam->dir->xd * relative_y);
    double transform_y = inv_det * (-data->cam->plane->yd * relative_x + data->cam->plane->xd * relative_y);
	if (transform_y <= 0.1)
		return ;
	int sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));
	int sprite_height = abs((int)(WIN_H / transform_y));
    int draw_start_y = -sprite_height / 2 + WIN_H / 2;
    if (draw_start_y < 0) draw_start_y = 0;
    int draw_end_y = sprite_height / 2 + WIN_H / 2;
    if (draw_end_y >= WIN_H) draw_end_y = WIN_H - 1;
	int sprite_width = abs((int)(WIN_H / transform_y));
	int draw_start_x = -sprite_width / 2 + sprite_screen_x;
    if (draw_start_x < 0) draw_start_x = 0;
    int draw_end_x = sprite_width / 2 + sprite_screen_x;
    if (draw_end_x >= WIN_W) draw_end_x = WIN_W - 1;
	int stripe;
    int	tex_x;
    int	tex_y;
    int	d;
    unsigned int color;

    stripe = draw_start_x;
    while (stripe < draw_end_x)
    {
        // Calcul de la coordonnée X de la texture
        tex_x = (int)(CUP_SIZE * (stripe - (-sprite_width / 2 + sprite_screen_x)) * CUP_SIZE / sprite_width) / CUP_SIZE;

        // Condition de dessin :
        // 1. Le sprite est sur l'écran.
        // 2. Il est plus proche que le mur déjà dessiné (vérification du z-buffer).
        if (transform_y > 0 && stripe > 0 && stripe < WIN_W && transform_y < data->zbuffer[stripe])
        {
            int y = draw_start_y;
            while (y < draw_end_y)
            {
                // Calcul de la coordonnée Y de la texture
                d = y * CUP_SIZE - WIN_H * CUP_SIZE / 2 + sprite_height * CUP_SIZE / 2;
                tex_y = ((d * CUP_SIZE) / sprite_height) / CUP_SIZE;

                // Récupérer la couleur de la texture
                // Note: J'ai simplifié l'indexation de la texture. Adaptez-la à votre format.
                // data->cup->sprites[anim_index][tex_y * CUP_SIZE + tex_x]
                color = get_sprite_pixel_color(data, tex_x, tex_y);

                // Si la couleur n'est pas transparente, on dessine le pixel.
                if (color != INVISIBLE) // INVISIBLE est souvent 0x00000000 ou 0xFF0000FF
                {
                    cub_put_pix_to_img(data->walls->img, stripe, y, color);
                }
                y++;
            }
        }
        stripe++;
    }
}