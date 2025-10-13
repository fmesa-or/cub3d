/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:01:23 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/14 00:52:15 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*************************************************************
 * Renders the initial game frame and sets up display.       *
 * 1. Load all wall textures from file paths.                *
 * 2. Create main screen image for rendering.                *
 * 3. Display the image in the MLX window.                   *
 * 4. Initialize player position and perform initial raycast.*
 ************************************************************/
static int	cu_render(t_data *data)
{
	load_text(data);
	data->game.screen = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);
	if (!data->game.screen)
	{
		error_msg("Error\nFailed to create screen image.\n");
		mlx_terminate(data->mlx);
		return (-1);
	}
	if (mlx_image_to_window(data->mlx, data->game.screen, 0, 0) == -1)
	{
		error_msg("Error\nFailed to put image to window.\n");
		mlx_terminate(data->mlx);
		return (-1);
	}
	cu_init_player(&data->game.player, &data->game);
	cu_cast_rays(data, data->game.screen);
	return (0);
}

/************************************************************
 * Main function that orchestrates the entire Cub3D program.*
 * 1. Initialize memory system and data structures.         *
 * 2. Parse configuration file (.cub).                      *
 * 3. Initialize MLX graphics library.                      *
 * 4. Render initial frame and setup display.               *
 * 5. Configure input hooks and run main game loop.         *
 * 6. Cleanup MLX42 internals on exit.                      *
 * 7. Free all manually allocated memory.                   *
 ***********************************************************/
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error_msg("Error\nPlease, run Cub3D followed by a map path.\n");
	ft_memset(&data, 0, sizeof(t_data));
	get_pdata(&data);
	check_and_parse_file(av[1], &data);
	data.mlx = mlx_init(S_WIDTH, S_HEIGHT, "CUB3D", true);
	if (!data.mlx)
	{
		error_msg("Error\nMLX42 init failed.\n");
		return (EXIT_FAILURE);
	}
	if (cu_render(&data) == -1)
		return (EXIT_FAILURE);
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx, movement_loop, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	mem_clear();
	return (EXIT_SUCCESS);
}
