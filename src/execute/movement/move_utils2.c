/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:58:47 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/20 18:02:25 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/************************************************************
 * Processes left and right rotation based on key states.   *
 * Calculates net rotation considering opposite directions. *
 * Returns 1 if any rotation occurred, 0 otherwise.         *
 ***********************************************************/
int	process_rotation(t_data *data, double delta_time)
{
	double	rotation_speed;
	double	net_rotation;

	net_rotation = 0;
	rotation_speed = R_SPEED * delta_time;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		net_rotation -= rotation_speed;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		net_rotation += rotation_speed;
	if (net_rotation == 0)
		return (0);
	rotate_player(data, net_rotation);
	return (1);
}
