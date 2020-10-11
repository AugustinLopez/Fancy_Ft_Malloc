/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 01:29:30 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/12 00:13:59 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"
#include "malloc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	fd_get()
{
	static int fd = -2;

	if (fd == -2)
		fd = open("log_malloc.txt", O_CREAT | O_RDWR | O_TRUNC);
	return (fd);
}

int	log_metadata_set(t_metadata *data)
{
	int	fd;

	fd = fd_get();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "\n>>> New metadata: [%p]\n\n", (void *)data);
	return (0);
}


int	log_metabody_set(t_metabody *body, t_metahead *head)
{
	int	fd;

	fd = fd_get();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "[%p] New metabody: %p -> %p (%zu left)\n", head->container,
		(void *)body, (void *)body->address, head->available_heap);
	return (0);
}

int	log_malloc(t_metabody *body, void *ptr, size_t size)
{
	int fd;

	fd = fd_get();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "Malloc %4zu: %p (N-%zu)\n", size, ptr, body->block_count);
	return (0);
}

int	log_free(t_metabody *body, void *ptr)
{
	int fd;

	fd = fd_get();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "Free:        %p (N-%zu)\n", ptr, body->block_count);
	return (0);
}
