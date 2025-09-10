/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:30:46 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/10 13:21:42 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	cu_floodfill(t_game game, bool ***filledmap, int i, int j)
{
	bool	is_surrounded;

	if (i < 0 || i >= game.max_row || j < 0 || j >= game.max_col)
		return (false);
	if (!game.map[i][j])
		return (false);
	if (game.map[i][j] == '1' || (*filledmap)[i][j] == true)
		return (true);
	else
		(*filledmap)[i][j] = true;
	is_surrounded = true;
	is_surrounded &= cu_floodfill(game, filledmap, (i - 1), j);
	is_surrounded &= cu_floodfill(game, filledmap, (i + 1), j);
	is_surrounded &= cu_floodfill(game, filledmap, i, (j - 1));
	is_surrounded &= cu_floodfill(game, filledmap, i, (j + 1));
	return (is_surrounded);
}

bool	cu_checktile(t_game game, int i, int j)
{
	if (game.map[i][j] == '0' || game.map[i][j] == 'N' || game.map[i][j] == 'S' || game.map[i][j] == 'W' || game.map[i][j] == 'E')
		return(true);
	else
		return (false);
}

//La nueva función, debería ir linea a linea buscando el primer 0 y rellenando el floodfill de cada sala.
void	cu_filledmaper(t_game game)
{
	bool	**filledmap;
	bool	is_filled;
	int		i;
	int		j;

	filledmap = scalloc(game.max_row + 1, sizeof(bool*));
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
	//aqui insertamos un bucle para que busque el primer cero que no se haya chequeado
	i = 0;
	j = 0;
	is_filled = true;
	while (i < game.max_row && is_filled == true)
	{
		while (game.map[i][j] && (game.map[i][j] != '0' || filledmap[i][j] == 1))
			j++;
		if (game.map[i][j] && (cu_checktile(game, i, j)) && filledmap[i][j] == 0)
			is_filled = cu_floodfill(game, &filledmap, i, j);
		else
		{
			j = 0;
			i++;
		}
	}
	//liberar fillempa;
	if(is_filled == false)
		error_msg("ERROR: BAD MAP: NOT CLOSED BY WALLS");
}