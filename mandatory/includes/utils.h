/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

// Cleanup functions
void				cub_clean2d(void **array, int size, unsigned int bitmask,
						bool freeArr);
void				cub_clean_data(t_data *data);
void				cub_clean_ray(t_ray *ray);
void				cub_clean_img(t_data *data, t_img *img);
void				cub_clean_field(t_data *data, t_walls *walls);
void				cub_clean_mlx(t_mlx *mlx);

// Color functions
int					cub_rgb_to_int(double r, double g, double b);
void				cub_cpy_with_transparency(t_img *dest, t_img *from,
						int x_offset, int y_offset);
void				cub_put_pix_to_img(t_img *img, double x, double y,
						unsigned int color);

// Error handling
void				cub_handle_fatal(t_data *data, char *custom_msg);
void				cub_parse_error(t_data *data, char *msg);
void				cub_handle_fatal_parse(t_data *data, int fd, char *line,
						char *msg);

// MLX utilities
t_mlx				*cub_init_mlx(void);
t_img				*cub_init_img_from_xpm(t_data *data, int width, int height,
						char *filename);
t_img				*cub_init_img(t_data *data, int width, int height,
						t_vec *location);
int					cub_refresh(void *param);
void				cub_clear_img(t_img *img);

// Image utilities
void				cub_update_img_info(t_img *img, int bpp, int line_length,
						int endian);
void				cub_update_img_coord(t_img *img, int width, int height,
						t_vec *location);

#endif
