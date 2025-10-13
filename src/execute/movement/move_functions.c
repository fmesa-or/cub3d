/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:29:37 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/13 19:35:16 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/************************************************************
 * Moves player forward in the direction they are facing.   *
 * Calculates new position based on direction vector.       *
 ***********************************************************/
void	move_forward(t_data *data, double delta_time)
{
	double	speed;
	double	new_x;
	double	new_y;

	printf("MOVING FORWARD\n");
	speed = P_SPEED * delta_time;
	new_x = data->game.player.x + data->game.player.dirX * speed;
	new_y = data->game.player.y + data->game.player.dirY * speed;
	move_player_safe(data, new_x, new_y);
}

/************************************************************
 * Moves player backward opposite to the direction facing.  *
 * Calculates new position based on inverted direction.     *
 ***********************************************************/
void	move_backward(t_data *data, double delta_time)
{
	double	speed;
	double	new_x;
	double	new_y;

	speed = P_SPEED * delta_time;
	new_x = data->game.player.x - data->game.player.dirX * speed;
	new_y = data->game.player.y - data->game.player.dirY * speed;
	move_player_safe(data, new_x, new_y);
}

/************************************************************
 * Moves player left perpendicular to facing direction.     *
 * Uses camera plane vector for sideways movement.          *
 ***********************************************************/
void	strafe_left(t_data *data, double delta_time)
{
	double	speed;
	double	new_x;
	double	new_y;

	speed = P_SPEED * delta_time;
	new_x = data->game.player.x - data->game.player.planeX * speed;
	new_y = data->game.player.y - data->game.player.planeY * speed;
	move_player_safe(data, new_x, new_y);
}

/************************************************************
 * Moves player right perpendicular to facing direction.    *
 * Uses camera plane vector for sideways movement.          *
 ***********************************************************/
void	strafe_right(t_data *data, double delta_time)
{
	double	speed;
	double	new_x;
	double	new_y;

	speed = P_SPEED * delta_time;
	new_x = data->game.player.x + data->game.player.planeX * speed;
	new_y = data->game.player.y + data->game.player.planeY * speed;
	move_player_safe(data, new_x, new_y);
}
