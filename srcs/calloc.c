/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:51:21 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/31 11:07:22 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>
#include <unistd.h>
#include "minilibft.h"

void		*mono_calloc(size_t count, size_t size)
{
	void		*ret;
	size_t		res;

	res = count * size;
	if (res < count || res < size)
		return (NULL);
	ret = mono_malloc(res);
	if (ret)
		ret = ft_memset(ret, 0, res);
	return (ret);
}

void		*calloc(size_t count, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_thread_mutex);
	ret = mono_calloc(count, size);
	pthread_mutex_unlock(&g_thread_mutex);
	return (ret);
}
