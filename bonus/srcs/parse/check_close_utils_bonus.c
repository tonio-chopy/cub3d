/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:44:25 by alaualik          #+#    #+#             */
/*   Updated: 2025/07/05 12:24:10 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_adjust_visited(char *elems, int i)
{
	if (elems[i] == E_BALL || elems[i] == E_BALL_VISITED)
		elems[i] = E_BALL_VISITED;
	else
		elems[i] = VISITED;
}
