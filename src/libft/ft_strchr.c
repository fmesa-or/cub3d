/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:11:14 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/19 14:16:12 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/********************************************************
 * Returns the string "s" starting where "c" is placing *
 *******************************************************/
char	*ft_strchr(char *s, int c)
{
	char	*ret;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
	{
		ret = &s[ft_strlen(s)];
		return (ret);
	}
	while ((s[i] != '\0'))
	{
		if (s[i] == (unsigned char)c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}
