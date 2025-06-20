/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:21 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/20 14:59:27 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_check_file(t_data *data, char *filename)
{
	int		fd;
	int		len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4))
		cub_handle_fatal(data, MSP_INVALID_FILENAME);
	fd = open(filename, R_OK);
	if (fd == -1)
		cub_handle_fatal(data, MSP_OPEN);
	close(fd);
}
