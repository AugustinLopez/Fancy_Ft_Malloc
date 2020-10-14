/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metabody.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:11:22 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 15:10:39 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include "minilibft.h"

static int	metabody_islast(t_metabody *body)
{
	t_metahead	*iter;
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

/*
** Return the size of a given zone of memory.
*/

static size_t	get_size_zone(t_metabody *body)
{
	if (body->id == ZLARGE)
		return (*((size_t *)(body->store)));
	else if (body->id == Z4)
		return (body->id * 256);
	else
		return (body->id * 128);
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
			&& (uintptr_t)ptr < (uintptr_t)(body->address) + get_size_zone(body)
			&& ((uintptr_t)ptr % body->id) == 0)
				return (body);
			i++;
		}
		head = head->next;
	}
	return (NULL);
}

int			metabody_free(t_metabody *body)
{
	t_metahead	*head;
	void		*mem;
	size_t		index;
	int			ret;

	ret = 0;
	if (body->block_count == 0
	&& (body->id == ZLARGE || metabody_islast(body) == 1))
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

t_metabody		*metabody_get(const size_t size)
{
	t_metadata	*data;
	t_metahead	*head;
	t_metabody	*body;
	size_t		index;

	index = 0;
	if ((head = metadata_find(g_metadata, get_flag(size), &index)))
	{
		data = (t_metadata *)(head->container);
		body = (t_metabody *)&((data->body)[index]);
		return (body);
	}
	if (!(head = metadata_find(g_metadata, 0, &index)))
	{
		if (!(data = metadata_add(&g_metadata)))
			return (NULL);
		if (!(head = metadata_find(data, 0, &index)))
			return (NULL);
	}
	return (metabody_set(head, size, index));
}
