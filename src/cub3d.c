/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:01:23 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/29 15:12:08 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}


int	main(int ac, char **av)
{
	t_data		data;
	mlx_image_t	*screen;

	if (ac != 2)
		error_msg("Error\nPlease, run Cub3D with exactly one argument.\n");

	// 1. Inicializar el sistema de memoria y datos
	ft_memset(&data, 0, sizeof(t_data));
	get_pdata(&data);

	// 2. Parse del archivo de configuración
	check_and_parse_file(av[1], &data);

	// 3. Inicializar MLX
	data.mlx = mlx_init(S_WIDTH, S_HEIGHT, "CUB3D", true);
	if (!data.mlx)
	{
		fprintf(stderr, "Error: MLX42 init failed.\n");
		return (EXIT_FAILURE);
	}

	// 4. Crear imagen principal para rendering
	screen = mlx_new_image(data.mlx, S_WIDTH, S_HEIGHT);
	if (!screen)
	{
		fprintf(stderr, "Error: Failed to create screen image.\n");
		mlx_terminate(data.mlx);
		return (EXIT_FAILURE);
	}
	
	// 5. Mostrar la imagen en la ventana
	if (mlx_image_to_window(data.mlx, screen, 0, 0) == -1)
	{
		fprintf(stderr, "Error: Failed to put image to window.\n");
		mlx_terminate(data.mlx);
		return (EXIT_FAILURE);
	}

	// 6. Cargar texturas
	load_text(&data);

	// 7. Inicializar jugador y hacer raycasting inicial
	cu_init_player(&data.game.player, &data.game);
	cu_cast_rays(&data, screen);

	// 7. Configurar hooks y ejecutar loop principal
	mlx_key_hook(data.mlx, key_hook, data.mlx);
	mlx_loop(data.mlx);

	// Cleanup MLX42 internals
	mlx_terminate(data.mlx);
	//Use the function for free all the data stored manually
	mem_clear();
	return (EXIT_SUCCESS);
}
