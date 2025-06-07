/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "types.h"

// Raycast algorithm
void				cub_iter_ray(t_data *data, t_ray *ray);
void				compute_increments(t_ray *ray, t_vec *player);
double				cub_measure_dist_to_wall(t_data *data,
						t_vec *ray_dirvector);
double				compute_dist(t_data *data, t_ray *ray, char side);

// Ray initialization
void				cub_init_ray(t_data *data, t_vec *ray_dirvector);
void				reinit_ray(t_data *data, t_vec *ray_dirvector);

// Texture handling
int					*cub_read_texture(t_data *data, char *file);
void				cub_apply_texture(t_data *data, t_vec *from, double toY,
						t_ray *ray);

// Camera initialization
void				cub_init_cam(t_data *data);
void				cub_init_graphics(t_data *data);

#endif
