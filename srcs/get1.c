/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:11:22 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 17:39:34 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>

/*
** Return the number of address in a metabody associated to a given memory size.
*/

uint16_t		get_block(const size_t size)
{
	if (size == 0)
		return (0);
	if (size <= Z4)
		return (256);
	if (size <= Z11)
		return (128);
	return (1);
}

/*
** Return the flag of a metaboby associated to a given memory size.
*/

static uint16_t	get_flag_no_bonus(const size_t size)
{
	if (size <= TINY)
		return (TINY);
	if (size <= SMALL)
		return (SMALL);
	return (ZLARGE);
}

uint16_t		get_flag(const size_t size)
{
	if (size == 0)
		return (0);
	if ((get_env() & ENV_ZONE) == 0)
		return (get_flag_no_bonus(size));
	if (size <= Z4)
		return (Z4);
	if (size <= Z5)
		return (Z5);
	if (size <= Z6)
		return (Z6);
	if (size <= Z7)
		return (Z7);
	if (size <= Z8)
		return (Z8);
	if (size <= Z9)
		return (Z9);
	if (size <= Z10)
		return (Z10);
	if (size <= Z11)
		return (Z11);
	if (size <= Z12)
		return (Z12);
	return (ZLARGE);
}

/*
** Return the amount of memory to be reserved for allocation associated to
** a given memory size.
*/

static size_t	get_page_no_bonus(const size_t size)
{
	size_t	i;

	i = getpagesize();
	if (size <= TINY && TINY == Z4)
		i *= 1;
	else if (size <= TINY)
		i *= TINY / 32;
	else if (size <= SMALL && SMALL == Z4)
		i *= 1;
	else if (size <= SMALL)
		i *= SMALL / 32;
	else if (size % i)
		i *= (size / i) + 1;
	else
		i *= (size / i);
	return (i);
}

size_t			get_page(const size_t size)
{
	size_t	i;

	if ((get_env() & ENV_ZONE) == 0)
		return (get_page_no_bonus(size));
	i = getpagesize();
	if (size <= Z5)
		i *= 1;
	else if (size <= Z6)
		i *= 2;
	else if (size <= Z7)
		i *= 4;
	else if (size <= Z8)
		i *= 8;
	else if (size <= Z9)
		i *= 16;
	else if (size <= Z10)
		i *= 32;
	else if (size <= Z11)
		i *= 64;
	else if (size <= Z12)
		i *= 128;
	else if (size % i)
		i *= (size / i) + 1;
	else
		i *= (size / i);
	return (i);
}
