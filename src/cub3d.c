/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:01:23 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/25 12:11:24 by fmesa-or         ###   ########.fr       */
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






	
	//test
//	int	i = 0;

	check_and_parse_file(av[1], &data);
//	printf("max col: %d\n", data.game.max_col);
//	printf("max row: %d\n", data.game.max_row);
//	printf("spawn_dir: %c\n", data.game.spawn_dir);
//	printf("x: %d\n", data.game.spawn_x);
//	printf("y: %d\n", data.game.spawn_y);
//	printf("ceiling: %d\n", *data.game.textures->ceiling);
//	printf("floor: %d\n", *data.game.textures->floor);
//	printf("ea: %s\n", data.game.textures->ea_path);
//	printf("no: %s\n", data.game.textures->no_path);
//	printf("so: %s\n", data.game.textures->so_path);
//	printf("we: %s\n", data.game.textures->we_path);
//	while (data.game.map[i])
//	{
//		printf("%s\n", data.game.map[i]);
//		i++;
//	}





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
