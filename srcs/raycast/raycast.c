#include "test.h"

void    raycast(t_data *data)
{
    int     x;
    double  camera_x;
    t_point ray;

    x = 0;
    while (x < WIN_W)
    {
        camera_x = 2 * x / (double) WIN_W - 1;
        ray.xd = data->dir_vector->xd + data->player_pos->xd + data->cam_vector->xd; 
    }
}