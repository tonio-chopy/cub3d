/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:54 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/13 13:12:57 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

/*
 * passing 0b1001 will free index 0 and 4
 */
void	cub_clean2d(void **array, int size, unsigned int bitmask, bool freeArr)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		if ((bitmask & (1 << i)) != 0)
			free(array[i]);
		i++;
	}
	if (freeArr)
		free(array);
}

void	cub_clean_parsed(t_parsed_map *parsed)
{
	if (!parsed)
		return ;
	free(parsed->elems);
	if (parsed->paths)
	{
		free(parsed->paths[0]);
		free(parsed->paths[1]);
		free(parsed->paths[2]);
		free(parsed->paths[3]);
	}
	free(parsed->paths);
	free(parsed);
}

void	cub_clean_cam(t_cam *cam)
{
	if (cam->dir)
		free(cam->dir);
	if (cam->plane)
		free(cam->plane);
	free(cam);
}

void	cub_clean_text(int **tab)
{
	int	i;

	i = 0;
	while (i < 28)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	cub_clean_data(t_data *data)
{
	if (data->minimap)
		cub_clean_minimap(data, data->minimap);
	if (data->walls)
		cub_clean_field(data, data->walls);
	if (data->mlx)
		cub_clean_mlx(data->mlx);
	if (data->parsed_map)
		cub_clean_parsed(data->parsed_map);
	if (data->cam)
		cub_clean_cam(data->cam);
	if (data->player_pos)
		free(data->player_pos);
	if (data->ray)
		cub_clean_ray(data->ray);
	if (data->tex)
		cub_clean_text(data->tex);
	if (data->goal)
		cub_clean_goal(data->goal);
	if (data->sprites)
		cub_clean_sprites(data);
	free(data);
}
