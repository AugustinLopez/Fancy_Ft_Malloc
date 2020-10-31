/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 21:46:44 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 15:08:25 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "minilibft.h"
#include <stddef.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

static void		*realloc_large(t_metabody *body, size_t size)
{
	size_t	stored;
	void	*ret;

	stored = *((size_t *)&(body->store));
	if (size <= stored && size >= stored - getpagesize())
	{
		body->block_count = size;
		return (body->address);
	}
	ret = mono_malloc(size);
	if (size < stored)
		ret = ft_memcpy(ret, body->address, size);
	else
		ret = ft_memcpy(ret, body->address, stored);
	mono_free(body->address);
	return (ret);
}

static void		*mono_realloc(void *ptr, size_t size)
{
	t_metabody	*body;
	void		*ret;

	if (!ptr)
		return (mono_malloc(size));
	if (!size)
	{
		mono_free(ptr);
		return (NULL);
	}
	body = metabody_find(ptr, g_metadata);
	if (body == NULL)
		return (NULL);
	else if (body->id == ZLARGE)
		return (realloc_large(body, size));
	else if (size > body->id || size <= body->id / 2)
	{
		ret = mono_malloc(size);
		ret = ft_memcpy(ret, ptr, (body->size)[body->index]);
		mono_free(ptr);
		return (ptr);
	}
	(body->size)[body->index] = size;
	return (ptr);
}

void			*realloc(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_thread_mutex);
	ret = mono_realloc(ptr, size);
	pthread_mutex_unlock(&g_thread_mutex);
	return (ret);
}
