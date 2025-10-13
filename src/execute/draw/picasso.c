/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:36:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/13 19:30:22 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/************************************************************
 * Finds the Y coordinate from the texture (once per column)*
 * Checks tex_y is inside the bounds.                       *
 ***********************************************************/
static int	cu_maar(int y, t_data *data, mlx_image_t *texture)
{
	int	tex_y;

	tex_y = (int)((y - S_HEIGHT / 2 + data->game.ray.lineHeight / 2)
			* texture->height / data->game.ray.lineHeight);
	if (tex_y >= (int)texture->height)
		tex_y = texture->height - 1;
	if (tex_y < 0)
		tex_y = 0;
	return (tex_y);
}

/************************************************************
 * Finds the X coordinate from the texture (once per column)*
 * Checks tex_x is inside the bounds.                       *
 * Note:  wall_x goes from 0.1 to 1.0                       *
 ***********************************************************/
static int	cu_gouel(t_data *data, mlx_image_t *texture)
{
	double	wall_x;
	int		tex_x;

	if (data->game.ray.side == 0)
	{
		wall_x = data->game.player.y + data->game.ray.perpWallDist
			* data->game.ray.rayDirY;
	}
	else
	{
		wall_x = data->game.player.x + data->game.ray.perpWallDist
			* data->game.ray.rayDirX;
	}
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}

/*************************************************************************
 * Choose wich texture needs (once per column) and checks that is loaded.*
 ************************************************************************/
static mlx_image_t	*cu_olivier(t_data *data, mlx_image_t *texture)
{
	if (data->game.ray.side == 0)
	{
		if (data->game.ray.rayDirX > 0)
			texture = data->game.img_text[TEXT_EA].img;
		else
			texture = data->game.img_text[TEXT_WE].img;
	}
	else
	{
		if (data->game.ray.rayDirY > 0)
			texture = data->game.img_text[TEXT_SO].img;
		else
			texture = data->game.img_text[TEXT_NO].img;
	}
	if (!texture)
		error_msg("Error\nNULL texture.");
	return (texture);
}

/**************************************************************
 * Draws vertical wall line from drawStart to drawEnd.        *
 * Finds the X & Y coordinate inside the texture.             *
 * Draws the ceiling.                                         *
 * Draws every Y pixel from the X coordinate from the texture.*
 * Draws the floor.                                           *
 *************************************************************/
void	cu_picasso(t_data *data, mlx_image_t *screen, int x, mlx_image_t *text)
{
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	text = cu_olivier(data, text);
	tex_x = cu_gouel(data, text);
	y = -1;
	while (++y < data->game.ray.drawStart)
		mlx_put_pixel(screen, x, y,
			get_hex_color(data->game.textures->ceiling));
	y = data->game.ray.drawStart;
	while (y <= data->game.ray.drawEnd)
	{
		tex_y = cu_maar(y, data, text);
		color = ((uint32_t *)text->pixels)[tex_y * text->width + tex_x];
		mlx_put_pixel(screen, x, y, color);
		y++;
	}
	while (y < S_HEIGHT)
	{
		mlx_put_pixel(screen, x, y, get_hex_color(data->game.textures->floor));
		y++;
	}
}
