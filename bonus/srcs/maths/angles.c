/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:15 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/10 15:35:14 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

double	ft_to_rad(double degrees)
{
	return (degrees * PI / 180.0f);
}

double	ft_to_deg(double radians)
{
	return (radians * (180 / PI));
}

double	ft_vector_len(t_vec *p)
{
	double	len;

	len = sqrt(p->xd * p->xd + p->yd * p->yd);
	return (len);
}

double	ft_get_angle_between_vec(t_vec *u, t_vec *v)
{
	double	scalar_product;
	double	cos_theta;
	double	angle_rad;

	scalar_product = ft_vector_scalar_product(u, v);
	u->magnitude = ft_vector_len(u);
	v->magnitude = ft_vector_len(v);
	if (u->magnitude < 0.0001 || v->magnitude < 0.0001)
		return (0);
	cos_theta = scalar_product / (u->magnitude * v->magnitude);
	if (cos_theta > 1.0)
		cos_theta = 1.0;
	else if (cos_theta < -1.0)
		cos_theta = -1;
	angle_rad = acos(cos_theta);
	return (ft_to_deg(angle_rad));
}
