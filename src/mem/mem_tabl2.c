/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_tabl2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:46:55 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/13 20:47:09 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/***************************************************
 * Safe close wrapper that removes fd from tracking*
 * table and closes the file descriptor.           *
 **************************************************/
int	sclose(int fd)
{
	t_data	*data;

	data = get_pdata(NULL);
	if (!data || fd < 0 || fd > 1023)
		return (1);
	data->fd_table[fd] = 0;
	return (close(fd));
}

/**************************************************
 * Closes all tracked file descriptors and clears *
 * the fd table. Used for cleanup on program exit.*
 *************************************************/
void	sclose_all(void)
{
	t_data	*data;
	int		fd;

	data = get_pdata(NULL);
	if (!data)
		return ;
	fd = 0;
	while (fd < 1024)
	{
		if (data->fd_table[fd])
		{
			close(fd);
			data->fd_table[fd] = 0;
		}
		fd++;
	}
}
