#include "test.h"

double   ft_to_rad(double degrees)
{
    return (degrees * PI / 180.0f);
}

double	ft_to_deg(double radians)
{
	return (radians * (180 / PI));
}

void	clean_3dmatrix(double **m, int size)
{
	cub_clean2d((void **)m, size, 0b111, true);
}

double **init_empty_3dmatrix(void)
{
	double	**m;
	int		i;

	m = ft_calloc(3, sizeof(double *));
	if (!m)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		m[i] = ft_calloc(3, sizeof(double));
		if (!m[i])
		{
			clean_3dmatrix(m, 3);
			return (NULL);
		}
		i++;
	}
	return (m);
}

/*
 * counterclockwise rotation by angle theta
 */
double **get_zrotation_matrix(double angle_rad)
{
	double	**m;
	double	cos_t;
	double	sin_t;

	cos_t = cosf(angle_rad);
	sin_t = sinf(angle_rad);
	m = init_empty_3dmatrix();
	if (!m)
		return (NULL);
	m[0][0] = cos_t;
	m[0][1] = -sin_t;
	m[0][2] = 0.0;
	m[1][0] = sin_t;
	m[1][1] = cos_t;
	m[1][2] = 0.0;
	m[2][0] = 0.0;
	m[2][1] = 0.0;
	m[2][2] = 1.0;
	return (m);
}

double	multiply_line(double column[3], double line[3])
{
	return (line[0] * column[0] + line[1] * column[1] + line[2] * column[2]);
}

void	multiply_matrix(t_vec *p, double **matrix)
{
	double column[3];

	column[0] = p->xd;
	column[1] = p->yd;
	column[2] = 1.0;

	p->xd = multiply_line(column, matrix[0]);
	p->yd = multiply_line(column, matrix[1]);
}

t_vec	*ft_rotate_vector_new(t_vec *p, double angle_rad)
{
	double **m;
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
	double **m;

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

void	ft_multiply_vector(t_vec *p, double factor)
{
	p->magnitude *= factor;
	p->xd *= factor;
	p->xd *= factor;
}

double	ft_vector_len(t_vec *p)
{
	double len;

	len = sqrt(p->xd * p->xd + p->yd * p->yd);
	return (len);
}

double	ft_vector_scalar_product(t_vec *u, t_vec *v)
{
	return (u->xd * v->xd + u->yd * v->yd);
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

