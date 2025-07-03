/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:46:11 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/03 17:26:41 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIM_BONUS_H
# define ANIM_BONUS_H

# include "cub_bonus.h"

// doors
void				handle_open(t_data *data, int key);
void				handle_close(t_data *data, int key);

// shoot
void				handle_shoot(t_data *data, int key);
void				init_random(void);
double				cub_measure_dist_to_opened_door(t_data *data,
						t_vec *ray_dirvector);
int					cub_merge_goal_col(t_data *data, t_ray *ray, double pos,
						double texture_x);
int					cub_get_ball_col(t_data *data, t_ray *ray, double pos,
						double texture_x);
void				cub_apply_ball(t_data *data, t_vec *from, double toY,
						t_ray *ray);
void				cub_update_goal_anim(t_data *data);
void				cub_compute_cup_size(t_data *data, int *code, char elem);

// flag
# define FR_BLUE 0x002395ED
# define FR_WHITE 0x00FFFFFF
# define FR_RED 0x00FF5050
# define ES_RED 0x00FF5050
# define ES_YELLOW 0x00FFCC00

void				cub_draw_flags(t_data *data);

// help
# define HELP_X 30
# define HELP_Y 600
# define HELP_W 200
# define HELP_H 150
# define HELP_COL 0xEE000000
# define HELP_TEXT 0x00FFFFFF

void				cub_draw_help(t_data *data);

#endif