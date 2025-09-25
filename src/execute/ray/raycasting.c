/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:27:16 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/25 14:55:24 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * x			-> Pixel.
 * cameraX		-> The positión of the ray in the camera. Goes from -1 to 1.*
 * rayDirX/Y	-> The direction of the ray.
 */
void	cu_cast_rays(t_data *data)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;

	x = 0;
	while (x < S_WIDTH)
	{
		// PASO 1: Calcular dirección del rayo
		cameraX = ((2 * (x / (double)S_WIDTH)) - 1);
		rayDirX = data->game.player.dirX + data->game.player.planeX * cameraX;
		rayDirY = data->game.player.dirY + data->game.player.planeY * cameraX;

		// PASO 2: Encontrar que tiene más cerca el rayo, si el x o el y del grid.

		// PASO 3: Avanzar hasta encontrar la primera colisión con un muro. Solo necesitamos avanzar por la hipotenusa del triangulo que hemos sacado en el paso anterior, ya que avanzará todo el rato lo mismo al ser un grid.

		// PASO 4: calcular distancia.

		//TODO: sideDist (siguiente paso);
		x++;
	}



}

void	cu_raycasting()
{

}
