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
void				cub_clean_goal(t_goal *goal);
void				cub_clean_sprites(t_data *data);
void				cub_clean_bonus(t_data *data);

// clean img
void				cub_clean_ray(t_ray *ray);
void				cub_clean_img(t_data *data, t_img *img);
void				cub_clean_field(t_data *data, t_walls *walls);
void				cub_clean_mlx(t_mlx *mlx);
// colors
int					cub_rgb_to_int(double r, double g, double b);
void				cub_cpy_with_transparency(t_img *dest, t_img *from,
						int x_offset, int y_offset);
void				cub_put_pix_to_img(t_img *img, double x, double y,
						unsigned int color);


// errors
# define MSP_OPEN "error opening file"
# define MSP_IVF "invalid map path"
# define MSP_IVL "invalid configuration line"					
# define MSP_UNK "unknown or misplaced element in .cub file"

# define MSP_MISSING "missing informations"						// missingdirection
# define MSP_IVC "invalid content after configuration"
# define MSP_INVALID_COLOR "invalid color"
# define MSP_IVP "invalid texture path"							// invalidpath
# define MSP_MTP "missing texture path"							// missingtextpath
# define MSP_ECT "extra content after texture path"				// extracontent
# define MSP_DTP "can't have two textures for one direction" 	// duplicatedir
# define MSP_DFC "duplicate floor color"						// test
# define MSP_DCC "duplicate ceiling color"						// test

# define MSP_ELM "empty line in map content" 					// test
# define MSP_IVM "invalid map line"								// invalidchar
# define MSP_MPP "multiple player positions"					// two players
# define MSP_MIP "missing player position"						// missingplayer
# define MSP_PIM "player must be inside the map"				// player not inside
# define MSP_NOT_CLOSED "map is not closed"						// not closed

# define MSG_EMPTY_ENV "empty env var"
# define MSG_ALLOC "memory allocation error"
# define MSG_USAGE "usage cub3D <map path> [optional debug level from 1 to 2]"

void				cub_handle_fatal(t_data *data, char *custom_msg);
void				cub_parse_error(t_data *data, char *msg);
void				cub_handle_fatal_parse(t_data *data, int fd, char *line,
						char *msg);
// mlx utils
t_mlx				*cub_init_mlx(void);
t_img				*cub_init_img_from_xpm(t_data *data, int width, int height,
						char *filename);
t_img				*cub_init_img(t_data *data, int width, int height,
						t_vec *location);
int					cub_refresh(void *param);
void				cub_clear_img(t_img *img);

// utils bonus
int					cub_refresh_bonus(void *param);

#endif