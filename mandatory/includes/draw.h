/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "types.h"

// Basic drawing functions
void				cub_drawline(t_img *img, t_vec *from, t_vec *to, int color);
void				cub_draw_rect(t_img *img, t_shape *rect);
void				init_shape(t_vec *start, double width, t_shapetype type,
						t_shape *shape);

// Scene drawing
void				cub_draw_ceiling_and_floor(t_data *data);

// Wall drawing
void				cub_drawline_wall(t_data *data, double dist, t_ray *ray,
						int screen_x);
void				cub_draw_walls(t_data *data);

#endif
