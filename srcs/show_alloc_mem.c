/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 11:29:59 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/12 22:15:31 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "minilibft.h"
#include <pthread.h>
#include <stdio.h>
#include <stddef.h>

void		print_zone(t_metabody *body)
{
	uint16_t	flag;

	flag = get_flag(body->id);
	if (ZONE_BONUS == 0)
	{
		if (flag == TINY)
			ft_printf("TINY : %#X\n", (uintptr_t)(body->address));
		else if (flag == SMALL)
			ft_printf("SMALL : %#X\n", (uintptr_t)(body->address));
		else
			ft_printf("LARGE : %#X\n", (uintptr_t)(body->address));
	}
	else
	{
		if (flag != ZLARGE)
			ft_printf("Zone [ %d ] : %#X\n", body->id, (uintptr_t)(body->address));
		else
			ft_printf("LARGE : %#X\n", (uintptr_t)(body->address));
	}
}

size_t		print_allocation(t_metabody *body)
{
	size_t		i;
	size_t		max;
	size_t		offset;
	size_t		ret;
	uintptr_t	address;

	if (body->id == ZLARGE)
	{
		offset = *((size_t *)(body->size)) + 1;
		address = (uintptr_t)(body->address);
		ft_printf("%#X - %#X : %zu bytes\n", address, address + offset, offset);
		return (offset);
	}
	i = 0;
	ret = 0;
	max = 128 + 128 * (body->id == Z4);
	while (i < max)
	{
		if (((body->free)[i / 8] & (1 << (i % 8))) != 0)
		{
			if (body->id == Z4 && i % 2)
				offset = ((body->size)[i / 2] & 0xf0) >> 4;
			else if (body->id == Z4)
				offset = (body->size)[i / 2] & 0xf;
			else if (body->id <= Z8)
				offset = (body->size)[i];
			else if (i % 2)
				offset = ((body->size)[i] << 4)  + (((body->store)[i / 2] & 0xf0) >> 4);
			else
				offset = ((body->size)[i] << 4) + ((body->store)[i / 2] & 0xf);
			offset += 1;
			address = (uintptr_t)(body->address) + i * body->id;
			ft_printf("%#X - %#X : %zu bytes\n", address, address + offset, offset);
			ret += offset;
		}
		i++;
	}
	return (ret);
}

void		mono_show_alloc_mem(void)
{
	t_metahead	*iter;
	t_metabody	*body;
	size_t		i;
	size_t		total;

	if (g_metadata == NULL)
		return ;
	total = 0;
	iter = (t_metahead *)&(g_metadata->head);
	while (iter)
	{
		i = 0;
		while (i < AVAILABLE)
		{
			body = (t_metabody *)&((((t_metadata *)(iter->container))->body)[i]);
			if (body->id != 0)
			{
				print_zone(body);
				total += print_allocation(body);
			}
			++i;
		}
		iter = iter->next;
	}
	ft_printf("Total: %zu bytes\n", total);
}

void		show_alloc_mem(void)
{
	pthread_mutex_lock(&g_thread_mutex);
	mono_show_alloc_mem();
	pthread_mutex_unlock(&g_thread_mutex);
}
