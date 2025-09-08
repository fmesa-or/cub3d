/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whole_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:42:11 by crmorale          #+#    #+#             */
/*   Updated: 2025/09/08 21:08:17 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	save_player_pos(int i, int j, char dir, t_game *game)
{
	game->spawn_x = j;
	game->spawn_y = i;
	game->spawn_dir = dir;
}

void check_player_pos(t_game *game)
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

void	check_and_parse_file(char *file_name, t_data *data)
{

	char	**map_array;
	int		i;

	i = 0;
	init_textinfo(data->game.textures);
	check_file(file_name);
	map_array = read_file(file_name);
	parse_textures(map_array, data->game.textures, &i);//REVISAR ROMPE AL EJECUTAR
	cu_parse_map(map_array, i);
	cu_checkmap(data);
	check_player_pos(&data->game);
}
