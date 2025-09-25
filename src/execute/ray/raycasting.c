/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:27:16 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/25 13:59:38 by fmesa-or         ###   ########.fr       */
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
		cameraX = ((2 * (x / (double)S_WIDTH)) - 1);
		rayDirX = data->game.player.dirX + data->game.player.planeX * cameraX;
		rayDirY = data->game.player.dirY + data->game.player.planeY * cameraX;

		// DEBUG: Imprimir algunos rayos para ver los valores /////////////////
		if (x % 200 == 0)  // Cada 200 píxeles
		{
			printf("Pixel %d: cameraX=%.3f, rayDirX=%.3f, rayDirY=%.3f\n", 
				x, cameraX, rayDirX, rayDirY);
		}
		///////////////////////////////////////////////////////////////////////

		//TODO: Aquí iría el DDA (siguiente paso);
		x++;
	}



}

void	cu_raycasting()
{

}
