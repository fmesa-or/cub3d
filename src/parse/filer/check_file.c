/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:08:24 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/13 20:50:47 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/******************************************
 * Validates file has .cub extension.     *
 * Exits with error if invalid or missing.*
 *****************************************/
void	check_extension(char *file_name)
{
	int	len;

	if (!file_name)
		error_msg("Error:\nNULL file_name.\n");
	len = ft_strlen(file_name);
	if (len <= 4)
		error_msg("Error\nInvalid file extension. Expected .cub file.");
	if (!(file_name[len - 1] == 'b' && file_name[len - 2] == 'u'
			&& file_name[len - 3] == 'c' && file_name[len - 4] == '.'))
		error_msg("Error\nInvalid file extension. Expected .cub file.");
}

/*************************************************
 * Checks file exists and is readable.           *
 * Exits with error if not found or not readable.*
 ************************************************/
void	check_file_exists(char *file_name)
{
	if (access(file_name, F_OK) != 0)
		error_msg("Error\nFile not found.\n");
	if (access(file_name, R_OK) != 0)
		error_msg("Error\nRead file not readable.\n");
}

/**************************************************
 * Complete file validation: extension and access.*
 * Combines both extension and existence checks.  *
 *************************************************/
void	check_file(char *av)
{
	check_extension(av);
	check_file_exists(av);
}
