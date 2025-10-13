/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:21:41 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/13 22:42:44 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**********************************
 * Sets to 0/NULL every parameter.*
 *********************************/
void	init_textinfo(t_textinfo *info)
{
	int	i;

	if (!info)
		return ;
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->ea_path = NULL;
	i = 0;
	while (i < 3)
	{
		info->floor[i] = -1;
		info->ceiling[i] = -1;
		i++;
	}
	info->has_no = 0;
	info->has_so = 0;
	info->has_we = 0;
	info->has_ea = 0;
	info->has_c = 0;
	info->has_f = 0;
}

/**********************************
 * Sets to 0/NULL every parameter.*
 *********************************/
void	init_img_struct(t_img_text *img_text)
{
	img_text->img = NULL;
	img_text->width = 0;
	img_text->height = 0;
}
