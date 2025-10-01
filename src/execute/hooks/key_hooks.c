/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:28:43 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/01 14:00:44 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
	printf("KEY PRESSED\n");
}

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
	printf("KEY RELEASED\n");
}

/************
* @brief The key hook

* @param keydata The key data
* @param param The data struct
*************/
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
