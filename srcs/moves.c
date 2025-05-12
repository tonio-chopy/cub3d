#include "test.h"

void    move_if_possible(t_data *data, t_point *target, t_point *move_vector)
{
    double  dist_to_wall;
    double  dist_move;
    t_point direction;
    double  ratio;

    dist_move = ft_vector_len(move_vector);
    if (dist_move < 0.0001)
        return ;
    ft_normalize_vector(move_vector);
    dist_to_wall = cub_measure_dist_to_wall(data, move_vector);
    if (dist_move + MOVEMENT_SECURITY < dist_to_wall)
    {
        data->player_pos->xd = target->xd;
        data->player_pos->yd = target->yd;
    }
    else
    {
        ratio = (dist_to_wall - MOVEMENT_SECURITY) / dist_move;
        data->player_pos->xd += direction.xd * ratio;
        data->player_pos->yd += direction.yd * ratio;
    }
}