/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:01:30 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/19 14:28:51 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define GNL_BUFF_SIZE 4096

static char	*ft_hold_the_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (!backup)
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));//change for smalloc
	if (!line)
		return (NULL);
	if (backup[i] != '\0')
		line[i + 1] = '\0';
	while (i >= 0)
	{
		line[i] = backup[i];
		i--;
	}
	return (line);
}

static char	*ft_backuper(char *backup)
{
	int		i;
	int		j;
	char	*newbackup;

	i = gnl_jumpfinder(backup);
	if (!backup[i])
	{
		free(backup);//fix
		return (NULL);
	}
	newbackup = (char *)malloc((sizeof(char) * (ft_strlen(backup) - i)));//fix
	if (!newbackup)
		return (NULL);
	j = 0;
	while (backup[i + ++j])
		newbackup[j - 1] = backup[i + j];
	if (backup)
		free (backup);//fix
	newbackup[j - 1] = '\0';
	if (newbackup[0] == '\0')
	{
		free (newbackup);//fix
		return (NULL);
	}
	return (newbackup);
}

static char	*ft_read_left(int fd, char *backup)
{
	int		read_bytes;
	char	*buffer;

	buffer = (char *)malloc((GNL_BUFF_SIZE + 1) * sizeof(char));//fix
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(backup, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, GNL_BUFF_SIZE);//check if read saves memory
		if (read_bytes <= 0)
		{
			free (buffer);//fix
			if (read_bytes == -1)
			{
				free (backup);//fix
				return (NULL);
			}
			return (backup);
		}
		buffer[read_bytes] = '\0';
		backup = gnl_strjoin(backup, buffer);
	}
	free (buffer);//fix
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;

	if (fd < 0 || GNL_BUFF_SIZE <= 0)
		return (NULL);
	backup = ft_read_left(fd, backup);
	if (!backup)
	{
		free (backup);//fix
		backup = NULL;
		return (NULL);
	}
	line = ft_hold_the_line(backup);
	backup = ft_backuper(backup);
	return (line);
}
