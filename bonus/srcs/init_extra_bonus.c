/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_extra_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:50:28 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/22 12:50:35 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_init_sprite(t_data *data)
{
	t_sprite	*sprite;

	sprite = ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
		cub_handle_fatal(data, MSG_ALLOC);
	data->sprite = sprite;
}
