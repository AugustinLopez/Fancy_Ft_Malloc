/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metablock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:29:16 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 19:51:59 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "minilibft.h"
#include <stdint.h>
#include <sys/types.h>

size_t	metablock_get_size(t_metabody *body, const size_t i)
{
	size_t	size;

	if (body->id == ZLARGE)
		size = *((size_t *)(body->size)) + 1;
	else if (body->id == Z4 && i % 2)
		size = ((body->size)[i / 2] & 0xf0) >> 4;
	else if (body->id == Z4)
		size = (body->size)[i / 2] & 0xf;
	else if (body->id <= Z8)
		size = (body->size)[i];
	else if (i % 2)
		size = ((body->size)[i] << 4) + (((body->store)[i / 2] & 0xf0) >> 4);
	else
		size = ((body->size)[i] << 4) + ((body->store)[i / 2] & 0xf);
	return (size + 1);
}

ssize_t	metablock_get_available_index(t_metabody *body)
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

int		metablock_free(t_metabody *body, void *ptr)
{
	size_t	index;

	index = 0;
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
	if ((get_env() & ENV_SCRIBBLE) != 0)
		(void)ft_memset(ptr, 0xaa, metablock_get_size(body, index));
	return (0);
}
