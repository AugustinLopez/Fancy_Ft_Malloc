/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:48:29 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/11 02:22:17 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

size_t		offset_get(t_metabody *body)
{
	if (body->id == Z12)
		return (*((size_t *)(body->store)));
	else if (body->id == Z4)
		return (body->id * 256);
	else
		return (body->id * 128);
}
void		metablock_free(t_metabody *body, const void *ptr)
{
	size_t	index;

	if (body->id == Z12)
		body->block_count = 0;
	else
	{
		index = (uintptr_t)ptr - (uintptr_t)(body->address);
		index /= (uintptr_t)(body->address);
		if ((body->free)[index / 8] & (1 << (index % 8)))
		{
			(body->free)[index / 8] &= (0xff ^ (1 << (index % 8)));
			body->block_count -= 1;
		}
	}
}
int			metabody_islast(t_metabody *body)
{
	t_metahead *iter;
	size_t		i;
	size_t		j;

	j = 0;
	if (body->id == Z12)
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

t_metabody	*metabody_find(void *ptr, t_metadata *start)
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
			if ((body->id == Z12 && ptr == body->address)
			|| (ptr >= body->address
			&& (uintptr_t)ptr < (uintptr_t)(body->address) + offset_get(body)
			&& ((uintptr_t)ptr % body->id) == 0))
				return (body);
			i++;
		}
		head = head->next;
	}
	return (NULL);
}

#include "minilibft.h"

void	metabody_free(t_metabody *body)
{
	t_metahead	*head;
	size_t		index;

	if (body->block_count == 0 && (body->id == Z12 || metabody_islast(body) == 1))
	{
		head = body->head;
		index = body->index;
		if (body->id == Z12)
			munmap(body->address, *((size_t *)(body->store)));
		else
			munmap(body->address, get_page(body->id));
		(head->id)[index] = 0;
		(head->full) &= (0xff ^ (1 << index));
		head->available_heap += 1;
	}
}

void	metadata_free(t_metahead *head)
{
	void	*ptr;

	ptr = head->container;
	if (head->next)
		head->next->prev = head->prev;
	if (head->prev)
		head->prev->next = head->next;
	munmap(ptr, getpagesize());
}

void	mono_free(void *ptr)
{
	t_metabody	*body;
	t_metahead	*head;

	if (ptr == NULL || g_metadata == NULL)
		return ;
	body = metabody_find(ptr, g_metadata);
	if (body == NULL)
		return ;
	metablock_free(body, ptr);
	head = body->head;
	metabody_free(body);
	if (head->available_heap == AVAILABLE && head->container != g_metadata)
		metadata_free(head);
	log_free(body, ptr);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_thread_mutex);
	mono_free(ptr);
	pthread_mutex_unlock(&g_thread_mutex);
}
