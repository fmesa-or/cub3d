/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_man.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:53:35 by fmesa-or          #+#    #+#             */
/*   Updated: 2025/10/13 20:41:46 by fmesa-or         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**************************************************
 * Generates hash index from pointer address using*
 * bit manipulation for uniform distribution.     *
 *************************************************/
static unsigned int	hash_index_ptr(void *ptr)
{
	unsigned long	addr;

	addr = (unsigned long)ptr;
	addr = ~addr + (addr << 15);
	addr = addr ^ (addr >> 12);
	addr = addr + (addr << 2);
	addr = addr ^ (addr >> 4);
	addr = addr * 2057;
	addr = addr ^ (addr >> 16);
	return (addr % MEM_HASH_SIZE);
}

/*************************************************
 * Searches for memory node in hash table by ptr.*
 * Returns node if found, NULL otherwise.        *
 ************************************************/
static t_mem	*mem_find(void *ptr)
{
	t_data	*data;
	t_mem	*mem;

	data = get_pdata(NULL);
	if (!data || !ptr)
		return (NULL);
	mem = data->mem_table[hash_index_ptr(ptr)];
	while (mem)
	{
		if (mem->ptr == ptr)
			return (mem);
		mem = mem->next;
	}
	return (NULL);
}

/********************************************
 * Adds new memory pointer to hash table.   *
 * Updates existing node or creates new one.*
 *******************************************/
void	mem_add(void *ptr)
{
	t_data			*data;
	unsigned int	i;
	t_mem			*new_mem;
	t_mem			*new_node;

	data = get_pdata(NULL);
	if (!data || !ptr)
		return ;
	new_mem = mem_find(ptr);
	if (new_mem)
	{
		free(new_mem->ptr);
		new_mem->ptr = ptr;
	}
	else
	{
		i = hash_index_ptr(ptr) % MEM_HASH_SIZE;
		new_node = malloc(sizeof(t_mem));
		if (!new_node)
			alloc_fail(NO_MEMORY);
		new_node->ptr = ptr;
		new_node->next = data->mem_table[i];
		data->mem_table[i] = new_node;
	}
}

/************************************************
 * Removes memory node from hash table and frees*
 * both the stored pointer and the node itself. *
 ***********************************************/
void	mem_delete(void *ptr)
{
	t_data			*data;
	unsigned int	i;
	t_mem			*mem;
	t_mem			*prev;

	data = get_pdata(NULL);
	if (!data || !ptr)
		return ;
	i = hash_index_ptr(ptr);
	mem = data->mem_table[i];
	prev = NULL;
	while (mem)
	{
		if (mem->ptr == ptr)
		{
			if (prev)
				prev->next = mem->next;
			else
				data->mem_table[i] = mem->next;
			return (free(mem->ptr), free(mem));
		}
		prev = mem;
		mem = mem->next;
	}
	free(ptr);
}

/***********************************************
 * Clears entire memory hash table, freeing all*
 * stored pointers and nodes. Used for cleanup.*
 **********************************************/
void	mem_clear(void)
{
	t_data			*data;
	unsigned int	i;
	t_mem			*mem;
	t_mem			*next;

	i = 0;
	data = get_pdata(NULL);
	while (data && i < MEM_HASH_SIZE)
	{
		if (data->mem_table[i])
		{
			mem = data->mem_table[i];
			while (mem)
			{
				next = mem->next;
				free(mem->ptr);
				free(mem);
				mem = next;
			}
			data->mem_table[i] = NULL;
		}
		i++;
	}
}
