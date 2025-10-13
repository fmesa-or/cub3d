/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:47:06 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/14 00:52:31 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*************************************************
 * Safe exit that closes all file descriptors and*
 * frees all tracked memory before exiting.      *
 ************************************************/
void	sexit(int code)
{
	sclose(STDIN_FILENO);
	sclose(STDOUT_FILENO);
	sclose(STDERR_FILENO);
	sclose_all();
	sfree_all();
	exit(code);
}

/**************************************************
 * Handles allocation failures by printing error  *
 * messages and performing safe exit with cleanup.*
 *************************************************/
void	alloc_fail(int type)
{
	if (type == NO_MEMORY)
		error_msg("Error\nVMEM: No memory left on the device\n");
	sexit(1);
}

/*****************************************************
 * Global data accessor using static variable.     *
 * Stores data when called with parameter, returns *
 * stored data when called with NULL.               *
 ****************************************************/
t_data	*get_pdata(t_data *data)
{
	static t_data	*pdata;

	if (data)
		pdata = data;
	return (pdata);
}

/*****************************************************
 * Sets memory area to specified value byte by    *
 * byte. Custom implementation of memset.          *
 ****************************************************/
void	*ft_memset(void *b, int c, int len)
{
	unsigned char	*p;

	p = b;
	while (len--)
		*p++ = (unsigned char)c;
	return (b);
}

/*****************************************************
 * Zeros out memory area. Custom implementation of  *
 * bzero function for memory initialization.        *
 ****************************************************/
void	*ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*a;

	i = 0;
	a = (char *)s;
	if (n == 0)
	{
		return (0);
	}
	while (i < n)
	{
		a[i] = 0;
		i++;
	}
	return (0);
}
