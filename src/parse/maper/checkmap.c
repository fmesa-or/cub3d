/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:23:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/20 18:02:50 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**********************************************************
 * Helper function to validate empty lines after map ends.*
 * Ensures no additional map content exists after the main*
 * map has finished.                                      *
 *********************************************************/
static void	cu_sub_secondmap_check(t_game game, int *i, int *j)
{
	if (((ft_isspace(game.map[*i][*j])) != 1) && ((game.map[*i][*j] != '\n'
			&& game.map[*i][*j] != '\0')))
		error_msg("Error\nTOO MANY MAPS IN VERTICAL.\n");
	else
	{
		while ((ft_isspace(game.map[*i][*j])) == 1)
			(*j)++;
		if (game.map[*i][*j] != '\n' && game.map[*i][*j] != '\0')
			error_msg("Error\nTOO MANY MAPS IN VERTICAL.\n");
		(*j) = 0;
		(*i)++;
	}
}

/********************************************************
 * Validates that no additional map content exists after*
 * the main map ends. Checks for empty rows and ensures *
 * map integrity throughout the file.                   *
 *******************************************************/
static void	cu_secondmap_check(t_game game)
{
	int		i;
	int		j;
	bool	space_cut;

	i = 0;
	j = 0;
	space_cut = false;
	while (game.map[i] != NULL)
	{
		if (space_cut == true && game.map[i] != NULL)
			cu_sub_secondmap_check(game, &i, &j);
		while (game.map[i] != NULL && (ft_isspace(game.map[i][j])) == 1)
			j++;
		if (game.map[i] != NULL && (game.map[i][j] == '\n'
			|| game.map[i][j] == '\0'))
			space_cut = true;
		if (game.map[i] != NULL)
			i++;
		j = 0;
	}
}

/*********************************************************
 * Calculates and stores maximum map dimensions.         *
 * Finds the longest row and total number of rows in map.*
 ********************************************************/
static void	cu_map_size(char **map)
{
	int		i;
	int		j;
	int		max_col;
	t_data	*data;

	max_col = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max_col)
			max_col = j;
		i++;
	}
	data = get_pdata(NULL);
	data->game.max_col = max_col;
	data->game.max_row = i;
}

/******************
 * MAIN CHECKMAPER*
 *****************/
void	cu_checkmap(t_data *data)
{
	cu_map_size(data->game.map);
	cu_filledmaper(data->game);
	cu_secondmap_check(data->game);
}
