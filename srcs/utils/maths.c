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
	}
	return (m);
}

/*
 * counterclockwise x rotation by angle theta
 */
double **get_xrotation_matrix(double angle)
{
	double	**m;
	double	cos_t;
	double	sin_t;

	cos_t = cos(angle);
	sin_t = sin(angle);
	m = init_empty_3dmatrix();
	if (!m)
		return (NULL);
	m[0][0] = 1.0;
	m[0][1] = 0.0;
	m[0][2] = 0.0;
	m[1][0] = 0.0;
	m[1][1] = cos_t;
	m[1][2] = -sin_t;
	m[2][0] = 0.0;
	m[2][1] = sin_t;
	m[2][2] = cos_t;
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
	column[2] = 1;

	p->xd = multiply_line(column, matrix[0]);
}

void	ft_rotate_vector(t_point *p, double angle)
{
	double **m;

	m = get_xrotation_matrix(angle);
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