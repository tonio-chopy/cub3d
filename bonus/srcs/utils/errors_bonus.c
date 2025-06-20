/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:08 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/20 19:45:57 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_handle_fatal(t_data *data, char *custom_msg)
{
	if (!custom_msg)
		perror("cub3d:");
	else
		ft_printfd(2, "%s%s%s\n", P_YELLOW, custom_msg, P_NOC);
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
	cub_free_gnl(fd);
	close(fd);
	cub_handle_fatal(data, msg);
}
