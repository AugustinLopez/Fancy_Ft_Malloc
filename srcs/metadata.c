/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:11:22 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 19:34:32 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <sys/mman.h>
#include "minilibft.h"

t_metahead			*metadata_find(const t_metadata *start,
									const uint16_t flag,
									size_t *index)
{
	t_metahead	*iter;
	size_t		i;

	if (start == NULL || flag == ZLARGE)
		return (NULL);
	iter = (t_metahead *)&(start->head);
	while (iter)
	{
		if (iter->available_heap)
		{
			i = 0;
			while (i < AVAILABLE)
			{
				if ((iter->id)[i] == flag && ((iter->full) & (1 << i)) == 0)
				{
					*index = i;
					return (iter);
				}
				++i;
			}
		}
		iter = iter->next;
	}
	return (NULL);
}

static void			guard_free(t_metahead *head)
{
	if (head->r_protect != NULL
	&& (munmap(head->r_protect, getpagesize())) == -1)
		log_free_failed(head->r_protect, ERR_FREE_MUNMAP);
	if (head->l_protect != NULL
	&& (munmap(head->l_protect, getpagesize())) == -1)
		log_free_failed(head->l_protect, ERR_FREE_MUNMAP);
}

int					metadata_free(t_metahead *head, t_metadata *start)
{
	void	*ptr;
	int		ret;
	void	*l;
	void	*r;

	ret = 0;
	if (head->available_heap == AVAILABLE && head->container != (void *)start)
	{
		ptr = head->container;
		l = head->l_protect;
		r = head->r_protect;
		if (head->next)
			head->next->prev = head->prev;
		if (head->prev)
			head->prev->next = head->next;
		if ((get_env() & ENV_GUARD) != 0)
			guard_free(head);
		ret = munmap(ptr, getpagesize());
		if (ret == -1)
			log_free_failed(ptr, ERR_FREE_MUNMAP);
		else
			log_metadata_free((t_metadata *)ptr, l, r);
		return (1);
	}
	return (ret);
}

/*
** Create a metadata page of the requested type.
** If any error occur, return NULL.
*/

static t_metadata	*metadata_set(void)
{
	t_metadata		*elem;
	t_metahead		*head;
	void			*temp;

	temp = NULL;
	if ((get_env() & ENV_GUARD) != 0)
		temp = mmap_malloc(getpagesize(), 1);
	if ((elem = (t_metadata *)mmap_malloc(getpagesize(), 0)) == NULL)
		return (NULL);
	head = &((elem->head).data);
	head->container = elem;
	head->available_heap = AVAILABLE;
	if ((get_env() & ENV_GUARD) != 0)
	{
		head->l_protect = temp;
		head->r_protect = mmap_malloc(getpagesize(), 1);
		log_metadata_set(elem, head->l_protect, head->r_protect);
	}
	else
		log_metadata_set(elem, 0, 0);
	return (elem);
}

t_metadata			*metadata_add(t_metadata **start)
{
	t_metadata	*data;
	t_metahead	*head;

	if (!(data = metadata_set()))
		return (NULL);
	if (!*start)
	{
		*start = data;
		return (*start);
	}
	head = &(((*start)->head).data);
	while (head)
	{
		if (head->next == NULL)
			break ;
		head = head->next;
	}
	head->next = (t_metahead *)&(data->head);
	head->next->prev = head;
	return (data);
}
