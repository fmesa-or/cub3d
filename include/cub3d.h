/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:01:46 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/13 19:14:16 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>

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

/*******
 * MEM *
 ******/
# define MEM_HASH_SIZE 1031
//void	mem_clear(void);
//void	mem_delete(void *ptr);
//void	mem_add(void *ptr);
//int		sopen(const char *file, int oflag, int perm);
//void	sfree_all(void);
//void	sfree(void *ptr);
//void	*smalloc(long bytes);
//int		spipe(int *fd);
//int		sdup2(int fd1, int fd2);
//int		sdup(int fd);
//void	sclose_all(void);
//int		sclose(int fd);
//char	*get_cwd(void);
//void	*ft_memset(void *b, int c, int len);
//t_data	*get_pdata(t_data *data);
//void	alloc_fail(int type);
//void	sexit(int code);


#endif