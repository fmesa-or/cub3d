/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:29:47 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/13 21:55:42 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/***********************************************************
 * Converts string to integer with RGB validation rules.  *
 * Returns -1 for invalid format, signs, or overflow.     *
 **********************************************************/
int	ft_atoi_rgb(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
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
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (-1);
	return (result);
}

/***********************************************************
 * Validates if integer is within valid RGB range (0-255).*
 * Returns 1 if valid, 0 if outside RGB boundaries.       *
 **********************************************************/
int	valid_rgb_value(int n)
{
	return (n >= 0 && n <= 255);
}

/**************************************************************
 * Parses three RGB components from split string array.      *
 * Validates each value and stores in rgb array if valid.    *
 *************************************************************/
static int	sub_parse_rgb_line(char ***parts, int rgb[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!(*parts)[i])
		{
			ft_sfree_split((*parts));
			return (0);
		}
		rgb[i] = ft_atoi_rgb((*parts)[i]);
		if (!valid_rgb_value(rgb[i]))
		{
			ft_sfree_split((*parts));
			return (0);
		}
		i++;
	}
	return (1);
}

/**************************************************************
 * Parses RGB color line in format "R,G,B" from config file.*
 * Splits by comma and validates exactly three RGB values.   *
 *************************************************************/
int	parse_rgb_line(char *line, int rgb[3])
{
	char	**parts;

	while ((*line >= 9 && *line <= 13) || *line == 32)
		line++;
	parts = ft_split(line, ',');
	if (!parts)
		return (0);
	if (sub_parse_rgb_line(&parts, rgb) == 0)
		return (0);
	if (parts[3])
	{
		ft_sfree_split(parts);
		return (0);
	}
	ft_sfree_split(parts);
	return (1);
}
