/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:29:47 by crmorale          #+#    #+#             */
/*   Updated: 2025/08/25 20:39:50 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int ft_atoi_rgb(const char *str)
{
	int	i;
	int	result;
	
	i = 0;
	result = 0;
	while(str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while (str[i] >= 48 && str[i] <= 57) {
		result = result * 10 + str[i] - 48;
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result);
}

int	valid_rgb_value(int n)
{
	return (n >= 0 && n <= 255);
}

