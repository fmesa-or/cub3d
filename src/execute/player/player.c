/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:41:31 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/13 20:25:56 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sub_init_player(t_player *player)
{
	player->planeX = 0;
	player->planeY = 0;
	player->dirX = 0;
	player->dirY = 0;
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
		game->player.dirY = -1;
		game->player.planeX = 0.66;
	}
	else if (game->spawn_dir == 'S')
	{
		game->player.dirY = 1;
		game->player.planeX = -0.66;
	}
	else if (game->spawn_dir == 'E')
	{
		game->player.dirX = 1;
		game->player.planeY = 0.66;
	}
	else if (game->spawn_dir == 'W')
	{
		game->player.dirX = -1;
		game->player.planeY = -0.66;
	}
}
