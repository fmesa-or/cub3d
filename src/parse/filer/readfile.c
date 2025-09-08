/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:25:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/08 18:05:51 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * READING THE FILE
 * Saves the (map).cub into one string
 * 
 * Queremos recibir un archivo y convertirlo en un array separado por saltos de linea
 */
char	**read_file(const char *filename)
{
	int		fd;
	char	*line;
	char	**array;
	char	**tmp;
	int		i;
	int		j;

	//abrimos el archivo
	fd = sopen(filename, O_RDONLY, -1);
	if (fd < 0)
		return (NULL);

	array = smalloc(sizeof(char *)); // array vacío
	if (!array)
		//ERROR
	array[0] = NULL;
	i = 0;

	//creamos un bucle para automatizar todas las demas posibles lineas si existieran
	while ((line = get_next_line(fd)) != NULL)
	{
		// reservar nuevo array con 1 slot más
		tmp = smalloc(sizeof(char *) * (i + 2));
		// copiar punteros existentes
		j = -1;
		while (++j < i)
			tmp[j] = array[j];
		// añadir nueva línea
		tmp[i] = line;
		tmp[i + 1] = NULL;

		sfree(array);   // liberar solo el array (no sus strings)
		array = tmp;
		i++;
	}

	sclose(fd);//fix sclose!!

	return (array);
}
