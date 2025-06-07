/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "types.h"

// Movement functions
void				cub_move_if_possible(t_data *data, t_vec *target,
						t_vec *move_vector);
void				cub_update_rotation(t_data *data);
void				cub_update_translation(t_data *data);

// Rotation handlers
int					handle_stop_rotate(t_data *data, int key);
int					handle_rotate(t_data *data, int key);
int					handle_mouse_rotate(int x, int y, void *param);

// Event handlers
int					handle_click_on_close(void *param);
int					cub_handle_no_event(void *param);
int					cub_handle_keypress(int key, void *param);
int					cub_handle_keyrelease(int key, void *param);

#endif
