/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:46:14 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/05 11:51:58 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_BONUS_H
# define CONST_BONUS_H

# define WIN_W 1024
# define WIN_H 768
# define MINIMAP_SIZE 200

# define GREY 0x00A0A7A5
# define GRASS 0x00B1E1A1
# define RED 0x00FF0000
# define L_RED 0xAAFF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000
# define YELLOW 0x00DCE600
# define INVISIBLE 0x00FF00FF

# define WALL_N RED
# define WALL_S GRASS
# define WALL_E BLUE
# define WALL_W GREY

# define COL_FOV RED

# define MAP_EMPTY GRASS
# define MAP_WALL GREY
# define MAP_OUT BLACK

# define E_WALL '1'
# define E_INSIDE '0'
# define E_EMPTY ' '
# define E_NORTH 'N'
# define E_SOUTH 'S'
# define E_WEST 'W'
# define E_EAST 'E'
# define E_GOAL_LEFT 'G'
# define E_GOAL_CENTER 'H'
# define E_GOAL_OPENED 'O'
# define E_GOAL_RIGHT 'I'
# define E_BALL 'B'
# define E_BALL_VISITED '@'
# define E_CUP 'C'

# define BONUS_NAME "cub3D_bonus"

#endif