/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:01:23 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/20 18:58:20 by fmesa-or         ###   ########.fr       */
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

int	main(void)
{
	mlx_t	*mlx;
	t_data	data;
	
	// Inicializar el sistema de memoria
	ft_memset(&data, 0, sizeof(t_data));
	get_pdata(&data);

	//test
	char	**array;
	array = read_file("docs/notes/tareas");
	if (array == NULL)
		printf("Error: No se pudo leer el archivo 'docs/notes/tareas'\n");
	else
	{
		int	i = 0;
		printf("Contenido del archivo:\n");
		while (array[i])
		{
			printf("Línea %d: %s", i + 1, array[i]);
			i++;
		}
	}

	mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!mlx)
	{
		fprintf(stderr, "Error: MLX42 init failed.\n");
		return (EXIT_FAILURE);
	}
	//Hook ESC to close
	mlx_key_hook(mlx, key_hook, mlx);
	//Run main loop
	mlx_loop(mlx);

	// Cleanup MLX42 internals
	mlx_terminate(mlx);
	//Use the function for free all the data stored manually
	mem_clear();
	return (EXIT_SUCCESS);
}
