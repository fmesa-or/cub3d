/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:38:23 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/26 20:38:39 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;
	char	*dst_;
	char	*src_;

	i = 0;
	n = 0;
	dst_ = dst;
	src_ = (char *)src;
	while (src[n] != '\0')
		n++;
	if (dstsize == 0)
		return (n);
	if (dstsize != '\0')
	{
		while (i < dstsize - 1 && i < n)
		{
			dst_[i] = src_[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (n);
}
