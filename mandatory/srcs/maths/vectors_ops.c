/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:36:56 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/07 11:36:57 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_multiply_vector(t_vec *p, double factor)
{
	p->magnitude *= factor;
	p->xd *= factor;
	p->xd *= factor;
}

double	ft_vector_scalar_product(t_vec *u, t_vec *v)
{
	return (u->xd * v->xd + u->yd * v->yd);
}

t_vec	*ft_rotate_vector_new(t_vec *p, double angle_rad)
{
	double	**m;
	t_vec	*new;

	new = cub_init_vec_double(p->xd, p->yd);
	m = get_zrotation_matrix(angle_rad);
	if (!m)
		return (NULL);
	multiply_matrix(new, m);
	clean_3dmatrix(m, 3);
	return (new);
}

void	ft_rotate_vector(t_vec *p, double angle_rad)
{
	double	**m;

	m = get_zrotation_matrix(angle_rad);
	if (!m)
		return ;
	multiply_matrix(p, m);
	clean_3dmatrix(m, 3);
}

void	ft_normalize_vector(t_vec *p)
{
	double	len;

	len = sqrt(p->xd * p->xd + p->yd * p->yd);
	p->xd /= len;
	p->yd /= len;
	p->magnitude = 1;
}
