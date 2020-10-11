/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:51:21 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/11 02:16:06 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>
#include "minilibft.h"

void	*mono_malloc(size_t size)
{
	void		*ret;
	t_metabody	*body;
	static size_t	j = 0;

	(void)j;
	if (size == 0)
		return (NULL);
	body = metabody_get(size);
	if (body == NULL)
		return (NULL);
	ret = ptr_get(body, size);
	if (ret == NULL)
		return (NULL);
	log_malloc(body, ret, size);
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
