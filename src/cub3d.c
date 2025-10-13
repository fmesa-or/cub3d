/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmorale <crmorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:01:23 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/03 21:36:15 by crmorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static int	cu_render(t_data *data)
{
	// 1. Cargar texturas
	load_text(data);
	
	// 2. Crear imagen principal para rendering
	data->game.screen = mlx_new_image(data->mlx, S_WIDTH, S_HEIGHT);
	if (!data->game.screen)
	{
		fprintf(stderr, "Error\nFailed to create screen image.\n");
		mlx_terminate(data->mlx);
		return (-1);
	}
	
	// 3. Mostrar la imagen en la ventana
	if (mlx_image_to_window(data->mlx, data->game.screen, 0, 0) == -1)
	{
		fprintf(stderr, "Error\nFailed to put image to window.\n");
		mlx_terminate(data->mlx);
		return (-1);
	}
	
	// 4. Inicializar jugador y hacer raycasting inicial
	cu_init_player(&data->game.player, &data->game);
	cu_cast_rays(data, data->game.screen);
	//print_controls();??
	
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;


	if (ac != 2)
		error_msg("Error\nPlease, run Cub3D followed by a map path.\n");
	// 1. Inicializar el sistema de memoria y datos
	ft_memset(&data, 0, sizeof(t_data));
	get_pdata(&data);
	// 2. Parse del archivo de configuración
	check_and_parse_file(av[1], &data);
	// 3. Inicializar MLX
	data.mlx = mlx_init(S_WIDTH, S_HEIGHT, "CUB3D", true);
	if (!data.mlx)
	{
		fprintf(stderr, "Error\nMLX42 init failed.\n");
		return (EXIT_FAILURE);
	}
	// 4. RENDER
	if (cu_render(&data) == -1)
		return (EXIT_FAILURE);

	// 7. Configurar hooks y ejecutar loop principal
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx, movement_loop, &data);
	mlx_loop(data.mlx);
	// Cleanup MLX42 internals
	mlx_terminate(data.mlx);
	//Use the function for free all the data stored manually
	mem_clear();
	return (EXIT_SUCCESS);
}
