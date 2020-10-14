/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:51:21 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 19:53:24 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>
#include <unistd.h>
#include "minilibft.h"

static void	malloc_set_size(t_metabody *body, const size_t size, const size_t i)
{
	if (body->id == Z4)
	{
		(body->size)[i / 2] &= 0xf0 >> (4 * (i % 2));
		(body->size)[i / 2] |= (size - 1) << (4 * (i % 2));
	}
	else if (body->id <= Z8)
		(body->size)[i] = size - 1;
	else if (body->id <= ZMAX)
	{
		body->size[i] = (size - 1) >> 4;
		(body->store)[i / 2] &= 0xf0 >> (4 * (i % 2));
		(body->store)[i / 2] |= ((size - 1) & 0xf) << (4 * (i % 2));
	}
	else
	{
		*((size_t *)(body->size)) = size - 1;
		*((size_t *)(body->store)) = (size / getpagesize()) * getpagesize();
		if (size % getpagesize())
			*((size_t *)(body->store)) += getpagesize();
	}
}

static void	malloc_set_head(t_metabody *body)
{
	t_metahead	*head;

	body->block_count += 1;
	head = (t_metahead *)(body->head);
	if ((body->id == Z4 && body->block_count == 256)
		|| (body->id != Z4 && body->block_count == 128))
		head->full |= (1 << body->index);
}

/*
** Set and return a pointer from a metabody.
*/

static void	*malloc_ptr(t_metabody *body, const size_t size)
{
	ssize_t		i;

	if (body->id == ZLARGE)
	{
		malloc_set_size(body, size, 0);
		malloc_set_head(body);
		return (body->address);
	}
	if ((i = metablock_get_available_index(body)) == -1)
		return (NULL);
	if (((body->free)[i / 8] & (1 << (i % 8))) == 0)
		(body->free)[i / 8] |= (1 << (i % 8));
	malloc_set_size(body, size, i);
	malloc_set_head(body);
	return (((uint8_t *)(body->address)) + i * body->id);
}

/*
** 1. Look for a valid metabody
** 2. Get a pointer from the metabody
*/

void		*mono_malloc(size_t size)
{
	void		*ret;
	t_metabody	*body;

	if (size == 0)
		return (NULL);
	body = metabody_get(size);
	if (body == NULL)
		return (NULL);
	ret = malloc_ptr(body, size);
	if (ret == NULL)
		return (NULL);
	if ((get_env() & ENV_PRESCRIBBLE) != 0)
		(void)ft_memset(ret, 0xaa, size);
	log_malloc(body, ret, size);
	return (ret);
}

void		*malloc(size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_thread_mutex);
	ret = mono_malloc(size);
	pthread_mutex_unlock(&g_thread_mutex);
	return (ret);
}
