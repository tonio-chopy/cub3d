/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:21 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/21 16:09:34 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_check_file(t_data *data, char *filename)
{
	int		fd;
	int		len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4))
		cub_handle_fatal(data, MSP_IVF);
	fd = open(filename, R_OK);
	if (fd == -1)
		cub_handle_fatal(data, MSP_OPEN);
	close(fd);
}
