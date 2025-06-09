/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:12 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/09 17:34:14 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOOT_BONUS_H
# define SHOOT_BONUS_H

#include "test.h"
#include <time.h>

void	handle_shoot(t_data *data, int key);
void	handle_open(t_data *data, int key);
void	handle_close(t_data *data, int key);
void	init_random(void);

double	cub_measure_dist_to_opened_door(t_data *data, t_vec *ray_dirvector);
#endif
