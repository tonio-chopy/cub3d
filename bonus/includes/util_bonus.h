/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:46:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/05 12:50:04 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_BONUS_H
# define UTIL_BONUS_H

# include "cub_bonus.h"

// ========= utils
// clean
void				cub_clean2d(void **array, int size, unsigned int bitmask,
						bool freeArr);
void				cub_clean_data(t_data *data);

// images
void				cub_clear_img(t_img *img);
void				cub_draw_help(t_data *data);
void				cub_update_img_info(t_img *img, int bpp, int line_length,
						int endian);
void				cub_update_img_coord(t_img *img, int width, int height,
						t_vec *location);

// clean bonus
void				cub_clean_minimap(t_data *data, t_minimap *minimap);
void				cub_clean_goal(t_data *data, t_goal *goal);
void				cub_clean_sprites(t_data *data);
void				cub_clean_bonus(t_data *data);

// clean img
void				cub_clean_ray(t_ray *ray);
void				cub_clean_img(t_data *data, t_img *img);
void				cub_clean_field(t_data *data, t_walls *walls);
void				cub_clean_mlx(t_mlx *mlx);
void				cub_clean_balls(t_data *data);

// colors
int					cub_rgb_to_int(double r, double g, double b);
void				cub_cpy_with_transparency(t_img *dest, t_img *from,
						int x_offset, int y_offset);
void				cub_put_pix_to_img(t_img *img, double x, double y,
						unsigned int color);
unsigned int		get_sprite_pixel_color(t_data *data, t_sprite *sprite,\
						int tex_x, int tex_y);

// sounds

enum e_sound
{
	ENSEMBLE,
	KIKI,
	ROJA,
	KICK,
	BOO,
	GOAL
};
void				cub_play_effect(t_data *data, int index);
void				cub_stop_audio(t_data *data, bool audio);
void				cub_play_song(t_data *data, int index);
void				cub_init_sound(t_data *data);

// errors
# define MSP_OPEN "Error\nopening file"
# define MSP_IVF "Error\ninvalid map path"
# define MSP_IVL "Error\ninvalid configuration line"					
# define MSP_UNK "Error\nunknown or misplaced element in .cub file"

# define MSP_MISSING "Error\nmissing informations"						// test
# define MSP_IVC "Error\ninvalid content after configuration"			// test
# define MSP_INVALID_COLOR "Error\ninvalid color"						// test
# define MSP_IVP "Error\ninvalid texture path"							// test
# define MSP_MTP "Error\nmissing texture path"							// test
# define MSP_ECT "Error\nextra content after texture path"				// test
# define MSP_DTP "Error\ncan't have two textures for one direction" 	// test
# define MSP_DFC "Error\nduplicate floor color"						// test
# define MSP_DCC "Error\nduplicate ceiling color"						// test

# define MSP_ELM "Error\nempty line in map content" 					// test
# define MSP_IVM "Error\ninvalid map line"								// test
# define MSP_MPP "Error\nmultiple player positions"					// test
# define MSP_MIP "Error\nmissing player position"						// test
# define MSP_NOT_CLOSED "Error\nmap is not closed or player not in map"// test

# define MSG_TEX "Error\nadding texture"
# define MSG_EMPTY_ENV "Error\nempty env var"
# define MSG_ALLOC "Error\nmemory allocation error"
# define MSG_USAGE "Error\nusage cub3D <map path>"
# define MSP_ERR "Error\nparsing error"

void				cub_handle_fatal(t_data *data, char *custom_msg);
void				cub_parse_error(t_data *data, char *msg);
void				cub_handle_fatal_parse(t_data *data, int fd, char *line,
						char *msg);
// mlx utils
void				cub_init_mlx(t_data *data);
t_img				*cub_init_img_from_xpm(t_data *data, int width, int height,
						char *filename);
t_img				*cub_init_img(t_data *data, int width, int height,
						t_vec *location);
int					cub_refresh(void *param);
void				cub_clear_img(t_img *img);

// utils bonus
int					cub_refresh_bonus(void *param);

#endif
