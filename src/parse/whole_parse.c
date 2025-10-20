/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whole_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:42:11 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/20 17:11:45 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*******************************************
 * Checks the Player is inside of the maze.*
 ******************************************/
static void	cu_check_pj(t_game *game, int i, int j)
{
	if (i <= 0 || j <= 0)
		error_msg("Error\nBad PJ position.\n");
	if (!game->map[i][j])
		error_msg("Error\nMap lost!.\n");
	if (game->map[i - 1][j] > '1' || game->map[i - 1][j] < '0')
		error_msg("Error\nBad PJ position1.\n");
	if (!game->map[i + 1] || !(game->map[i + 1][j] <= '1'
		&& game->map[i + 1][j] >= '0'))
		error_msg("Error\nBad PJ position2.\n");
	if (game->map[i][j - 1] > '1' || game->map[i][j - 1] < '0')
		error_msg("Error\nBad PJ position3.\n");
	if (!game->map[i][j + 1] || !(game->map[i][j + 1] <= '1'
		&& game->map[i][j + 1] >= '0'))
		error_msg("Error\nBad PJ position4.\n");
	printf("CHECK\n");
}

/*********************************************************
 * Saves player spawn position and direction in game.   *
 * Stores coordinates and facing direction for startup.  *
 ********************************************************/
void	save_player_pos(int i, int j, char dir, t_game *game)
{
	cu_check_pj(game, i, j);
	game->spawn_x = j;
	game->spawn_y = i;
	game->spawn_dir = dir;
}

/************************************************************
 * Scans the entire map to find player starting position.  *
 * Searches for N/S/E/W characters and saves their coords. *
 ***********************************************************/
void	check_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N')
				save_player_pos(i, j, 'N', game);
			else if (game->map[i][j] == 'S')
				save_player_pos(i, j, 'S', game);
			else if (game->map[i][j] == 'E')
				save_player_pos(i, j, 'E', game);
			else if (game->map[i][j] == 'W')
				save_player_pos(i, j, 'W', game);
			j++;
		}
		i++;
	}
}

/***************************************************************
 * Main parsing function that processes the .cub file.        *
 * Validates file, parses textures, map, and player position. *
 **************************************************************/
void	check_and_parse_file(char *file_name, t_data *data)
{
	char	**map_array;
	int		i;

	i = 0;
	data->game.textures = smalloc(sizeof(t_textinfo));
	init_textinfo(data->game.textures);
	check_file(file_name);
	map_array = read_file(file_name);
	parse_textures(map_array, data->game.textures, &i);
	cu_parse_map(map_array, i);
	cu_checkmap(data);
	check_player_pos(&data->game);
}
