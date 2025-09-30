/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:29:47 by crmorale          #+#    #+#             */
/*   Updated: 2025/09/30 13:18:04 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi_rgb(const char *str)
{
	int	i;
	int	result;
	
	i = 0;
	result = 0;
	while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0') //para string vacíos o sólo espacios
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while (str[i] >= 48 && str[i] <= 57) 
	{
		if (result > (INT_MAX - (str[i] - 48)) / 10) // Detectar Overflow
			return (-1);
		result = result * 10 + str[i] - 48;
		i++;
	}
	// Skip trailing whitespace
	while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (-1);
	return (result);
}

int	valid_rgb_value(int n)
{
	return (n >= 0 && n <= 255);
}

static uint32_t	rgb_to_hex(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

	/*LLAMAR a get_hex_color desde la que lo necesitemos del siguiente modo:
	
		uint32_t floor_color = get_color(game->textures->floor);
		uint32_t floor_ceiling = get_color(game->textures->ceiling);
	*/

uint32_t	get_hex_color(int rgb[3])
{
	return (rgb_to_hex(rgb[0], rgb[1], rgb[2]));
}

	
/**
 * 
 */
int	parse_rgb_line(char *line, int rgb[3])
{
	char	**parts;
	int		i;

	// saltar espacios
	while ((*line >= 9 && *line <= 13) || *line == 32)
		line++;
	// dividir por coma
	parts = ft_split(line, ','); //añadir split
	if (!parts)
		return (0);
	// comprobar que hay exactamente 3 valores
	i = 0;
	while (i < 3)
	{
		if (!parts[i])
		{
			ft_sfree_split(parts);
			return (0);
		}
		rgb[i] = ft_atoi_rgb(parts[i]);
		if (!valid_rgb_value(rgb[i]))
		{
			ft_sfree_split(parts);
			return (0);
		}
		i++;
	}
	if (parts[3]) // más de 3 valores -> error
	{
		ft_sfree_split(parts);
		return (0);
	}
	ft_sfree_split(parts);
	return (1);
}