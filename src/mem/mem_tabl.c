/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_tabl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:46:16 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/13 20:42:39 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/************************************************
 * Safe malloc wrapper that adds pointer to hash*
 * table for automatic cleanup on program exit. *
 ***********************************************/
void	*smalloc(long bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		alloc_fail(NO_MEMORY);
	mem_add(ptr);
	return (ptr);
}

/*************************************************
 * Safe calloc wrapper that zeros memory and adds*
 * pointer to hash table for tracking.           *
 ************************************************/
void	*scalloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		ptr = smalloc (0);
		return (ptr);
	}
	ptr = smalloc (count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/***************************************************
 * Safe free wrapper that removes pointer from hash*
 * table and frees memory.                         *
 **************************************************/
void	sfree(void *ptr)
{
	mem_delete(ptr);
}

/*********************************************
 * Frees all tracked memory pointers at once.*
 * Used for program cleanup.                 *
 ********************************************/
void	sfree_all(void)
{
	mem_clear();
}

/***************************************************
 * Safe open wrapper that tracks file descriptors  *
 * for automatic cleanup. Handles both 2 and 3 arg *
 * open() calls based on perm parameter.           *
 **************************************************/
int	sopen(const char *file, int oflag, int perm)
{
	t_data	*data;
	int		fd;

	data = get_pdata(NULL);
	if (!data)
		return (-1);
	fd = -1;
	if (perm == -1)
		fd = open(file, oflag);
	else
		fd = open(file, oflag, perm);
	if (fd >= 0 && fd < 1024)
		data->fd_table[fd] = 1;
	return (fd);
}
