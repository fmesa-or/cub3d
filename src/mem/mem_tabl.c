/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_tabl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:46:16 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/08 20:04:09 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*smalloc(long bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		alloc_fail(NO_MEMORY);
	mem_add(ptr);
	return (ptr);
}
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

void	sfree(void *ptr)
{
	mem_delete(ptr);
}

void	sfree_all(void)
{
	mem_clear();
}

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
