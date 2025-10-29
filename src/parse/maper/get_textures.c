/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:19:04 by crmorale          #+#    #+#             */
/*   Updated: 2025/10/22 20:57:44 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sub_parse_textures(int flag, t_textinfo *tex, char **line)
{
	if (flag == 1)
		tex->no_path = get_texture_path((*line), 2);
	else if (flag == 2)
		tex->so_path = get_texture_path((*line), 2);
	else if (flag == 3)
		tex->ea_path = get_texture_path((*line), 2);
	else if (flag == 4)
		tex->we_path = get_texture_path((*line), 2);
	else if (flag == 5)
	{
		if (!parse_rgb_line((*line) + 1, tex->floor))
			error_msg("Error\nInvalid floor colour value.\n");
	}
	else if (flag == 6)
	{
		if (!parse_rgb_line((*line) + 1, tex->ceiling))
			error_msg("Error\nInvalid ceiling colour value.\n");
	}
	return (1);
}

/**********************************************************
 * Parses texture identifiers and RGB values from map     *
 * file. Extracts NO, SO, EA, WE textures and F, C colors.*
 * Stops when map data (1 or 0) is found.                 *
 *********************************************************/
void	parse_textures(char **map_array, t_textinfo *tex, int *i)
{
	char	*line;

	while (map_array[*i])
	{
		line = map_array[*i];
		while (*line && ft_isspace(*line))
			line++;
		if (!ft_strncmp(line, "NO", 2))
			tex->has_no += sub_parse_textures(1, tex, &line);
		else if (!ft_strncmp(line, "SO", 2))
			tex->has_so += sub_parse_textures(2, tex, &line);
		else if (!ft_strncmp(line, "EA", 2))
			tex->has_ea += sub_parse_textures(3, tex, &line);
		else if (!ft_strncmp(line, "WE", 2))
			tex->has_we += sub_parse_textures(4, tex, &line);
		else if (*line == 'F')
			tex->has_f += sub_parse_textures(5, tex, &line);
		else if (*line == 'C')
			tex->has_c += sub_parse_textures(6, tex, &line);
		else if (*line == '1' || *line == '0')
			break ;
		(*i)++;
	}
	final_tex_check(tex);
}
