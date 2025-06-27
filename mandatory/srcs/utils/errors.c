/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/20 19:47:35 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_handle_fatal(t_data *data, char *custom_msg)
{
	if (!custom_msg)
		perror("cub3d:");
	else
		ft_printfd(2, "%s%s%s\n", P_YELLOW, custom_msg, P_NOC);
	if (data)
		cub_clean_data(data);
	exit(EXIT_FAILURE);
}

void	cub_free_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	cub_handle_fatal_parse(t_data *data, int fd, char *line, char *msg)
{
	free(line);
	if (fd != -1)
	{
		cub_free_gnl(fd);
		close(fd);
	}
	cub_handle_fatal(data, msg);
}
