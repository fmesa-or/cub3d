/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:25:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/13 21:23:13 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*********************************************************************
 * Reads all lines from file descriptor into dynamic array.          *
 * Reallocates array for each new line, preserving existing pointers.*
 ********************************************************************/
static void	sub_read_file(int fd, char ***array)
{
	int		i;
	int		j;
	char	*line;
	char	**tmp;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = smalloc(sizeof(char *) * (i + 2));
		j = -1;
		while (++j < i)
			tmp[j] = (*array)[j];
		tmp[i] = line;
		tmp[i + 1] = NULL;
		sfree((*array));
		(*array) = tmp;
		line = get_next_line(fd);
		i++;
	}
}

/********************************************
 * Reads entire .cub file into string array.*
 * Each line becomes separate array element.*
 * Returns NULL on file open failure.       *
 *******************************************/
char	**read_file(const char *filename)
{
	int		fd;
	char	**array;

	fd = sopen(filename, O_RDONLY, -1);
	if (fd < 0)
		return (NULL);
	array = smalloc(sizeof(char *));
	if (!array)
		error_msg("ERROR\nreadfile.c: read_file: 56: failed to save array.");
	array[0] = NULL;
	sub_read_file(fd, &array);
	sclose(fd);
	return (array);
}
