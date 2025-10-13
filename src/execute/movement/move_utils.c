/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:29:06 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/13 20:22:14 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**********************************************
 * Checks wall collision at given coordinates.*
 * Returns 1 if collision, 0 if safe.         *
 *********************************************/
int	check_wall_collision(t_data *data, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	if (!data || !data->game.map)
		return (1);
	if (new_x < 0.1 || new_y < 0.1 || new_x >= (data->game.max_col - 0.1)
		|| new_y >= (data->game.max_row - 0.1))
		return (1);
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (!data->game.map[map_y])
		return (1);
	if (data->game.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

/******************************************************
 * Moves player safely, checking collisions per axis. *
 * Allows wall sliding by testing X and Y separately. *
 *****************************************************/
void	move_player_safe(t_data *data, double new_x, double new_y)
{
	if (!data || !data->game.map)
		return ;
	if (!check_wall_collision(data, new_x, data->game.player.y))
	{
		data->game.player.x = new_x;
		printf("Player X: %.2f\n", data->game.player.x);
	}
	if (!check_wall_collision(data, data->game.player.x, new_y))
	{
		data->game.player.y = new_y;
		printf("Player Y: %.2f\n", data->game.player.y);
	}
}

/******************************************************
 * Rotates player direction and camera plane by angle.*
 * Uses 2D rotation matrix transformation.            *
 *****************************************************/
void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->game.player.dirX;
	data->game.player.dirX = data->game.player.dirX * cos(angle)
		- data->game.player.dirY * sin(angle);
	data->game.player.dirY = old_dir_x * sin(angle)
		+ data->game.player.dirY * cos(angle);
	old_plane_x = data->game.player.planeX;
	data->game.player.planeX = data->game.player.planeX * cos(angle)
		- data->game.player.planeY * sin(angle);
	data->game.player.planeY = old_plane_x * sin(angle)
		+ data->game.player.planeY * cos(angle);
}

/***********************************************************
 * Rotates the camera to the left smothly using delta time.*
 **********************************************************/
void	look_left(t_data *data, double delta_time)
{
	double	rotation_speed;

	rotation_speed = R_SPEED * delta_time;
	rotate_player(data, -rotation_speed);
}

/************************************************************
 * Rotates the camera to the right smothly using delta time.*
 ***********************************************************/
void	look_right(t_data *data, double delta_time)
{
	double	rotation_speed;

	rotation_speed = R_SPEED * delta_time;
	rotate_player(data, rotation_speed);
}
