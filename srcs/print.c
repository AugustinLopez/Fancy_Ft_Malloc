/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:39:21 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/31 18:03:59 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "minilibft.h"

void		print_dump(void *address, size_t size)
{
	size_t	i;
	uint8_t	*ptr;

	if (size == 0 || address == NULL)
		return ;
	ptr = (uint8_t *)address;
	i = 0;
	while (i < size)
	{
		if (((i + 1) % 16) != 0)
			ft_printf("%02p ", ptr[i]);
		else
			ft_printf("%02p\n", ptr[i]);
		i++;
	}
	if (size % 16 != 0)
		ft_printf("\n");
}

size_t		print_large(t_metabody *body, int option)
{
	size_t		offset;
	uintptr_t	address;

	offset = *((size_t *)(body->size)) + 1;
	address = (uintptr_t)(body->address);
	ft_printf("%#p - %#p : %zu bytes\n", address, address + offset, offset);
	if (option != 0)
		print_dump((void *)address, offset);
	return (offset);
}

size_t		print_allocation(t_metabody *body, size_t max, int option)
{
	size_t		i;
	size_t		ret;
	size_t		offset;
	uintptr_t	address;

	i = 0;
	ret = 0;
	while (i < max)
	{
		if (((body->free)[i / 8] & (1 << (i % 8))) != 0)
		{
			offset = metablock_get_size(body, i);
			address = (uintptr_t)(body->address) + i * body->id;
			ft_printf("%#p - %#p : %zu bytes\n", (void *)address, address + offset,
				offset);
			if (option != 0)
				print_dump((void *)address, offset);
			ret += offset;
		}
		i++;
	}
	return (ret);
}

void		print_zone(t_metabody *body)
{
	uint16_t	flag;

	flag = get_flag(body->id);
	if ((get_env() & ENV_ZONE) == 0)
	{
		if (flag <= TINY)
			ft_printf("TINY : %#p\n", (uintptr_t)(body->address));
		else if (flag <= SMALL)
			ft_printf("SMALL : %#p\n", (uintptr_t)(body->address));
		else
			ft_printf("LARGE : %#p\n", (uintptr_t)(body->address));
	}
	else
	{
		if (flag != ZLARGE)
			ft_printf("Zone [ %d ] : %#p\n", body->id,
				(uintptr_t)(body->address));
		else
			ft_printf("LARGE : %#p\n", (uintptr_t)(body->address));
	}
}

size_t		print_metadata(t_metahead *head, int option)
{
	t_metabody	*body;
	size_t		total;
	size_t		i;

	i = 0;
	total = 0;
	while (i < AVAILABLE)
	{
		body = (t_metabody *)&((((t_metadata *)(head->container))->body)[i]);
		if (body->id != 0)
		{
			print_zone(body);
			if (body->id == ZLARGE)
				total += print_large(body, option);
			else if (body->id == Z4)
				total += print_allocation(body, 256, option);
			else
				total += print_allocation(body, 128, option);

		}
		i++;
	}
	return (total);
}
