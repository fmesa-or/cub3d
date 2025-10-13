/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:48:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/14 00:54:34 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cu_init_flies(t_flies *flies, int start)
{
	flies->i = start;
	flies->j = 0;
	flies->line_len = 0;
	flies->player_count = 0;
	flies->start = start;
}

/************************************************************
 * Validates and copies map characters from file to map.   *
 * Counts player positions and checks for valid characters.*
 * Returns updated map with copied line.                   *
 ***********************************************************/
static char	**sub_cu_savemap_loop(char **file, t_flies *flies, char **map)
{
	flies->j = 0;
	while (flies->j < flies->line_len)
	{
		if (file[flies->start][flies->j] == 'N'
			|| file[flies->start][flies->j] == 'S'
			|| file[flies->start][flies->j] == 'E'
			|| file[flies->start][flies->j] == 'W')
		{
			flies->player_count++;
			if (flies->player_count > 1)
				error_msg("Error\nMULTIPLE PLAYER POSITIONS FOUND\n");
			map[flies->i][flies->j] = file[flies->start][flies->j];
		}
		else if (file[flies->start][flies->j] == '0'
			|| file[flies->start][flies->j] == '1'
			|| file[flies->start][flies->j] == ' ')
		{
			map[flies->i][flies->j] = file[flies->start][flies->j];
		}
		else
			error_msg("Error\nBAD CHARACTER FOR MAP\n");
		flies->j++;
	}
	return (map);
}

/*************************************************************
 * Processes each line of the map from file to map array.   *
 * Allocates memory for each line and validates characters. *
 * Ensures exactly one player position exists.              *
 ************************************************************/
static void	sub_cu_savemap(char **file, t_flies flies, char **map)
{
	t_data	*data;

	flies.i = 0;
	while (file[flies.start])
	{
		flies.j = 0;
		while (file[flies.start][flies.j] != '\n'
				&& file[flies.start][flies.j] != '\0')
			flies.j++;
		flies.line_len = flies.j;
		map[flies.i] = smalloc(sizeof(char) * (flies.line_len + 1));
		if (!map[flies.i])
			error_msg("Error\nparse_map.c: cu_savemap: malloc FAILED\n");
		map = sub_cu_savemap_loop(file, &flies, map);
		map[flies.i][flies.j] = '\0';
		flies.start++;
		flies.i++;
	}
	if (flies.player_count == 0)
		error_msg("Error\nparse_map.c: cu_savemap: NO PLAYER POSITION FOUND\n");
	if (flies.player_count != 1)
		error_msg("Error\nEXACTLY ONE PLAYER POSITION REQUIRED\n");
	data = get_pdata(NULL);
	data->game.map = map;
}

/**********************************************************
 * Saves map portion from file starting at given line.  *
 * Calculates map dimensions and allocates memory.       *
 * Calls helper functions to process map content.        *
 *********************************************************/
void	cu_savemap(char **file, int start)
{
	char	**map;
	t_flies	flies;

	cu_init_flies(&flies, start);
	while (file[flies.i])
		flies.i++;
	map = smalloc(sizeof(char *) * (flies.i - start + 1));
	if (!map)
		error_msg("Error\nparse_map.c: cu_savemap: malloc FAILED\n");
	map[flies.i - start] = NULL;
	sub_cu_savemap(file, flies, map);
}

/************************************************************
 * Finds the first line containing '1' (wall character).   *
 * Scans file from start until map beginning is located.   *
 * Calls cu_savemap to process and store the map.          *
 ***********************************************************/
void	cu_parse_map(char **file, int start)
{
	int		j;
	bool	map_found;

	if (!file)
		error_msg("Error\nparse_map.c: cu_parse_map: file = NULL\n");
	map_found = 0;
	while (file[start])
	{
		j = 0;
		while (file[start][j] != '\n' && file[start][j] != '\0')
		{
			if (file[start][j] == '1')
			{
				map_found = 1;
				break ;
			}
			j++;
		}
		if (map_found == 1)
			break ;
		start++;
	}
	cu_savemap(file, start);
	sfree(file);
}
