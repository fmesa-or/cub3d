/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:28:13 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/13 20:11:11 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/************************************************************
 * Processes left and right rotation based on key states.   *
 * Returns 1 if any rotation occurred, 0 otherwise.         *
 ***********************************************************/
int	process_rotation(t_data *data, double delta_time)
{
	int	rotated;

	rotated = 0;
	if (data->game.keys.left_pressed && (look_left(data, delta_time), 1))
		rotated = 1;
	if (data->game.keys.right_pressed && (look_right(data, delta_time), 1))
		rotated = 1;
	return (rotated);
}

/************************************************************
 * Processes WASD movement based on key states.             *
 * Returns 1 if any movement occurred, 0 otherwise.         *
 ***********************************************************/
int	process_movement(t_data *data, double delta_time)
{
	int	moved;

	moved = 0;
	if (data->game.keys.w_pressed && (move_forward(data, delta_time), 1))
		moved = 1;
	if (data->game.keys.s_pressed && (move_backward(data, delta_time), 1))
		moved = 1;
	if (data->game.keys.a_pressed && (strafe_left(data, delta_time), 1))
		moved = 1;
	if (data->game.keys.d_pressed && (strafe_right(data, delta_time), 1))
		moved = 1;
	return (moved);
}

/************************************************************
 * Handles movement and rotation simultaneously.            *
 * Re-casts rays only if player moved or rotated.           *
 ***********************************************************/
static void	sub_movement_loop(t_data *data, double delta_time)
{
	int	moved;
	int	rotated;

	moved = process_movement(data, delta_time);
	rotated = process_rotation(data, delta_time);
	if (moved || rotated)
		cu_cast_rays(data, data->game.screen);
}

/************************************************************
 * Main movement loop called every frame by MLX42.          *
 * Calculates delta time for smooth frame-rate independent  *
 * movement and handles player input processing.            *
 ***********************************************************/
void	movement_loop(void *param)
{
	t_data			*data;
	static double	last_time = -1;
	double			current_time;
	double			delta_time;

	data = (t_data *)param;
	current_time = mlx_get_time();
	if (last_time < 0)
	{
		last_time = current_time;
		return ;
	}
	delta_time = current_time - last_time;
	last_time = current_time;
	sub_movement_loop(data, delta_time);
}
