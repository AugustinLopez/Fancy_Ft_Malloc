/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_malloc_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 01:08:55 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/10 14:47:28 by aulopez          ###   ########.fr       */
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
	t_metahead	*head;

	if (body->id == Z4)
	{
		(body->size)[i / 2] &= 0xf0 >> (4 * (i % 2));
		(body->size)[i / 2] |= size << (4 * (i % 2));
	}
	else if (body->id <= Z10)
		(body->size)[i] = size;
	else if (body->id == Z11)
	{
		body->size[i] = size >> 4;
		(body->store)[i / 2] &= 0xf0 >> (4 * (i % 2));
		(body->store)[i / 2] |= (size & 0xf) << (4 * (i % 2));
	}
	else
	{
		*((size_t *)(body->size)) = size;
		*((size_t *)(body->store)) = (size / getpagesize()) * getpagesize();
		if (size % getpagesize())
			*((size_t *)(body->store)) += getpagesize();
		//printf("%zu\n", *((size_t *)(body->store)));
	}
}

void	head_set(t_metabody *body)
{
	t_metahead	*head;

	body->available_block -= 1;
	head = (t_metahead *)(body->head);
	if (body->available_block == 0)
		head->full |= (1 << body->index);
}

void	*ptr_get(t_metabody *body, const size_t size)
{
	void	*ret;
	ssize_t	i;

	if (body->id == Z12)
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
