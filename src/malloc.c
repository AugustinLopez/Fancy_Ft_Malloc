/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:51:21 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/10 14:49:45 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>


#include <stdio.h>

void	*mono_malloc(size_t size)
{
	void		*ret;
	t_metabody	*body;
	static size_t	j = 0;

	if (size == 0)
		return (NULL);
	body = metabody_get(size);
	if (body == NULL)
		return (NULL);
	ret = ptr_get(body, size);
	if (ret == NULL)
		return (NULL);
	//printf("%3zu. %p %p\n", j++, (void *)body, ret);
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

#include <string.h>

int main(void)
{
	size_t	i;
	size_t	j;
	void	*m[500];

	i = 0;
	j = 0;
	while (i < 14)
	{
		m[i++] = mono_malloc(4097);
		memset(m[i - 1], 0xff, 4096 * 2);
	}
	i = 0;
	while (i < 300)
		m[i++] = mono_malloc(16);
/*	while (j < i)
	{
		printf("%3zu. %p\n", j, m[j]);
		j++;
	}*/
	return (0);
}
