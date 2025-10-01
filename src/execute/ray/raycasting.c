/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:27:16 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/01 11:49:12 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/********************************************************************
 * Calculates perpendicular wall distance and line height.          *
 *                                                                  *
 * lineHeight		-> Wall height in pixels on screen.             *
 * perpWallDist	-> Perpendicular distance to wall (avoids fish-eye).*
 *******************************************************************/
static void	cu_measurer(t_data *data)
{


	if (data->game.ray.side == 0) {
	// Pared vertical - usamos la coordenada X
		data->game.ray.perpWallDist = (data->game.ray.mapX - data->game.player.x + (1 - data->game.ray.stepX) / 2) / data->game.ray.rayDirX;
	}
	else
	{
		// Pared horizontal - usamos la coordenada Y
		data->game.ray.perpWallDist = (data->game.ray.mapY - data->game.player.y + (1 - data->game.ray.stepY) / 2) / data->game.ray.rayDirY;
	}

	data->game.ray.lineHeight = (int)(S_HEIGHT / data->game.ray.perpWallDist);

	data->game.ray.drawStart = -data->game.ray.lineHeight / 2 + S_HEIGHT / 2;
	if (data->game.ray.drawStart < 0)
		data->game.ray.drawStart = 0;

	data->game.ray.drawEnd = data->game.ray.lineHeight / 2 + S_HEIGHT / 2;
	if (data->game.ray.drawEnd >= S_HEIGHT)
		data->game.ray.drawEnd = S_HEIGHT - 1;
}

/*********************************************************
 * DDA algorithm: step through grid until hitting a wall.*
 *                                                       *
 * hit	-> Flag: 0 = no wall found, 1 = wall hit.        *
 ********************************************************/
static void	cu_dda_cane(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->game.ray.sideDistX < data->game.ray.sideDistY) {
			data->game.ray.sideDistX += data->game.ray.deltaDistX;
			data->game.ray.mapX += data->game.ray.stepX;
			data->game.ray.side = 0;  // Golpeamos una pared vertical
		} else {
			data->game.ray.sideDistY += data->game.ray.deltaDistY;
			data->game.ray.mapY += data->game.ray.stepY;
			data->game.ray.side = 1;  // Golpeamos una pared horizontal
		}
		
		if (data->game.map[data->game.ray.mapY][data->game.ray.mapX] == '1') {
			hit = 1;  // ¡Encontramos un muro!
		}
	}
}

/***************************************************************************
 * Initialize DDA variables: deltaDist, sideDist, step, mapX/Y             *
 *                                                                         *
 * deltaDistX/Y	-> Length ray travels for one unit step in X/Y.            *
 * sideDistX/Y	-> Distance from player to next grid line in X/Y.          *
 * stepX/Y		-> Direction to advance in grid (-1 or +1).                *
 * mapX/Y		-> Current grid coordinates (integer) where ray is located.*
 **************************************************************************/
static void	cu_dda_sizer(t_data *data)
{
	if (data->game.ray.rayDirX == 0)
		data->game.ray.deltaDistX = 1e30;  // Valor muy grande (prácticamente infinito)
	else
		data->game.ray.deltaDistX = fabs(1.0 / data->game.ray.rayDirX);
	
	if (data->game.ray.rayDirY == 0)
		data->game.ray.deltaDistY = 1e30;  // Valor muy grande (prácticamente infinito)
	else
		data->game.ray.deltaDistY = fabs(1.0 / data->game.ray.rayDirY);

	data->game.ray.mapX = (int)data->game.player.x;
	data->game.ray.mapY = (int)data->game.player.y;

	if (data->game.ray.rayDirX < 0) {
		data->game.ray.stepX = -1;
		data->game.ray.sideDistX = (data->game.player.x - data->game.ray.mapX) * data->game.ray.deltaDistX;
	} else {
		data->game.ray.stepX = 1;
		data->game.ray.sideDistX = (data->game.ray.mapX + 1.0 - data->game.player.x) * data->game.ray.deltaDistX;
	}

	if (data->game.ray.rayDirY < 0) {
		data->game.ray.stepY = -1;
		data->game.ray.sideDistY = (data->game.player.y - data->game.ray.mapY) * data->game.ray.deltaDistY;
	} else {
		data->game.ray.stepY = 1;
		data->game.ray.sideDistY = (data->game.ray.mapY + 1.0 - data->game.player.y) * data->game.ray.deltaDistY;
	}
}

/******************************************************
 * Main raycasting: cast ray for each screen column.  *
 *                                                    *
 * Steps:                                             *
 * 1. Calculate ray direction                         *
 * 2. Initialize DDA variables                        *
 * 3. Execute DDA algorithm to find wall              *
 * 4. Calculate wall distance and height              *
 * 5. Draw vertical wall line                         *
 *                                                    *
 * x		-> Current screen column (0 to S_WIDTH).  *
 * y		-> Starting Y coordinate for drawing.     *
 * cameraX	-> Ray position in camera space (-1 to 1).*
 *****************************************************/
void	cu_cast_rays(t_data *data, mlx_image_t *screen)
{
	int		x;
	int		y;
	double	cameraX;

	x = 0;
	while (x < S_WIDTH)
	{
		// PASO 1: Calcular dirección del rayo
		cameraX = ((2 * (x / (double)S_WIDTH)) - 1);
		data->game.ray.rayDirX = data->game.player.dirX + data->game.player.planeX * cameraX;
		data->game.ray.rayDirY = data->game.player.dirY + data->game.player.planeY * cameraX;
		// PASO 2: Calcular distancias DDA
		cu_dda_sizer(data);
		// PASO 3: Algoritmo DDA - Avanzar hasta encontrar un muro
		cu_dda_cane(data);
		// PASO 4: Calcular distancia perpendicular y altura de la línea
		cu_measurer(data);
		// PASO 5: Dibujar la línea vertical
		y = data->game.ray.drawStart;
		cu_picasso(data, screen, x);
		x++;
	}
}
