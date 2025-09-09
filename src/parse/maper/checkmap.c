/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:23:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/09 18:06:54 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cu_sub_secondmap_check(t_game game, int *i, int *j)
{
	if (((ft_isspace(game.map[*i][*j])) != 1) && ((game.map[*i][*j] != '\n' && game.map[*i][*j] != '\0')))
		error_msg("ERROR: TOO MANY MAPS IN VERTICAL.");
	else
	{
		while ((ft_isspace(game.map[*i][*j])) == 1)
			(*j)++;
		if (game.map[*i][*j] != '\n' && game.map[*i][*j] != '\0')
			error_msg("ERROR: TOO MANY MAPS IN VERTICAL.");
		(*j) = 0;
		(*i)++;
	}
}

/**
 * We look for an empty row *
 */
static void	cu_secondmap_check(t_game game)//si meto lineas vacías al final salta como que tiene demasiados mapas
{
	int	i;
	int	j;
	bool	space_cut;

	i = 0;
	j = 0;
	space_cut = false;
	while (game.map[i] && (ft_isspace(game.map[i][j])) != 1)
		i++;
	while (game.map[i])
	{
		if (space_cut == true)
			cu_sub_secondmap_check(game, &i, &j);
		//si encontramos un espacio, revisa la fila entera
		while (game.map[i] && (ft_isspace(game.map[i][j])) == 1)
			j++;
//		if (space_cut == true && (ft_isspace(game.map[i][j])) != 1)
//			error_msg("ERROR: TOO MANY MAPS IN VERTICAL.");
		if (game.map[i] && (game.map[i][j] == '\n' || game.map[i][j] == '\0'))
			space_cut = true;
		if (space_cut == true)
			cu_sub_secondmap_check(game, &i, &j);
		i++;
		j = 0;
	}
}

/*static bool	cu_floodfill(t_game game, bool **filledmap, int i, int j)
{
	bool	is_surrounded;

	if (i < 0 || i >= game.max_row || j < 0 || j >= game.max_col)
		return (false);
	if (game.map[i][j] == '1' || filledmap[i][j] == true)
		return (true);
	else
		filledmap[i][j] = true;
	is_surrounded = true;
	is_surrounded &= cu_floodfill(game, filledmap, i - 1, j);
	is_surrounded &= cu_floodfill(game, filledmap, i + 1, j);
	is_surrounded &= cu_floodfill(game, filledmap, i, j - 1);
	is_surrounded &= cu_floodfill(game, filledmap, i, j + 1);
	return (is_surrounded);
}

static void	cu_filledmaper(t_game game)
{
	bool	**filledmap;
	bool	is_filled;
	int		i;

	filledmap = scalloc(game.max_row + 1, sizeof(bool*)); //añadir calloc con smalloc
	if (!filledmap)
		error_msg("ERROR: checkmap.c: cu_filledmaper: first scalloc failed.");
	i = 0;
	while (i < game.max_row)
	{
		filledmap[i] = scalloc(game.max_col, sizeof(bool));
		if (!filledmap[i])
			error_msg("ERROR: checkmap.c: cu_filledmaper: second scalloc failed.");
		i++;
	}
	is_filled = cu_floodfill(game, filledmap, game.spawn_y, game.spawn_x);
	//liberar fillempa;
	if(is_filled == false)
		error_msg("ERROR: BAD MAP: NOT CLOSED BY WALLS");
}*/

static void	cu_map_size(char **map)
{
	int	i;
	int	j;
	int	max_col;
	t_data	*data;

	max_col = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
			j++;
		if (j > max_col)
			max_col = j;
		i++;
	}
	data = get_pdata(NULL);
	data->game.max_col = j;
	data->game.max_row = i;
}

/**
 * 
 */
void	cu_checkmap(t_data *data)
{

	cu_map_size(data->game.map);
//	cu_filledmaper(data->game);
	cu_secondmap_check(data->game);

}
