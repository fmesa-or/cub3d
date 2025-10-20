/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:36:00 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/20 16:50:18 by fmesa-or         ###   ########.fr       */
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

	tex_y = (int)((y - data->game.win_height / 2
				+ data->game.ray.line_height / 2)
			* texture->height / data->game.ray.line_height);
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
		wall_x = data->game.player.y + data->game.ray.perp_wall_dist
			* data->game.ray.raydir_y;
		if (data->game.ray.raydir_x < 0)
			wall_x = -wall_x;
	}
	else
	{
		wall_x = data->game.player.x + data->game.ray.perp_wall_dist
			* data->game.ray.raydir_x;
		if (data->game.ray.raydir_y > 0)
			wall_x = -wall_x;
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
		if (data->game.ray.raydir_x < 0)
			texture = data->game.img_text[TEXT_EA].img;
		else
			texture = data->game.img_text[TEXT_WE].img;
	}
	else
	{
		if (data->game.ray.raydir_y < 0)
			texture = data->game.img_text[TEXT_SO].img;
		else
			texture = data->game.img_text[TEXT_NO].img;
	}
	if (!texture)
		error_msg("Error\nNULL texture.\n");
	return (texture);
}

static uint32_t	sub_cu_picasso(mlx_image_t *txt, int tex_x, int tex_y)
{
	uint32_t	color;

	color = ((uint32_t *)txt->pixels)[tex_y * txt->width + tex_x];
	color = ((color & 0xFF) << 24) | ((color & 0xFF00) << 8)
		| ((color & 0xFF0000) >> 8) | ((color & 0xFF000000) >> 24);
	return (color);
}

/**************************************************************
 * Draws vertical wall line from draw_start to draw_end.        *
 * Finds the X & Y coordinate inside the texture.             *
 * Draws the ceiling.                                         *
 * Draws every Y pixel from the X coordinate from the texture.*
 * Draws the floor.                                           *
 *************************************************************/
void	cu_picasso(t_data *dat, mlx_image_t *scrn, int x, mlx_image_t *txt)
{
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	txt = cu_olivier(dat, txt);
	tex_x = cu_gouel(dat, txt);
	y = -1;
	while (++y < dat->game.ray.draw_start)
		mlx_put_pixel(scrn, x, y,
			get_hex_color(dat->game.textures->ceiling));
	y = dat->game.ray.draw_start;
	while (y <= dat->game.ray.draw_end)
	{
		tex_y = cu_maar(y, dat, txt);
		color = sub_cu_picasso(txt, tex_x, tex_y);
		mlx_put_pixel(scrn, x, y, color);
		y++;
	}
	while (y < dat->game.win_height)
	{
		mlx_put_pixel(scrn, x, y, get_hex_color(dat->game.textures->floor));
		y++;
	}
}
