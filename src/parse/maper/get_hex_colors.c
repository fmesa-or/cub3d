/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hex_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:53:25 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/20 15:40:29 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/***********************************************************
 * Converts RGB values to 32-bit hexadecimal color format.*
 * Combines R, G, B channels with full opacity (0xFF).    *
 **********************************************************/
static uint32_t	rgb_to_hex(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

/***********************************************************
 * Converts RGB array to hexadecimal color format.        *
 * Wrapper function for rgb_to_hex using array input.     *
 **********************************************************/
uint32_t	get_hex_color(int rgb[3])
{
	return (rgb_to_hex(rgb[0], rgb[1], rgb[2]));
}
