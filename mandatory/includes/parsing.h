/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "types.h"

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

// Line processing
char				*cub_trim_map(char *line);
char				*cub_trim_full(char *line);
bool				cub_is_map_line(char *line);
void				cub_add_map_line(t_data *data, t_parsed_map *parsed_map,
						char *line, int i);

// Parsing utilities
int					cub_parse_color(char *str, unsigned int *color);
void				cub_compute_adjacent_indexes_x(t_parsed_map *map, int i,
						int *left_i, int *right_i);
void				cub_compute_adjacent_indexes_y(t_parsed_map *map, int i,
						int *up_i, int *down_i);
void				cub_check_map_not_started(t_data *data, char *line);

// Main parsing function
int					cub_parse_file(char *filename, t_data *data);

#endif
