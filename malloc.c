/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:51:21 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/09 18:04:44 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>

void	*mono_malloc(size_t size)
{
	void		*ret;
	t_metadata	*metadata;
	t_metabody	*body;

	if (size == 0)
		return (NULL);
	metadata = metadata_get(size);
	if (metadata == NULL)
		return (NULL);
	body = metabody_get(metadata, size);
	if (body == NULL)
		return (NULL);
	ret = ptr_get(body);
	return (ret);
}

void	*malloc(size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_thread_mutex);
	ret = mono_malloc(size);
	pthread_mutex_unlock(&g_thread_mutex);
	return (ret);
}