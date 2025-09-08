/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmem.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:16:58 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/09/08 20:05:22 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VMEM_H
# define VMEM_H

# define MEM_HASH_SIZE 1031

/*****************************
 * Description for ALLOC FAIL*
 ****************************/
enum e_type
{
	NO_MEMORY = 90,
	DUP_FAIL = 46,
	DUP2_FAIL = 47,
	PIPE_FAIL = 48
};

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
void	*smalloc(long bytes);
void	*scalloc(size_t count, size_t size);
void	alloc_fail(int type);
void	mem_add(void *ptr);
void	sexit(int code);
void	sclose_all(void);
void	sfree_all(void);
void	mem_clear(void);
void	*ft_memset(void *b, int c, int len);
void	*ft_bzero(void *s, size_t n);
//int		spipe(int *fd);
//int		sdup2(int fd1, int fd2);
//int		sdup(int fd);
//char	*get_cwd(void);

#endif