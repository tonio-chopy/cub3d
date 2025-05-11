#include "test.h"

float   to_rad(int degrees)
{
    const float PI = 3.14159;

    return (degrees * PI / 180.0f);
}

double	multiply_line(int p[3], int m[3])
{

}

void	multiply_matrix(t_point *p, double matrix[3][3])
{
	double point[3];

	point[0] = p->xf;
	point[1] = p->yf;
	point[2] = 1;


}

void	rotate_vector(t_point *p)
{

}
