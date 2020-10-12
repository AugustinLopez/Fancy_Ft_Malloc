/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:48:29 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/12 17:19:00 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

size_t		offset_get(t_metabody *body)
{
	if (body->id == ZLARGE)
		return (*((size_t *)(body->store)));
	else if (body->id == Z4)
		return (body->id * 256);
	else
		return (body->id * 128);
}
int			metablock_free(t_metabody *body, const void *ptr)
{
	size_t	index;

	if (body->id == ZLARGE)
	{
		if (body->block_count != 0)
			body->block_count = 0;
		else
			return (1);
	}
	else
	{
		index = (uintptr_t)ptr - (uintptr_t)(body->address);
		index /= (uintptr_t)(body->id);
		if ((body->free)[index / 8] & (1 << (index % 8)))
		{
			(body->free)[index / 8] ^= (1 << (index % 8));
			body->block_count -= 1;
		}
		else
			return (1);
	}
	return (0);
}
int			metabody_islast(t_metabody *body)
{
	t_metahead *iter;
	size_t		i;
	size_t		j;

	j = 0;
	if (body->id == ZLARGE)
		return (0);
	iter = (t_metahead *)&(body->head);
	while (iter)
	{
		i = 0;
		while (i < AVAILABLE)
		{
			if ((iter->id)[i] == body->id)
				++j;
			if (j > 1)
				return (1);
			++i;
		}
		iter = iter->next;
	}
	return (0);
}

t_metabody	*metabody_find(const void *ptr, t_metadata *start)
{
	t_metadata	*data;
	t_metahead	*head;
	t_metabody	*body;
	size_t		i;

	head = (t_metahead *)&(start->head);
	while (head)
	{
		i = 0;
		data = (t_metadata *)(head->container);
		while (i < AVAILABLE)
		{
			body = (t_metabody *)&((data->body)[i]);
			if ((head->id)[i] == ZLARGE && ptr == body->address)
				return (body);
			if ((head->id)[i] != ZLARGE && (head->id)[i] != 0
			&& ptr >= body->address
			&& (uintptr_t)ptr < (uintptr_t)(body->address) + offset_get(body)
			&& ((uintptr_t)ptr % body->id) == 0)
				return (body);
			i++;
		}
		head = head->next;
	}
	return (NULL);
}

int	metabody_free(t_metabody *body)
{
	t_metahead	*head;
	void		*mem;
	size_t		index;
	int			ret;

	ret = 0;
	if (body->block_count == 0 && (body->id == ZLARGE || metabody_islast(body) == 1))
	{
		head = body->head;
		index = body->index;
		mem = body->address;
		if (body->id == ZLARGE)
			ret = munmap(body->address, *((size_t *)(body->store)));
		else
			ret = munmap(body->address, get_page(body->id));
		(head->id)[index] = 0;
		(head->full) &= (MASK_AVAILABLE ^ (1 << index));
		head->available_heap += 1;
		if (ret == -1)
			log_free_failed(body->address, ERR_FREE_MUNMAP);
		else
			log_metabody_free(body, mem, head);
	}
	return (ret);
}

int		metadata_free(t_metahead *head, t_metadata *start)
{
	void	*ptr;
	int		ret;

	ret = 0;
	if (head->available_heap == AVAILABLE && head->container != (void *)start)
	{
		ptr = head->container;
		if (head->next)
			head->next->prev = head->prev;
		if (head->prev)
			head->prev->next = head->next;
		ret = munmap(ptr, getpagesize());
		if (ret == -1)
			log_free_failed(ptr, ERR_FREE_MUNMAP);
		else
			log_metadata_free((t_metadata *)ptr);
		return (1);
	}
	return (ret);
}

void	mono_free(void *ptr)
{
	t_metabody	*body;
	t_metahead	*head;

	if (ptr == NULL || g_metadata == NULL)
	{
		log_free_failed(ptr, ERR_FREE_INVALID);
		return ;
	}
	body = metabody_find(ptr, g_metadata);
	if (body == NULL)
	{
		log_free_failed(ptr, ERR_FREE_INVALID);
		return ;
	}
	if (metablock_free(body, ptr) == 1)
	{
		log_free_failed(ptr, ERR_FREE_DOUBLE);
		return ;
	}
	head = body->head;
	log_free(ptr, body->block_count);
	metabody_free(body);
	metadata_free(head, g_metadata);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_thread_mutex);
	mono_free(ptr);
	pthread_mutex_unlock(&g_thread_mutex);
}
