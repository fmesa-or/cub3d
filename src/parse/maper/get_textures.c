/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:19:04 by crmorale          #+#    #+#             */
/*   Updated: 2025/09/08 21:04:35 by fmesa-or         ###   ########.fr       */
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

int valid_tex(char *path)
{
	if (!path)
		return (0);
	return (check_tex_path(path) && check_xpm(path));
}

char	*get_texture_path(char *line, int j)
{
	int	 len;
	int	 i;
	char	*path;
	while (line[j] && ft_isspace(line[j]))
		j++;
	len = j;
	while (line[len] && !ft_isspace(line[len]) && line[len] != '\n')
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

void	final_tex_check(t_textinfo *tex)
{
	if (!tex->has_no || !tex->has_so || !tex->has_ea || !tex->has_we
		|| !tex->has_c || !tex->has_f)
		error_msg("Error\nCannot find all the textures and colors in map file.\n");
	if (!valid_tex(tex->no_path) || !valid_tex(tex->so_path)
		|| !valid_tex(tex->ea_path) || !valid_tex(tex->we_path))
		error_msg("Error\nInvalid textures or texture paths.\n");
}

//revisa si tenemos todos los datos? para poder enviar la posición i?
void	parse_textures(char **map_array, t_textinfo *tex, int *i)
{
	char	*line;
	while (map_array[*i])
	{
		line = map_array[*i];
		while (*line && ft_isspace(*line))
			line++;
		if (!ft_strncmp(line, "NO", 2) && tex->has_no == 0)
		{
			tex->no_path = get_texture_path(line, 2);
			tex->has_no++;
		}
		else if (!ft_strncmp(line, "SO", 2) && tex->has_so == 0)
		{
			tex->so_path = get_texture_path(line, 2);
			tex->has_so++;
		}
		else if (!ft_strncmp(line, "WE", 2) && tex->has_we == 0)
		{
			tex->we_path = get_texture_path(line, 2);
			tex->has_we++;
		}
		else if (!ft_strncmp(line, "EA", 2) && tex->has_ea == 0)
		{
			tex->ea_path = get_texture_path(line, 2);
			tex->has_ea++;
		}
		else if (*line == 'F' && tex->has_f == 0)
		{
			parse_rgb_line(line + 1, tex->floor);
			tex->has_f++;
		}
		else if (*line == 'C' && tex->has_c == 0)
		{
			parse_rgb_line(line + 1, tex->ceiling);
			tex->has_c++;
		}
		else if (*line == '1' || *line == '0')
			break ;			// aquí empezaría el mapa
		(*i)++;
	}
	final_tex_check(tex); // ***AÑADIDA ESTA FUNCIÓN***
	//checkear que las texturas aparezcan 1 vez y que sean minimo todas valor 1.
}