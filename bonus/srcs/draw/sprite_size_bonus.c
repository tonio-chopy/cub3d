/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_size_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/25 17:31:58 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void cub_compute_sprite_dist(t_data *data, t_vec *dist, char elem, t_sprite *sprite)
{
	int		ball_i;
	t_vec	*pos;
	// t_vec	*trans;
	// t_vec	*rot;
	// double	angle_from_dir;

	ball_i = ft_strchri(data->parsed_map->elems, elem);
	if (elem == E_CUP)
		ball_i = data->parsed_map->opened_door_index;
	// printf("door index = %d\n", data->parsed_map->opened_door_index);
	pos = cub_get_coord_from_index(data, ball_i);
	if (!pos)
		cub_handle_fatal(data, MSG_ALLOC);
	// printf("player pos x %f y %f\n", data->player_pos->xd, data->player_pos->yd);
	pos->xd += 0.5;
	pos->yd += 0.5;

	// pos = ft_translate_vector_new(pos, data->player_pos);
	// ft_rotate_vector(pos, -data->cam->angle);

	dist->xd = pos->xd;
	dist->yd = pos->yd;
	dist->xd = pos->xd - data->player_pos->xd;
	dist->yd = pos->yd - data->player_pos->yd;
	dist->magnitude = 1;

	printf("dist after tranform y %f x %f\n", dist->yd, dist->xd);
	// trans = ft_translate_vector_new(pos, dist);
	// data->cam->plane = ft_rotate_vector_new(trans, ft_to_rad(-data->cam->angle));
	sprite->distance = sqrt(dist->xd * dist->xd + dist->yd * dist->yd);
	free(pos);
	// if (elem == E_CUP)
	// 	printf("sprite dist is %f\n", sprite->distance);
}

void	debug_cam(t_cam *cam)
{
	printf("cam dir x %f y %f\n", cam->dir->xd, cam->dir->yd);
	printf("cam plane x %f y %f\n", cam->plane->xd, cam->plane->yd);
}

void test_angle_vector_consistency(t_data *data)
{
    // Calculer le vecteur à partir de l'angle
    double calc_x = cos(ft_to_rad(data->cam->angle));
    double calc_y = -sin(ft_to_rad(data->cam->angle)); // - car y inversé
    
    printf("Stored vector: (%.2f, %.2f)\n", data->cam->dir->xd, data->cam->dir->yd);
    printf("Calculated from angle: (%.2f, %.2f)\n", calc_x, calc_y);
    
    // Ils devraient être identiques (± epsilon)
}

void cub_compute_cup_size(t_data *data, int *code, char elem)
{
	// double invdet;
	// double det;
	// double	angleFromDir;
	// // t_vec relative_pos;
	t_vec dist;
	// t_vec cup_trans;
	t_vec *pos;
	*code = 1;
	// cub_compute_sprite_dist(data, &dist, elem, data->cup);

	// test_angle_vector_consistency(data);
	int index;
	index = ft_strchri(data->parsed_map->elems, elem);
	if (elem == E_CUP)
		index = data->parsed_map->opened_door_index;


	pos = cub_get_coord_from_index(data, index);
	pos->xd += 0.5;
	pos->yd += 0.5;
	pos->magnitude = 1;



	// t_vec *translate = cub_init_vec_double(-data->player_pos->xd, -data->player_pos->yd);
	// translation
	// dist = *ft_translate_vector_new(pos, translate);
	// rotation
	// printf("dist before rotate at angle %f y %f x %f\n", data->cam->angle - 180, dist.yd, dist.xd);
	// // ft_rotate_vector(&dist, ft_to_rad(data->cam->angle));
	// printf("dist after rotate y %f x %f\n", dist.yd, dist.xd);

	// det = data->cam->plane->xd * data->cam->dir->yd - data->cam->plane->yd * data->cam->dir->xd;
	// if (det == 0)
	// 	invdet = 1.0 / 0.0000001;
	// else
	// 	invdet = 1.0 / det;
	// dist.xd = invdet * (data->cam->dir->yd * dist.xd - data->cam->dir->xd * dist.yd);
	// dist.yd = invdet * (data->cam->plane->xd * dist.yd - data->cam->plane->yd * dist.xd);
	// if (dist.yd < 0)
	// 	return ;

	dist.xd = pos->xd - data->player_pos->xd;
	dist.yd = pos->yd - data->player_pos->yd;
	dist.magnitude = 1;

	double sprite_relative_x = pos->xd - data->player_pos->xd;
    double sprite_relative_y = pos->yd - data->player_pos->yd;
	
	printf("angle is %f\n", data->cam->angle);

	data->cam->plane->xd = FOV_SCALE * data->cam->dir->yd;
	data->cam->plane->xd = -FOV_SCALE * data->cam->dir->xd;

 	double inv_det = 1.0 / (data->cam->plane->xd * data->cam->dir->yd - data->cam->dir->xd * data->cam->plane->yd);

    // Formule de transformation standard pour un raycaster
    double transform_x = inv_det * (data->cam->dir->yd * sprite_relative_x - data->cam->dir->xd * sprite_relative_y);
    double transform_y = inv_det * (-data->cam->plane->yd * sprite_relative_x + data->cam->plane->xd * sprite_relative_y); // C'est la profondeur


    // double temp_x = dist.xd;
    // double temp_y = dist.yd;
	// ft_rotate_vector(&dist, ft_to_rad(data->cam->angle + 90));
	// double cos_angle = cos(ft_to_rad(data->cam->angle));
    // double sin_angle = sin(ft_to_rad(data->cam->angle));
    
    
	// printf("before rotate dist y %f x %f\n", dist.yd, dist.xd);
    // dist.xd = cos_angle * temp_x - sin_angle * temp_y;  // X dans l'espace caméra
    // dist.yd = sin_angle * temp_x + cos_angle * temp_y;  // Y dans l'espace caméra (profondeur)

	printf("after dist y %f x %f\n", transform_y, transform_x);
    if (transform_y <= 0.1) {
        printf("Cup behind camera, not rendering\n");
        return;
    }

// 	printf("\n=== TEST ROTATION ===\n");
// printf("Camera angle: %f°\n", data->cam->angle);
// printf("Camera direction vector: (%.2f, %.2f)\n", data->cam->dir->xd, data->cam->dir->yd);
// printf("Object world position: (%.2f, %.2f)\n", pos->xd, pos->yd);
// printf("Player world position: (%.2f, %.2f)\n", data->player_pos->xd, data->player_pos->yd);
// // printf("Before rotation: (%.2f, %.2f)\n", temp_x, temp_y);
// printf("After rotation: (%.2f, %.2f)\n", dist.xd, dist.yd);

	// Test de cohérence
// double expected_dir_x = cos(ft_to_rad(data->cam->angle));
// double expected_dir_y = sin(ft_to_rad(data->cam->angle)); // -sin car Y inversé

// printf("Stored dir: (%.2f, %.2f)\n", data->cam->dir->xd, data->cam->dir->yd);
// printf("Expected dir: (%.2f, %.2f)\n", expected_dir_x, expected_dir_y);
	data->cup->screenx = (int)((WIN_W / 2) * (1 + transform_x / transform_y));
	data->cup->distance = transform_y;
	
	if (data->cup->screenx < 0 || data->cup->screenx >= WIN_W || data->zbuffer[data->cup->screenx] < data->cup->distance)
		return;
	// data->cup->distance = sqrt(dist.xd * dist.xd + dist.yd * dist.yd);
// if (elem == E_CUP && data->cup->distance < 0.2)
// 		return;
	// printf("dir angle %f\n", data->cam->angle);
	// debug_cam(data->cam);
	// printf("cam dir y %f x %f\n", data->cam->dir->yd, data->cam->dir->xd);
	// printf("cam plane y %f x %f\n", data->cam->plane->yd, data->cam->plane->xd);
	// printf("cup dist x %f y %f\n", dist.xd, dist.yd);


	// Calcul de la projection X
    // double normalized_x = dist.xd / dist.yd;
    // double tan_half_fov = tan(ft_to_rad(FOV_DEGREES / 2.0));
	//  double screen_x = normalized_x / tan_half_fov;
    // data->cup->screenx = (int)((screen_x + 1.0) * (WIN_W / 2.0));

	// double fov_rad = ft_to_rad(FOV_DEGREES / 2);
	// double camx = 2 * (dist.xd / dist.yd) / tan(fov_rad);
	// printf("camx %f\n", camx);
	// angleFromDir = ft_to_rad(acos(dist.yd / data->cup->distance));	
	// printf("angle from dir %f\n", angleFromDir);
	// data->cup->screenx = (int) (1 + camx) * WIN_W / 2.0;
	// if (data->cup->screenx < 0 || data->cup->screenx >= WIN_W)
	// 	return ;
	// data->cup->screenx = (int)((FOV_DEGREES / 2 - angleFromDir) / FOV_DEGREES) * (WIN_W);
	// if (data->zbuffer[data->cup->screenx] < data->cup->distance)
	// 	return ;
	printf("Cup position: screen X = %d, camera space: x=%f, y=%f\n", 
        data->cup->screenx, transform_x, transform_y);
	// printf("det = %f, cup dist x = %f y %f - transform x %f y %f\n", det, cup_dist.xd, cup_dist.yd, relative_pos.xd, relative_pos.yd);
	// if (relative_pos.yd <= 0)
	// 	return;
	// double angle = acos(cup_dist.xd)
	// data->cup->screenx = (int)(((double)WIN_W * 0.5) * (1.0 + relative_pos.xd / relative_pos.yd));
	data->cup->sprite_size = abs((int)(WIN_H / transform_y));
	*code = 0;
}

void cub_compute_ball_size(t_data *data, int *code, char elem)
{
	double invdet;
	t_vec relative_pos;
	t_vec ball_dist;
	double	angleFromDir;
	double	tanPlane;

	*code = 1;
	cub_compute_sprite_dist(data, &ball_dist, elem, data->ball);
	if (elem == E_BALL && data->ball->distance < 0.2)
		return;
	angleFromDir = ft_to_deg(acos(ball_dist.xd / data->ball->distance));
	tanPlane = ft_to_deg(tan(angleFromDir));
	if (angleFromDir < 0)
		data->ball->screenx = (int)(((double)WIN_W * 0.5) * (((FOV_DEGREES / 2) - fabs(angleFromDir)) / FOV_DEGREES));
	else
		data->ball->screenx = (int)(((double)WIN_W * 0.5) * (((FOV_DEGREES / 2) + fabs(angleFromDir)) / FOV_DEGREES));
	invdet = 1.0 / (data->cam->plane->xd * data->cam->dir->yd - data->cam->dir->xd * data->cam->plane->yd);
	relative_pos.xd = invdet * (data->cam->dir->yd * ball_dist.xd - data->cam->dir->xd * ball_dist.yd);
	relative_pos.yd = invdet * (-data->cam->plane->yd * ball_dist.xd + data->cam->plane->xd * ball_dist.yd);
	if (relative_pos.yd <= 0)
		return;
	// data->ball->screenx = (int)(((double)WIN_W * 0.5) * (1.0 + relative_pos.xd / relative_pos.yd));
	data->ball->sprite_size = abs((int)(WIN_H / relative_pos.yd));
	*code = 0;
}
