/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomoron <tomoron@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:41:22 by tomoron           #+#    #+#             */
/*   Updated: 2024/12/05 17:32:25 by tomoron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

t_mem_chunk	*get_alloc_chunk(t_alloc *alloc, t_mem_chunk *first, size_t size);
int			get_prev_alloc(t_alloc **alloc, t_alloc **res, t_alloc *cur, \
		char *fnc);

static void	*realloc_recreate(t_alloc *alloc, size_t size)
{
	void	*new;

	pthread_mutex_unlock(&g_mallock);
	new = malloc(size);
	pthread_mutex_lock(&g_mallock);
	if (alloc->size < size)
		size = alloc->size;
	pthread_mutex_unlock(&g_mallock);
	ft_memcpy(new, alloc + 1, size);
	free(alloc + 1);
	pthread_mutex_lock(&g_mallock);
	return (new);
}

static void	*realloc_prealloc(t_alloc *alloc, t_mem_chunk *chunk, \
	int is_small, size_t size)
{
	t_alloc	*prev;

	chunk = get_alloc_chunk(alloc, chunk, is_small);
	if (!chunk)
		return (0);
	if (!get_prev_alloc(&alloc, &prev, chunk->first, "realloc"))
		return (0);
	if (alloc->size >= size)
	{
		chunk->space_left += alloc->size - size;
		alloc->size = size;
		return (alloc + 1);
	}
	if ((size > (size_t)TINY_MALLOC && is_small == 0)
		|| (size > SMALL_MALLOC && is_small == 1)
		|| (t_ul)(alloc->next) - (t_ul)(alloc + 1) < size)
		return (realloc_recreate(alloc, size));
	chunk->space_left -= size - alloc->size;
	alloc->size = size;
	return (alloc + 1);
}

static void	*realloc_large(t_alloc *alloc, size_t size)
{
	t_alloc	*prev;

	if (!get_prev_alloc(&alloc, &prev, g_allocs.large, "realloc"))
		return (0);
	return (realloc_recreate(alloc, size));
}

void	*realloc(void *ptr, size_t size)
{
	t_alloc	*alloc;

	if (!ptr)
		return (malloc(size));
	alloc = (t_alloc *)ptr - 1;
	pthread_mutex_lock(&g_mallock);
	ptr = realloc_prealloc(alloc, g_allocs.tiny, 0, size);
	if(!ptr)
		ptr = realloc_prealloc(alloc, g_allocs.small, 1, size);
	if(!ptr)
		ptr = realloc_large(alloc, size);
	pthread_mutex_unlock(&g_mallock);
	return(ptr);
}
