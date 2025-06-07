/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/07 11:36:54 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_vec	*cub_init_vec(int x, int y)
{
	t_vec	*point;

	point = ft_calloc(1, sizeof(t_vec));
	point->x = x;
	point->y = y;
	point->xd = (float)x;
	point->yd = (float)y;
	point->magnitude = 1;
	return (point);
}

t_vec	*cub_init_vec_double(double x, double y)
{
	t_vec	*point;

	point = ft_calloc(1, sizeof(t_vec));
	point->xd = x;
	point->yd = y;
	point->x = round(x);
	point->y = round(y);
	return (point);
}
