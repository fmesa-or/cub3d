/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmem.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:16:58 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/18 13:49:12 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VMEM_H
# define VMEM_H

# define MEM_HASH_SIZE 1031

/***
 * 
 */
typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}	t_mem;

/**********************************************************
 * game			-> Main struct                            *
 * mem_table	-> Where we store the info to free memory *
 * fd_table		-> Same but for file descriptors          *
 *********************************************************/
typedef struct s_data
{
	t_game		game;
	t_mem		*mem_table[MEM_HASH_SIZE];
	int			fd_table[1024];
} t_data;

/*************
 * FUNCTIONS *
 ************/
int		sopen(const char *file, int oflag, int perm);
int		sclose(int fd);
void	sfree(void *ptr);
void	mem_delete(void *ptr);
t_data	*get_pdata(t_data *data);
//void	*smalloc(long bytes);
//void	mem_clear(void);
//void	mem_add(void *ptr);
//void	sfree_all(void);
//int		spipe(int *fd);
//int		sdup2(int fd1, int fd2);
//int		sdup(int fd);
//char	*get_cwd(void);
//void	sclose_all(void);
//void	*ft_memset(void *b, int c, int len);
//void	alloc_fail(int type);
//void	sexit(int code);

#endif