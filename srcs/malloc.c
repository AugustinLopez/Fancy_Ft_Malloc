/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:51:21 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/11 00:53:43 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>
#include "minilibft.h"

void	*mono_malloc(size_t size)
{
	void		*ret;
	t_metabody	*body;
	//static size_t	j = 0;

	if (size == 0)
		return (NULL);
	body = metabody_get(size);
	if (body == NULL)
		return (NULL);
	ret = ptr_get(body, size);
	ft_printf("%p\n", ret);
	if (ret == NULL)
		return (NULL);
	//ft_printf("%3zu. %p %p\n", j++, (void *)body, ret);
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
