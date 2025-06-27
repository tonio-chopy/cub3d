/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:06:20 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/27 21:12:39 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	clean_3dmatrix(double **m, int size)
{
	cub_clean2d((void **)m, size, 0b111, true);
}

void	ft_multiply_vector(t_vec *p, double factor)
{
	p->magnitude *= factor;
	p->xd *= factor;
	p->xd *= factor;
}
