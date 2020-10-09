/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:11:22 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/09 21:39:04 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <sys/resource.h>

/*
** Return the number of block in a metabody associated to a given memory size.
*/

uint16_t	get_block(const size_t size)
{
	if (size == 0)
		return (0);
	if (size <= 16)
		return (256);
	if (size <= 2048)
		return (128);
	return(1);
}

/*
** Return the flag of a metaboby associated to a given memory size.
*/

uint16_t	get_flag(const size_t size)
{
	if (size == 0)
		return (0);
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
	return(Z12);
}

/*
** Return the amount of memory to be reserved for allocation associated to
** a given memory size.
*/

size_t		get_page(const size_t size)
{
	size_t	i;

	i = getpagesize();
	if (size <= Z4)
		i *= 1;
	else if (size <= Z5)
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
	else
		i = size;
	return(i);
}

/*
** Return 0 if system ressource consumption would still be under limit
** after a memory allocation.
*/

int			get_rlimit(const size_t size)
{
	struct rlimit	limit;

	if (getrlimit(RLIMIT_AS, &limit) != 0)
		return (1);
	if (size > limit.rlim_cur)
		return (1);
	return (0);
}