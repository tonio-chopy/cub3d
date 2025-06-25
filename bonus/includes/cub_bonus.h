/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:16 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/25 15:55:48 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include "../../mlx/mlx.h"
# include "../libft/includes/libft.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "const_bonus.h"
# include "struct_bonus.h"
# include "parsing_bonus.h"
# include "anim_bonus.h"
# include "util_bonus.h"

// ========= init
t_data				*cub_init_data(char **av);
void				cub_init_ball(t_data *data);
void				cub_init_cup(t_data *data);
void				cub_init_bonus(t_data *data);
void				cub_init_hooks(t_data *data);
bool				check_args(int ac, char **env);
void				debug_elems(t_parsed_map *map, char *elems);

// ======== draw
// basic
void				cub_drawline(t_img *img, t_vec *from, t_vec *to, int color);
void				cub_draw_rect(t_img *img, t_shape *rect);
void				init_shape(t_vec *start, double width, t_shapetype type,
						t_shape *shape);
// shapes
void				cub_draw_fov(t_data *data, t_vec *from, int degrees,
						int bisectlen);
void				cub_draw_ceiling_and_floor(t_data *data);
// walls
void				cub_drawline_wall(t_data *data, double dist, t_ray *ray,
						int screen_x);
void				cub_draw_walls(t_data *data);
// sprite ball
void				cub_draw_ball(t_data *data);
void				cub_compute_ball_size(t_data *data, int *code, char elem);
void				cub_compute_sprite_dist(t_data *data, t_vec *ball_dist, \
						char elem, t_sprite *sprite);
void				cub_draw_cup(t_data *data);

// ========= hooks
// movements
# define FOV_DEGREES 66 				// ensure coherent with FOV_SCALE
# define FOV_SCALE 0.649407f 			// tan (FOV_DEGREES / 2)
# define ROTATION_SPEED 0.03f 			// radians per frame
# define MOVEMENT_SPEED 0.03f 			// cell per frame
# define MOVEMENT_SECURITY 0.1f 		// min distance between wall and player

void				cub_move_if_possible(t_data *data, t_vec *target,
						t_vec *move_vector);
void				cub_update_rotation(t_data *data);
void				cub_update_translation(t_data *data);
// rotate
int					handle_stop_rotate(t_data *data, int key);
int					handle_rotate(t_data *data, int key);
int					handle_mouse_rotate(int x, int y, void *param);
// hooks
# define K_ESCAPE 65307
# define K_LEFT 65361
# define K_UP 65362
# define K_RIGHT 65363
# define K_DOWN 65364
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_H 104

int					handle_click_on_close(void *param);
int					cub_handle_no_event(void *param);
int					cub_handle_keypress(int key, void *param);
int					cub_handle_keyrelease(int key, void *param);

// ========= maps
// cam
void				cub_update_cam_vector(t_data *data);
void				cub_init_cam(t_data *data);
// coord
t_vec				*cub_get_topleftcoord_adjusted(t_parsed_map *map,
						t_minimap *mini, int index);
t_vec				*cub_get_centercoord_norm(t_parsed_map *map, int index);
// minimap
void				cub_draw_minimap(t_data *data);
void				cub_draw_player(t_data *data);
// init
void				cub_init_graphics(t_data *data);
// init tex bonus
void				cub_get_goal_tex(t_data *data);

// ========= maths
# define PI 3.14159265358979323846f
// vectors
t_vec				*cub_init_vec(int x, int y);
t_vec				*cub_init_vec_double(double x, double y);
// angles
double				ft_to_rad(double degrees);
double				ft_to_deg(double radians);
double				ft_vector_len(t_vec *p);
double				ft_get_angle_between_vec(t_vec *u, t_vec *v);
// vector ops
void				ft_multiply_vector(t_vec *p, double factor);
t_vec				*ft_rotate_vector_new(t_vec *p, double angle_rad);
t_vec				*ft_translate_vector_new(t_vec *p, t_vec *trans);
void				ft_rotate_vector(t_vec *p, double angle_rad);
double				ft_vector_scalar_product(t_vec *u, t_vec *v);
void				ft_normalize_vector(t_vec *p);
// matrix
void				multiply_matrix(t_vec *p, double **matrix);
double				**get_2drotation_matrix(double angle_rad);
double				**get_2dtranslation_matrix(t_vec *v);
void				clean_3dmatrix(double **m, int size);

// ========= raycast
void				cub_iter_ray(t_data *data, t_ray *ray);
void				compute_increments(t_ray *ray, t_vec *player);
double				cub_measure_dist_to_wall(t_data *data,
						t_vec *ray_dirvector);
double				cub_measure_dist_to_ball(t_data *data,
						t_vec *ray_dirvector);
double				compute_dist(t_data *data, t_ray *ray, char side);
// check
int					get_direction(char side, t_vec *dir);
// init
void				cub_init_ray(t_data *data, t_vec *ray_dirvector);
void				reinit_ray(t_data *data, t_vec *ray_dirvector);
// textures
# define TEXTURE_SIZE	1024
# define BALL_SIZE		1024
# define CUP_SIZE		1024

int					*cub_read_texture(t_data *data, char *file);
void				cub_apply_texture(t_data *data, t_vec *from, double toY,
						t_ray *ray);
t_vec				*cub_get_coord_from_index(t_data *data, int index);
t_vec				*cub_get_center_coord_from_index(t_data *data, int index);
void				cub_get_goal_tex(t_data *data);

#endif
