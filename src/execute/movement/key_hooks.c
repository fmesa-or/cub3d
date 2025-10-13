/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:28:43 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/14 00:56:54 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**********************************************************
 * Sets key press flags to 1 for movement and rotation.   *
 * Handles W, S, A, D for movement and LEFT, RIGHT arrows.*
 *********************************************************/
void	handle_key_press(t_game *game, int key)
{
	if (key == MLX_KEY_W)
		game->keys.w_pressed = 1;
	else if (key == MLX_KEY_S)
		game->keys.s_pressed = 1;
	else if (key == MLX_KEY_A)
		game->keys.a_pressed = 1;
	else if (key == MLX_KEY_D)
		game->keys.d_pressed = 1;
	else if (key == MLX_KEY_LEFT)
		game->keys.left_pressed = 1;
	else if (key == MLX_KEY_RIGHT)
		game->keys.right_pressed = 1;
}

/**********************************************************
 * Sets key press flags to 0 for movement and rotation.   *
 * Handles W, S, A, D for movement and LEFT, RIGHT arrows.*
 *********************************************************/
void	handle_key_release(t_game *game, int key)
{
	if (key == MLX_KEY_W)
		game->keys.w_pressed = 0;
	else if (key == MLX_KEY_S)
		game->keys.s_pressed = 0;
	else if (key == MLX_KEY_A)
		game->keys.a_pressed = 0;
	else if (key == MLX_KEY_D)
		game->keys.d_pressed = 0;
	else if (key == MLX_KEY_LEFT)
		game->keys.left_pressed = 0;
	else if (key == MLX_KEY_RIGHT)
		game->keys.right_pressed = 0;
}

/***********************************************************
 * Main key event handler for MLX42 library.               *
 * Closes window on ESC key press.                         *
 * Calls appropriate press/release handlers for other keys.*
 **********************************************************/
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	if (keydata.action == MLX_PRESS)
		handle_key_press(&data->game, keydata.key);
	else if (keydata.action == MLX_RELEASE)
		handle_key_release(&data->game, keydata.key);
}
