/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:20:49 by crmorale          #+#    #+#             */
/*   Updated: 2025/09/23 13:22:03 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	prepare_text_paths(t_game *game, char *paths[TEXT_COUNT])
{
	paths[TEXT_NO] = game->textures->no_path;
	paths[TEXT_SO] = game->textures->so_path;
	paths[TEXT_EA] = game->textures->ea_path;
	paths[TEXT_WE] = game->textures->we_path;
}

void	load_text(t_data *data)
{
	char	*paths[TEXT_COUNT];
	int 	i;
	xpm_t	*xpm;
	
	prepare_text_paths(&data->game, paths);
	i = 0;
	while (i < TEXT_COUNT)
	{
		xpm = mlx_load_xpm42(paths[i]);
		if (!xpm)
			error_msg("Error\nCannot load XPM texture.\n");
		data->game.img_text[i].img = mlx_texture_to_image(data->mlx, &xpm->texture);
		if (!data->game.img_text[i].img)
		{
			mlx_delete_xpm42(xpm);
			error_msg("Error\nCannot convert texture to image.\n");
		}
		data->game.img_text[i].width = xpm->texture.width;
		data->game.img_text[i].height = xpm->texture.height;
/*		// En MLX42, los pixels se acceden directamente a través de image->pixels   LO HACE AUTOMÁTICAMENTE LA MLX42
		data->game.img_text[i].addr = (char *)((mlx_image_t*)data->game.img_text[i].img)->pixels;
		data->game.img_text[i].bpp = 32; // MLX42 usa 32 bits por pixel (RGBA)
		data->game.img_text[i].line_len = xpm->texture.width * 4; // 4 bytes por pixel
		data->game.img_text[i].endian = 0; // Little endian*/
		mlx_delete_xpm42(xpm); // Liberar el XPM temporal
		i++;
	}
}
/*
MIRAR ESTO PARA CARGAR FUNCION DE LOAD_TEXT Y MLX
int main(void)
{
    t_data data;

    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    data.win = mlx_new_window(data.mlx, 800, 600, "cub3D");

    // parseas archivo, rellenas data.game.textures con rutas
    load_textures(&data); // ahora todo vive en t_data

    mlx_loop(data.mlx);
}*/

//AÑADIDA ESTRUC IMG_TEX EN GAME Y VOID *MLX Y *WIN EN DATA)
//INICIALIZAR ESTRUCTURA IMG_TEXT:

void	init_img_struct(t_img_text *img_text)
{
	img_text->img = NULL;
//	img_text->addr = NULL;
	img_text->width = 0;
	img_text->height = 0;
//	img_text->bpp = 0;
//	img_text->line_len = 0;
//	img_text->endian = 0;
}