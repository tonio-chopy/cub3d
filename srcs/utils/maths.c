#include "test.h"

float   ft_to_rad(int degrees)
{
    const float PI = 3.14159;

    return (degrees * PI / 180.0f);
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

	cos_t = cos(angle_rad);
	sin_t = sin(angle_rad);
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

void	multiply_matrix(t_point *p, double **matrix)
{
	double column[3];

	column[0] = p->xd;
	column[1] = p->yd;
	column[2] = 1.0;

	p->xd = multiply_line(column, matrix[0]);
	p->yd = multiply_line(column, matrix[1]);
	// printf("p x %f y %f\n", p->xd, p->yd);
}

t_point	*ft_rotate_vector_new(t_point *p, double angle_rad)
{
	double **m;
	t_point	*new;

	new = cub_init_point_double(p->xd, p->yd);
	m = get_zrotation_matrix(angle_rad);
	if (!m)
		return (NULL);
	multiply_matrix(new, m);
	clean_3dmatrix(m, 3);
	return (new);
}

void	ft_rotate_vector(t_point *p, double angle_rad)
{
	double **m;

	m = get_zrotation_matrix(angle_rad);
	if (!m)
		return ;
	multiply_matrix(p, m);
	clean_3dmatrix(m, 3);
}

void	ft_normalize_vector(t_point *p)
{
	double	len;

	len = sqrt(p->xd * p->xd + p->yd * p->yd);
	p->xd /= len;
	p->yd /= len;
}