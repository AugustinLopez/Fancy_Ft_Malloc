/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_malloc_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 01:08:55 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/12 16:36:52 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

int		free_set(t_metabody *body, const size_t index)
{
	if (((body->free)[index / 8] & (1 << (index % 8))) == 0)
	{
		(body->free)[index / 8] |= (1 << (index % 8));
		return (0);
	}
	return (1);
}

ssize_t	free_get(t_metabody *body)
{
	size_t	max;
	size_t	i;
	size_t	j;

	if (body->id == Z4)
		max = MAX_Z4;
	else
		max = MAX_OTHER;
	i = 0;
	while (i < max)
	{
		j = 0;
		while (j < 8)
		{
			if (((body->free)[i] & (1 << j)) == 0)
				return (i * 8 + j);
			j++;
		}
		i++;
	}
	return (-1);
}

void	size_set(t_metabody *body, const size_t size, const size_t i)
{
	if (body->id == Z4)
	{
		(body->size)[i / 2] &= 0xf0 >> (4 * (i % 2));
		(body->size)[i / 2] |= (size - 1) << (4 * (i % 2));
	}
	else if (body->id <= Z8)
		(body->size)[i] = size - 1;
	else if (body->id <= Z11)
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

void	head_set(t_metabody *body)
{
	t_metahead	*head;

	body->block_count += 1;
	head = (t_metahead *)(body->head);
	if ((body->id == Z4 && body->block_count == 256)
		|| (body->id != Z4 && body->block_count == 128))
		head->full |= (1 << body->index);
}

void	*ptr_get(t_metabody *body, const size_t size)
{
	ssize_t	i;

	if (body->id == ZLARGE)
	{
		size_set(body, size, 0);
		head_set(body);
		return (body->address);
	}
	if((i = free_get(body)) == -1)
		return (NULL);
	free_set(body, i);
	size_set(body, size, i);
	head_set(body);
	return (((uint8_t *)(body->address)) + i * body->id);
}