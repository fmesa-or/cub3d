/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:23:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/02 14:05:57 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * We look for an empty row *
 */
static void	cu_secondmap_check(t_game game)
{
	int	i;
	int	j;
	bool	space_cut;

	i = 0;
	j = 0;
	space_cut = false;
	while (game.map[i])
	{
		//si no es un espacio(pared, suelo o PJ, pasa a la siguiente)
		while (!(ft_isspace(game.map[i][j])))
			i++;
		if (space_cut == true && !(ft_isspace(game.map[i][j])))
			//ERROR: TOO MANY MAPS IN VERTICAL.
		//si encontramos un espacio, revisa la fila entera
		while (!(ft_isspace(game.map[i][j])))
			j++;
		if (space_cut == true && !(ft_isspace(game.map[i][j])))
			//ERROR: TOO MANY MAPS IN VERTICAL.
		if (game.map[i][j] == '\n' && game.map[i][j] == '\0')
			space_cut = true;
		i++;
		j = 0;
	}
}

static bool	cu_floodfill(t_game game, bool **filledmap, int i, int j)
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

	filledmap = ft_calloc(game.max_row + 1, sizeof(bool*)); //añadir calloc con smalloc
	if (!filledmap)
		//ERROR
	i = 0;
	while (i < game.max_row)
	{
		filledmap[i] = ft_calloc(game.max_col, sizeof(bool));
		if (!filledmap[i])
			//ERROR
		i++;
	}
	is_filled = cu_floodfill(game, filledmap, game.spawn_y, game.spawn_x);
	//liberar fillempa;
	if(is_filled == false)
		//ERROR: BAD MAP: NOT CLOSED BY WALLS
}

static void	cu_map_size(char **map)
{
	int	i;
	int	j;
	int	max_col;
	t_data	*data;

	max_col = 0;
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
void	cu_checkmap(void)
{
	t_data	*data;

	data = get_pdata(NULL);
	
	cu_map_size(data->game.map);
	cu_filledmaper(data->game);
	cu_secondmap_check(data->game);

}
