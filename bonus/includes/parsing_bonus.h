#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "cub_bonus.h"

// ========= parse
# define VISITED 'X'

// Main parsing function
int					cub_parse_file(char *filename, t_data *data);

// colors
int					cub_parse_color(char *str, unsigned int *color);

// File validation
void				cub_check_file(t_data *data, char *filename);
void				cub_find_player(t_data *data, t_parsed_map *parsed_map);
void				check_map_closed(t_data *data, t_parsed_map *map);
void				cub_measure_map(t_data *data, char *filename);

// Info parsing
void				cub_try_add_texture_paths_and_colors(t_data *data,
char *line);
	
// Info validation utilities
void				cub_check_info_filled(t_data *data, char *line);
bool				cub_are_infos_filled(t_data *data);
void				cub_init_cardinal_codes(char **codes);
void				cub_set_ceiling_color(t_data *data, char *line,
						unsigned int color);
void				cub_set_floor_color(t_data *data, char *line,
						unsigned int color);
void				cub_add_ceiling_or_floor_color(t_data *data, char *trimmed,
						char *line, bool *has_matched);
void				cub_check_texture_path(t_data *data, int i, char *line,
						char *trimmed);
int					cub_parse_color(char *str, unsigned int *color);

// Line processing
char				*cub_trim_map(char *line);
char				*cub_trim_full(char *line);
void				cub_add_map_line(t_data *data, t_parsed_map *parsed_map,
						char *line, int i);

// Parsing validation utilities
bool				is_valid_number(char *str);
bool				is_only_whitespace(char *line);
bool				has_consecutive_commas(char *str);
int					count_commas(char *str);
int					count_elements(char **split);

// String utilities
char				*trim_whitespace(char *str);

// Map utilities
void				cub_compute_adjacent_indexes_x(t_parsed_map *map, int i,
						int *left_i, int *right_i);
void				cub_compute_adjacent_indexes_y(t_parsed_map *map, int i,
						int *up_i, int *down_i);
void				cub_check_info_filled(t_data *data, char *line);
bool				cub_is_map_line(char *line, bool is_bonus);
void				cub_add_map_line(t_data *data, t_parsed_map *parsed_map,
						char *line, int i);

#endif