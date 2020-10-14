/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 11:29:59 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 17:58:59 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "minilibft.h"
#include <pthread.h>
#include <stddef.h>

static void	mono_show_alloc_mem(int option)
{
	t_metahead	*iter;
	size_t		total;

	if (g_metadata == NULL)
		return ;
	total = 0;
	iter = (t_metahead *)&(g_metadata->head);
	while (iter)
	{
		total += print_metadata(iter, option);
		iter = iter->next;
	}
	ft_printf("Total: %zu bytes\n", total);
}

void		show_alloc_mem_ex(void)
{
	pthread_mutex_lock(&g_thread_mutex);
	mono_show_alloc_mem(1);
	pthread_mutex_unlock(&g_thread_mutex);
}

void		show_alloc_mem(void)
{
	pthread_mutex_lock(&g_thread_mutex);
	mono_show_alloc_mem(0);
	pthread_mutex_unlock(&g_thread_mutex);
}
