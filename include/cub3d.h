/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:01:46 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/19 15:35:19 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "MLX42/MLX42.h"
# include "game.h"
# include "vmem.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

/**********
 * WINDOW *
 *********/
# define WIDTH 800
# define HEIGHT 600

/**********
 * COLORS *
 *********/
# define RD		"\033[1;91m"
# define PR		"\033[4;95m"
# define CI		"\033[0;96m"
# define GR		"\033[0;92m"
# define PI		"\033[0;94m"
# define FF		"\033[0;97m"
# define RES	"\033[0m"

/*********
 * CUB3D *
 ********/
char	**read_file(const char *filename);


/************
 *   GNL    *
 ***********/

char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
int		gnl_jumpfinder(char *backup);

/*************
 *   LIBFT   *
 ************/

int		ft_strlen(char *s);
char	*ft_strchr(char *s, int c);


#endif