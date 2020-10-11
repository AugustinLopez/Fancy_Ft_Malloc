/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metabody_malloc_get.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:11:22 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/11 02:08:38 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>

#include <stdio.h>

/*
** Create a metadata page of the requested type.
** If any error occur, return NULL.
*/

#include  "minilibft.h"

static t_metadata	*metadata_set(void)
{
	t_metadata		*elem;
	t_metahead		*head;
	size_t			requested;

	requested = getpagesize();
	if (get_rlimit(requested) != 0)
		return (NULL);
	elem = (t_metadata *)mmap(NULL, requested,
						PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (elem == MAP_FAILED)
		return (NULL);
	head = &((elem->head).data);
	head->container = elem;
	head->available_heap = AVAILABLE;
	log_metadata_set(elem);
	return (elem);
}

static t_metadata	*metadata_add(t_metadata **start)
{
	t_metadata	*data;
	t_metahead	*head;

	if (!(data = metadata_set()))
		return (NULL);
	if (!*start)
	{
		*start = data;
		return (*start);
	}
	head = &(((*start)->head).data);
	while (head)
	{
		if (head->next == NULL)
			break;
		head = head->next;
	}
	head->next = (t_metahead *)&(data->head);
	head->next->prev = head;
	return (data);
}

static t_metabody	*metabody_set(t_metahead *head,
								const size_t size,
								const size_t index)
{
	t_metabody	*body;
	t_metadata	*data;
	size_t		requested;
	void		*elem;

	requested = get_page(size);
	if (get_rlimit(requested) != 0)
		return (NULL);
	elem = (void *)mmap(NULL, requested,
						PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (elem == MAP_FAILED)
		return (NULL);
	data = (t_metadata *)(head->container);
	body = (t_metabody *)&((data->body)[index]);
	head->available_heap -= 1;
	body->head = head;
	body->index = index;
	body->address = elem;
	body->id = get_flag(size);
	(head->id)[index] = body->id;
	body->block_count = 0;
	log_metabody_set(body, head);
	return (body);
}

static t_metahead	*metahead_find(const t_metadata *start,
									const uint16_t flag,
									size_t *index)
{
	t_metahead	*iter;
	size_t		i;

	if (start == NULL || flag == Z12)
		return (NULL);
	iter = (t_metahead *)&(start->head);
	while (iter)
	{
		if (iter->available_heap)
		{
			i = 0;
			while (i < AVAILABLE)
			{
				if ((iter->id)[i] == flag && ((iter->full) & (1 << i)) == 0)
				{
					*index = i;
					return (iter);
				}
				++i;
			}
		}
		iter = iter->next;
	}
	return (NULL);
}

t_metabody		*metabody_get(const size_t size)
{
	t_metadata	*data;
	t_metahead	*head;
	t_metabody	*body;
	size_t		index;

	index = 0;
	if ((head = metahead_find(g_metadata, get_flag(size), &index)))
	{
		data = (t_metadata *)(head->container);
		body = (t_metabody *)&((data->body)[index]);
		return (body);
	}
	if (!(head = metahead_find(g_metadata, 0, &index)))
	{
		if (!(data = metadata_add(&g_metadata)))
			return (NULL);
		if (!(head = metahead_find(data, 0, &index)))
			return (NULL);
	}
	return (metabody_set(head, size, index));
}
