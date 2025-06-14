/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/14 16:48:06 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	cub_cleanup_gnl(void)
{
	int		dummy_pipe[2];
	char	*line;
	int		i;

	i = 0;
	while (i < 10)
	{
		if (pipe(dummy_pipe) == 0)
		{
			close(dummy_pipe[1]);
			line = get_next_line(dummy_pipe[0]);
			free(line);
			close(dummy_pipe[0]);
		}
		i++;
	}
}
