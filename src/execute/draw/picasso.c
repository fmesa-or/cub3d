/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:36:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/01 14:22:57 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/******************************************************
 * Draws vertical wall line from drawStart to drawEnd.*
 *****************************************************/
void	cu_picasso(t_data *data, mlx_image_t *screen, int x)
{
	int			y;
	int			texX;
	int			texY;
	double		wallX;
	uint32_t	color;
	mlx_image_t	*texture;

	// 1. Determinar qué textura usar (una vez por columna)
	if (data->game.ray.side == 0) {  // Pared vertical
		if (data->game.ray.rayDirX > 0)
			texture = data->game.img_text[TEXT_EA].img;  // Este
		else
			texture = data->game.img_text[TEXT_WE].img;  // Oeste
	} else {  // Pared horizontal
		if (data->game.ray.rayDirY > 0)
			texture = data->game.img_text[TEXT_SO].img;  // Sur
		else
			texture = data->game.img_text[TEXT_NO].img;  // Norte
	}

	// Verificar que la textura esté cargada (evitar segfault)
	if (!texture)
	{
		// Dibujar color sólido si no hay textura
		y = data->game.ray.drawStart;
		while (y <= data->game.ray.drawEnd)
		{
			mlx_put_pixel(screen, x, y, 0xFF0055);  // Rojo para debug
			y++;
		}
		return;
	}

	// 2. Calcular coordenada X de la textura (una vez por columna)
	if (data->game.ray.side == 0)
		wallX = data->game.player.y + data->game.ray.perpWallDist * data->game.ray.rayDirY;
	else
		wallX = data->game.player.x + data->game.ray.perpWallDist * data->game.ray.rayDirX;
	wallX -= floor(wallX);  // Parte fraccionaria (0.0 a 1.0)
	texX = (int)(wallX * texture->width);
	
	// Asegurar que texX esté dentro de bounds
	if (texX >= (int)texture->width)
		texX = texture->width - 1;
	if (texX < 0)
		texX = 0;
	//3.1. Pintar el techo
	y = -1;
	while (++y < data->game.ray.drawStart)
		mlx_put_pixel(screen, x, y, get_hex_color(data->game.textures->ceiling));
	// 3.2. Dibujar cada pixel "Y" de la pared (en cada "y" pintará cada "x" una a una)
	y = data->game.ray.drawStart;
	while (y <= data->game.ray.drawEnd)
	{
		texY = (int)((y - S_HEIGHT/2 + data->game.ray.lineHeight/2) * texture->height / data->game.ray.lineHeight);
		
		// Asegurar que texY esté dentro de bounds
		if (texY >= (int)texture->height)
			texY = texture->height - 1;
		if (texY < 0)
			texY = 0;
			
		color = ((uint32_t*)texture->pixels)[texY * texture->width + texX];
		mlx_put_pixel(screen, x, y, color);
		y++;
	}
	//3.3. Pintar suelo
	while (y < S_HEIGHT)
	{
		mlx_put_pixel(screen, x, y, get_hex_color(data->game.textures->floor));
		y++;
	}
}
