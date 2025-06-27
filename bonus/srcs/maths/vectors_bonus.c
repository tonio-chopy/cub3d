/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:21 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/27 16:52:55 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

t_vec	*cub_init_vec(int x, int y)
{
	t_vec	*point;

	point = ft_calloc(1, sizeof(t_vec));
	// point->x = x;
	// point->y = y;
	point->xd = (double)x;
	point->yd = (double)y;
	point->magnitude = 1;
	return (point);
}

t_vec	*cub_init_vec_double(double x, double y)
{
	t_vec	*point;

	point = ft_calloc(1, sizeof(t_vec));
	point->xd = x;
	point->yd = y;
	// point->x = (int) floor(x);
	// point->y = (int) floor(y);
	point->magnitude = 1.0;
	return (point);
}
