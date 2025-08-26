/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:19:04 by crmorale          #+#    #+#             */
/*   Updated: 2025/08/25 21:20:30 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_xpm(char *path)
{
	int len = 0;
	while (path[len])
		len++;
	if (len < 4)
		return 0;
	return (path[len - 4] == '.' && path[len - 3] == 'x' &&
				path[len - 2] == 'p' && path[len - 1] == 'm');
}

int check_tex_path(char *path)
{
	int fd = sopen(path, O_RDONLY, -1);
	if (fd < 0)
		return 0;
	sclose(fd);
	return 1;
}

int	valid_tex(char *path)
{
	if (!check_tex_path || !check_xpm)
		return (0);
	return (check_tex_path && check_xpm);
}

char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && is_space(line[j]))
		j++;
	len = j;
	while (line[len] && !is_space(line[len]) && line[len] != '\n')
		len++;
	path = smalloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (j < len)
		path[i++] = line[j++];
	path[i] = '\0';
	return (path);
}

//revisa si tenemops todos los datos? para poder enviar la posición i?
void	parse_textures(char **map_array, t_textinfo *tex, int *i)
{
	char	*line;

	while (map_array[*i])
	{
		*line = map_array[*i];
		while (*line && is_space(*line))
			line++;
		if (!strncmp(line, "NO", 2) && !tex->has_no++)
			tex->no_path = get_texture_path(line, 2);
		else if (!strncmp(line, "SO", 2) && !tex->has_so++)
			tex->so_path = get_texture_path(line, 2);
		else if (!strncmp(line, "WE", 2) && !tex->has_we++)
			tex->we_path = get_texture_path(line, 2);
		else if (!strncmp(line, "EA", 2) && !tex->has_ea++)
			tex->ea_path = get_texture_path(line, 2);
		else if (*line == 'F' && !tex->has_f++)
			parse_rgb_line(line + 1, &tex->floor);
		else if (*line == 'C' && !tex->has_c++)
			parse_rgb_line(line + 1, &tex->ceiling);
		else if (*line == '1' || *line == '0')
			break ;			   // aquí empezaría el mapa
		*i++;
	}
	//checkear que las texturas aparezcan 1 vez y que sean minimo todas valor 1.
}
