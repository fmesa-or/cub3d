/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:01:23 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/25 14:20:44 by fmesa-or         ###   ########.fr       */
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
	t_data	data;

	if (ac != 2)
		error_msg("Error\nPlease, run Cub3D with exactly one argument.\n");

	// Inicializar el sistema de memoria
		//iniciar a 0 los datos de las texturas.???? init data
	ft_memset(&data, 0, sizeof(t_data));//meter dentro de init data
	get_pdata(&data);


	//TESTING
	check_and_parse_file(av[1], &data);
	cu_init_player(&data.game.player, &data.game);
	cu_cast_rays(&data);

	//END TEST



	data.mlx = mlx_init(S_WIDTH, S_HEIGHT, "CUB3D", true);
	if (!data.mlx)
	{
		fprintf(stderr, "Error: MLX42 init failed.\n");
		return (EXIT_FAILURE);
	}
	//Hook ESC to close
	mlx_key_hook(data.mlx, key_hook, data.mlx);
	//Run main loop
	mlx_loop(data.mlx);

	// Cleanup MLX42 internals
	mlx_terminate(data.mlx);
	//Use the function for free all the data stored manually
	mem_clear();
	return (EXIT_SUCCESS);
}
