/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:00:09 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/20 15:08:50 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/***********************************************************
 * Validates if file path has correct PNG extension.      *
 * Returns 1 if ends with ".png", 0 otherwise.            *
 **********************************************************/
int	check_png(char *path)
{
	int	len;

	len = 0;
	while (path[len])
		len++;
	if (len < 4)
		return (0);
	return (path[len - 4] == '.' && path[len - 3] == 'p'
		&& path[len - 2] == 'n' && path[len - 1] == 'g');
}

/***********************************************************
 * Verifies if texture file path exists and is readable.  *
 * Opens file to test accessibility, returns 1 if valid.  *
 **********************************************************/
int	check_tex_path(char *path)
{
	int	fd;

	fd = sopen(path, O_RDONLY, -1);
	if (fd < 0)
		return (0);
	sclose(fd);
	return (1);
}

/***********************************************************
 * Validates texture by checking path existence and PNG   *
 * extension. Combines path and format validation checks. *
 **********************************************************/
int	valid_tex(char *path)
{
	if (!path)
		return (0);
	return (check_tex_path(path) && check_png(path));
}

/***********************************************************
 * Extracts texture path from configuration line string.  *
 * Skips whitespace and copies path until next delimiter. *
 **********************************************************/
char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && ft_isspace(line[j]))
		j++;
	len = j;
	while (line[len] && !ft_isspace(line[len]) && line[len] != '\n')
		len++;
	path = smalloc(sizeof(char) * (len - j + 1));
	i = 0;
	while (j < len)
		path[i++] = line[j++];
	path[i] = '\0';
	return (path);
}

/***********************************************************
 * Performs final validation of all texture requirements. *
 * Checks all textures and colors are present and valid.  *
 **********************************************************/
void	final_tex_check(t_textinfo *tex)
{
	if (!tex->has_no || !tex->has_so || !tex->has_ea || !tex->has_we
		|| !tex->has_c || !tex->has_f)
		error_msg("Error\nCannot find the textures and colors in map file.\n");
	if (!valid_tex(tex->no_path) || !valid_tex(tex->so_path)
		|| !valid_tex(tex->ea_path) || !valid_tex(tex->we_path))
		error_msg("Error\nInvalid textures or texture paths.\n");
	if (tex->has_no > 1 || tex->has_so > 1 || tex->has_ea > 1 || tex->has_we > 1
		|| tex->has_c > 1 || tex->has_f > 1)
		error_msg("Error\nJust one texture and color by parameter.\n");
}
