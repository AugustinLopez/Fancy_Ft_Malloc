/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 01:29:30 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 15:12:35 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"
#include "malloc.h"

int			log_metadata_set(t_metadata *data)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "\n>>> New metadata: [%p]\n\n", (void *)data);
	return (0);
}

int			log_metabody_set(t_metabody *body, t_metahead *head)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "[%p] New metabody: %p -> %p (%zu left)\n", head->container,
		(void *)body, (void *)body->address, head->available_heap);
	return (0);
}

int			log_malloc(t_metabody *body, void *ptr, size_t size)
{
	int fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "Malloc %4zu: %p (N-%zu)\n", size, ptr, body->block_count);
	return (0);
}

int			log_free(void *ptr, size_t count)
{
	int fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "Free:        %p (N-%zu)\n", ptr, count);
	return (0);
}

int			log_metabody_free(t_metabody *body, void *ptr, t_metahead *head)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "[%p] Freed metabody: %p -> %p (%zu left)\n",
		head->container, (void *)body, ptr, head->available_heap);
	return (0);
}

int			log_metadata_free(t_metadata *data)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "\n>>> Freed metadata: [%p]\n\n", (void *)data);
	return (0);
}

int			log_free_failed(void *ptr, t_error error)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	if (error == ERR_FREE_INVALID)
		ft_dprintf(fd, "! - Cannot free %p: invalid pointer\n", ptr);
	else if (error == ERR_FREE_DOUBLE)
		ft_dprintf(fd, "! - Cannot free %p: double-free\n", ptr);
	else if (error == ERR_FREE_MUNMAP)
		ft_dprintf(fd, "!!! -  Invalid munmap on %p\n", ptr);
	return (0);
}

int			log_debug(int i, char *str, void *ptr)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	ft_dprintf(fd, "%d - %s - %p\n",i , str, ptr);
	return (0);
}
