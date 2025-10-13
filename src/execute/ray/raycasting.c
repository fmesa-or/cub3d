/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:27:16 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/14 00:48:52 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/********************************************************************
 * Calculates perpendicular wall distance and line height.          *
 *                                                                  *
 * line_height	-> Wall height in pixels on screen.                 *
 * perp_wall_dist	-> Perpendicular distance to wall (avoids fish-eye).*
 *******************************************************************/
static void	cu_measurer(t_data *data)
{
	if (data->game.ray.side == 0)
	{
		data->game.ray.perp_wall_dist = (data->game.ray.map_x
				- data->game.player.x + (1 - data->game.ray.step_x) / 2)
			/ data->game.ray.raydir_x;
	}
	else
	{
		data->game.ray.perp_wall_dist = (data->game.ray.map_y
				- data->game.player.y + (1 - data->game.ray.step_y)
				/ 2) / data->game.ray.raydir_y;
	}
	data->game.ray.line_height = (int)(S_HEIGHT
			/ data->game.ray.perp_wall_dist);
	data->game.ray.draw_start = -data->game.ray.line_height / 2 + S_HEIGHT / 2;
	if (data->game.ray.draw_start < 0)
		data->game.ray.draw_start = 0;
	data->game.ray.draw_end = data->game.ray.line_height / 2 + S_HEIGHT / 2;
	if (data->game.ray.draw_end >= S_HEIGHT)
		data->game.ray.draw_end = S_HEIGHT - 1;
}

/*********************************************************
 * DDA algorithm: step through grid until hitting a wall.*
 *                                                       *
 * hit	-> 0 = no wall found / 1 = wall hit.             *
 ********************************************************/
static void	cu_dda_cane(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->game.ray.sidedist_x < data->game.ray.sidedist_y)
		{
			data->game.ray.sidedist_x += data->game.ray.deltadist_x;
			data->game.ray.map_x += data->game.ray.step_x;
			data->game.ray.side = 0;
		}
		else
		{
			data->game.ray.sidedist_y += data->game.ray.deltadist_y;
			data->game.ray.map_y += data->game.ray.step_y;
			data->game.ray.side = 1;
		}
		if (data->game.map[data->game.ray.map_y][data->game.ray.map_x] == '1')
		{
			hit = 1;
		}
	}
}

/************************************************************
 * Calculates step direction and initial side distances    *
 * based on ray direction for DDA algorithm.               *
 ***********************************************************/
static void	sub_dda_sizer(t_data *data)
{
	if (data->game.ray.raydir_x < 0)
	{
		data->game.ray.step_x = -1;
		data->game.ray.sidedist_x = (data->game.player.x - data->game.ray.map_x)
			* data->game.ray.deltadist_x;
	}
	else
	{
		data->game.ray.step_x = 1;
		data->game.ray.sidedist_x = (data->game.ray.map_x + 1.0
				- data->game.player.x) * data->game.ray.deltadist_x;
	}
	if (data->game.ray.raydir_y < 0)
	{
		data->game.ray.step_y = -1;
		data->game.ray.sidedist_y = (data->game.player.y
				- data->game.ray.map_y) * data->game.ray.deltadist_y;
	}
	else
	{
		data->game.ray.step_y = 1;
		data->game.ray.sidedist_y = (data->game.ray.map_y + 1.0
				- data->game.player.y) * data->game.ray.deltadist_y;
	}
}

/***************************************************************************
 * Initialize DDA variables: deltaDist, sideDist, step, map_x/Y             *
 *                                                                         *
 * deltadist_x/Y	-> Length ray travels for one unit step in X/Y.            *
 * sidedist_x/Y	-> Distance from player to next grid line in X/Y.          *
 * step_x/Y		-> Direction to advance in grid (-1 or +1).                *
 * map_x/Y		-> Current grid coordinates (integer) where ray is located.*
 * Note:  1e30 it's a really big number (almost infinite).                 *
 **************************************************************************/
static void	cu_dda_sizer(t_data *data)
{
	if (data->game.ray.raydir_x == 0)
		data->game.ray.deltadist_x = 1e30;
	else
		data->game.ray.deltadist_x = fabs(1.0 / data->game.ray.raydir_x);
	if (data->game.ray.raydir_y == 0)
		data->game.ray.deltadist_y = 1e30;
	else
		data->game.ray.deltadist_y = fabs(1.0 / data->game.ray.raydir_y);
	data->game.ray.map_x = (int)data->game.player.x;
	data->game.ray.map_y = (int)data->game.player.y;
	sub_dda_sizer(data);
}

/******************************************************
 * Main raycasting: cast ray for each screen column.  *
 *                                                    *
 * Steps:                                             *
 * 1. Calculate ray direction                         *
 * 2. Initialize DDA variables                        *
 * 3. Execute DDA algorithm until find wall           *
 * 4. Calculate wall distance and height              *
 * 5. Draw vertical wall line                         *
 *                                                    *
 * x		-> Current screen column (0 to S_WIDTH).  *
 * y		-> Starting Y coordinate for drawing.     *
 * camera_x	-> Ray position in camera space (-1 to 1).*
 *****************************************************/
void	cu_cast_rays(t_data *data, mlx_image_t *screen)
{
	int		x;
	double	camera_x;

	x = 0;
	while (x < S_WIDTH)
	{
		camera_x = ((2 * (x / (double)S_WIDTH)) - 1);
		data->game.ray.raydir_x = data->game.player.dir_x
			+ data->game.player.plane_x * camera_x;
		data->game.ray.raydir_y = data->game.player.dir_y
			+ data->game.player.plane_y * camera_x;
		cu_dda_sizer(data);
		cu_dda_cane(data);
		cu_measurer(data);
		cu_picasso(data, screen, x, NULL);
		x++;
	}
}
