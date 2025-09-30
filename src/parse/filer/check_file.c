/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmorale <crmorale@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:08:24 by crmorale          #+#    #+#             */
/*   Updated: 2025/08/19 21:05:55 by crmorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * 
 */

void	check_extension(char *file_name)
{
	int	len;

	if (!file_name)
		error_msg("Error:\nNULL file_name.\n");
	len = ft_strlen(file_name);
	if (len <= 4)
		error_msg("Error\nInvalid file extension. Expected .cub file.");
	if (!(file_name[len - 1] == 'b' && file_name[len - 2] == 'u' &&
		file_name[len - 3] == 'c' && file_name[len - 4] == '.'))
		error_msg("Error\nInvalid file extension. Expected .cub file.");
}

void	check_file_exists(char *file_name)
{
	if (access(file_name, F_OK) != 0)
		error_msg("Error\nFile not found.\n");
	if (access(file_name, R_OK) != 0)
		error_msg("Error\nRead file not readable.\n");
}


/**
 * 
 */
void	check_file(char *av)
{
	check_extension(av);
	check_file_exists(av);
}