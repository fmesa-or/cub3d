/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:28:13 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/20 17:08:19 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sub_process_movement(t_movement mov, t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		mov.move_x -= data->game.player.plane_x * mov.speed;
		mov.move_y -= data->game.player.plane_y * mov.speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		mov.move_x += data->game.player.plane_x * mov.speed;
		mov.move_y += data->game.player.plane_y * mov.speed;
	}
	if (mov.move_x == 0 && mov.move_y == 0)
		return (0);
	mov.new_x = data->game.player.x + mov.move_x;
	mov.new_y = data->game.player.y + mov.move_y;
	move_player_safe(data, mov.new_x, mov.new_y);
	return (1);
}

/************************************************************
 * Processes WASD movement based on key states.             *
 * Calculates net movement considering opposite directions. *
 * Returns 1 if any movement occurred, 0 otherwise.         *
 ***********************************************************/
int	process_movement(t_data *data, double delta_time)
{
	t_movement	mov;
	int			ret;

	mov.speed = P_SPEED * delta_time;
	mov.move_x = 0;
	mov.move_y = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		mov.move_x += data->game.player.dir_x * mov.speed;
		mov.move_y += data->game.player.dir_y * mov.speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		mov.move_x -= data->game.player.dir_x * mov.speed;
		mov.move_y -= data->game.player.dir_y * mov.speed;
	}
	ret = sub_process_movement(mov, data);
	return (ret);
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
 * Checks if window has been resized and updates screen.    *
 * Returns 1 if resize occurred, 0 otherwise.               *
 ***********************************************************/
static int	handle_window_resize(t_data *data)
{
	int	new_width;
	int	new_height;

	new_width = data->mlx->width;
	new_height = data->mlx->height;
	if (new_width != data->game.win_width
		|| new_height != data->game.win_height)
	{
		data->game.win_width = new_width;
		data->game.win_height = new_height;
		mlx_delete_image(data->mlx, data->game.screen);
		data->game.screen = mlx_new_image(data->mlx, new_width, new_height);
		if (!data->game.screen)
			return (0);
		if (mlx_image_to_window(data->mlx, data->game.screen, 0, 0) == -1)
			return (0);
		return (1);
	}
	return (0);
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
	if (!data || !data->mlx)
		return ;
	current_time = mlx_get_time();
	if (last_time < 0)
	{
		last_time = current_time;
		return ;
	}
	delta_time = current_time - last_time;
	last_time = current_time;
	if (delta_time > 0.1)
		delta_time = 0.1;
	if (handle_window_resize(data))
		cu_cast_rays(data, data->game.screen);
	sub_movement_loop(data, delta_time);
}
