/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/20 15:03:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

bool				check_args(int ac, char **env);
t_data				*cub_init_data(char **av);
void				cub_init_hooks(t_data *data);

// File validation
void				cub_check_file(t_data *data, char *filename);

// Player validation
void				cub_find_player(t_data *data, t_parsed_map *parsed_map);

// Map closure validation
void				check_map_closed(t_data *data, t_parsed_map *map);

// Map measurement
void				cub_measure_map(t_data *data, char *filename);

// Info parsing
bool				cub_are_infos_filled(t_data *data);
void				cub_try_add_texture_paths_and_colors(t_data *data,
						char *line);

// Info validation utilities 
void				cub_init_cardinal_codes(char **codes);
void				cub_set_ceiling_color(t_data *data, char *line,
						unsigned int color);
void				cub_set_floor_color(t_data *data, char *line,
						unsigned int color);

// Color parsing 
void				cub_add_ceiling_or_floor_color(t_data *data, char *trimmed,
						char *line, bool *has_matched);

// Texture parsing 
void				cub_handle_matching_code(t_data *data, int i, char *line,
						char *trimmed);

// Line processing
char				*cub_trim_map(char *line);
char				*cub_trim_full(char *line);
bool				cub_is_map_line(char *line);
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

// Color parsing
int					cub_parse_color(char *str, unsigned int *color);

// Map utilities
void				cub_compute_adjacent_indexes_x(t_parsed_map *map, int i,
						int *left_i, int *right_i);
void				cub_compute_adjacent_indexes_y(t_parsed_map *map, int i,
						int *up_i, int *down_i);
void				cub_check_map_not_started(t_data *data, char *line);

// Main parsing function
int					cub_parse_file(char *filename, t_data *data);

#endif
