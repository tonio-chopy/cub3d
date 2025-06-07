/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "types.h"

// Vector creation
t_vec				*cub_init_vec(int x, int y);
t_vec				*cub_init_vec_double(double x, double y);

// Angle functions
double				ft_to_rad(double degrees);
double				ft_to_deg(double radians);
double				ft_vector_len(t_vec *p);
double				ft_get_angle_between_vec(t_vec *u, t_vec *v);

// Vector operations
void				ft_multiply_vector(t_vec *p, double factor);
t_vec				*ft_rotate_vector_new(t_vec *p, double angle_rad);
void				ft_rotate_vector(t_vec *p, double angle_rad);
double				ft_vector_scalar_product(t_vec *u, t_vec *v);
void				ft_normalize_vector(t_vec *p);

// Matrix operations
void				multiply_matrix(t_vec *p, double **matrix);
double				**get_zrotation_matrix(double angle_rad);
void				clean_3dmatrix(double **m, int size);

#endif
