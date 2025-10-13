/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:20:49 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/13 22:43:46 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/********************************************************
 * Organizes texture paths into array for batch loading.*
 * Maps NO, SO, EA, WE paths to indexed array structure.*
 *******************************************************/
void	prepare_text_paths(t_game *game, char *paths[TEXT_COUNT])
{
	paths[TEXT_NO] = game->textures->no_path;
	paths[TEXT_SO] = game->textures->so_path;
	paths[TEXT_EA] = game->textures->ea_path;
	paths[TEXT_WE] = game->textures->we_path;
}

/******************************************************
 * Loads PNG textures into MLX42 images for rendering.*
 * Converts textures to images and stores dimensions. *
 * Handles texture loading errors and memory cleanup. *
 *****************************************************/
void	load_text(t_data *data)
{
	char			*paths[TEXT_COUNT];
	int				i;
	mlx_texture_t	*textures;

	prepare_text_paths(&data->game, paths);
	i = 0;
	while (i < TEXT_COUNT)
	{
		textures = mlx_load_png(paths[i]);
		if (!textures)
			error_msg("Error\nCannot load PNG texture.\n");
		data->game.img_text[i].img = mlx_texture_to_image(data->mlx, textures);
		if (!data->game.img_text[i].img)
		{
			mlx_delete_texture(textures);
			error_msg("Error\nCannot convert texture to image.\n");
		}
		data->game.img_text[i].width = textures->width;
		data->game.img_text[i].height = textures->height;
		mlx_delete_texture(textures);
		i++;
	}
}
