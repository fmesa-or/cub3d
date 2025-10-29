/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:01:30 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/13 21:18:17 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define GNL_BUFF_SIZE 4096

/**********************************************
 * Extracts one line from backup buffer.      *
 * Allocates memory for line including newline*
 * character and null terminator.             *
 *********************************************/
static char	*ft_hold_the_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (!backup)
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	line = (char *)smalloc(sizeof(char) * (i + 2));
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

/***********************************************
 * Updates backup buffer after line extraction.*
 * Removes processed line, keeps remaining text*
 * for next get_next_line() call.              *
 **********************************************/
static char	*ft_backuper(char *backup)
{
	int		i;
	int		j;
	char	*newbackup;

	i = gnl_jumpfinder(backup);
	if (!backup[i])
	{
		sfree(backup);
		return (NULL);
	}
	newbackup = (char *)smalloc((sizeof(char) * (ft_strlen(backup) - i)));
	if (!newbackup)
		return (NULL);
	j = 0;
	while (backup[i + ++j])
		newbackup[j - 1] = backup[i + j];
	if (backup)
		sfree (backup);
	newbackup[j - 1] = '\0';
	if (newbackup[0] == '\0')
	{
		sfree (newbackup);
		return (NULL);
	}
	return (newbackup);
}

/**********************************************
 * Reads from file descriptor until newline or*
 * EOF is found. Appends read data to backup  *
 * buffer using fixed-size buffer chunks.     *
 *********************************************/
static char	*ft_read_left(int fd, char *backup)
{
	int		read_bytes;
	char	*buffer;

	buffer = (char *)smalloc((GNL_BUFF_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(backup, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, GNL_BUFF_SIZE);
		if (read_bytes <= 0)
		{
			sfree (buffer);
			if (read_bytes == -1)
			{
				sfree (backup);
				return (NULL);
			}
			return (backup);
		}
		buffer[read_bytes] = '\0';
		backup = gnl_strjoin(backup, buffer);
	}
	sfree (buffer);
	return (backup);
}

/*********************************************
 * Reads and returns one line from file      *
 * descriptor. Uses static buffer to maintain*
 * state between calls. Returns NULL at EOF. *
 ********************************************/
char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;

	if (fd < 0 || GNL_BUFF_SIZE <= 0)
		return (NULL);
	backup = ft_read_left(fd, backup);
	if (!backup)
	{
		sfree (backup);
		backup = NULL;
		return (NULL);
	}
	line = ft_hold_the_line(backup);
	backup = ft_backuper(backup);
	return (line);
}
