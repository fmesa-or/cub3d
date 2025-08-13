/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmem.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:16:58 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/08/13 21:56:45 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VMEM_H
# define VMEM_H

# define MEM_HASH_SIZE 1031

/*************
 * FUNCTIONS *
 ************/
int		sopen(const char *file, int oflag, int perm);
int		sclose(int fd);
void	sfree(void *ptr);
void	mem_delete(void *ptr);
//void	mem_clear(void);
//void	mem_add(void *ptr);
//void	sfree_all(void);
//void	*smalloc(long bytes);
//int		spipe(int *fd);
//int		sdup2(int fd1, int fd2);
//int		sdup(int fd);
//void	sclose_all(void);
//char	*get_cwd(void);
//void	*ft_memset(void *b, int c, int len);
//t_data	*get_pdata(t_data *data);
//void	alloc_fail(int type);
//void	sexit(int code);

#endif