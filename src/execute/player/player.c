/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:41:31 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/14 00:39:59 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sub_init_player(t_player *player)
{
	player->plane_x = 0;
	player->plane_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
}

/****************************************************
 * Initializes player position and direction vectors*
 * based on spawn position and orientation from map.*
 ***************************************************/
void	cu_init_player(t_player *player, t_game *game)
{
	sub_init_player(player);
	player->x = game->spawn_x + 0.5;
	player->y = game->spawn_y + 0.5;
	if (game->spawn_dir == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
	}
	else if (game->spawn_dir == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
	}
	else if (game->spawn_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_y = 0.66;
	}
	else if (game->spawn_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_y = -0.66;
	}
}
