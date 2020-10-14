/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:48:29 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 17:31:46 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>

/*
** 1. Check if the pointer is part of our data
** 2. Attempt to free pointer.
** 3. Attempt to free the body associated to the pointer.
** 4. Attempt to free the metadata associated to the body.
*/

void		mono_free(void *ptr)
{
	t_metabody	*body;
	t_metahead	*head;

	if (ptr == NULL || g_metadata == NULL)
	{
		log_free_failed(ptr, ERR_FREE_INVALID);
		return ;
	}
	body = metabody_find(ptr, g_metadata);
	if (body == NULL)
	{
		log_free_failed(ptr, ERR_FREE_INVALID);
		return ;
	}
	if (metablock_free(body, ptr) == 1)
	{
		log_free_failed(ptr, ERR_FREE_DOUBLE);
		return ;
	}
	head = body->head;
	log_free(ptr, body->block_count);
	metabody_free(body);
	metadata_free(head, g_metadata);
}

void		free(void *ptr)
{
	pthread_mutex_lock(&g_thread_mutex);
	mono_free(ptr);
	pthread_mutex_unlock(&g_thread_mutex);
}
