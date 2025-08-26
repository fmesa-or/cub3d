/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sfree_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:31:11 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/26 20:32:30 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sfree_split(char **array)
{
	int i = 0;

	if (!array)
		return ;
	while (array[i])
	{
		sfree(array[i]);
		i++;
	}
	sfree(array);
}