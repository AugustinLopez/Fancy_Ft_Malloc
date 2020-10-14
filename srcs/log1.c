/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 01:29:30 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 18:43:21 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"
#include "malloc.h"

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
		ft_dprintf(fd, "!!! - Invalid munmap on %p\n", ptr);
	return (0);
}

int			log_mmap_failed(size_t size, t_error error)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	if (error == ERR_RLIMIT)
		ft_dprintf(fd, "!!! - Cannot allocate: issue with rlimit\n");
	else if (error == ERR_MMAP)
		ft_dprintf(fd, "!!! - Cannot allocate: issue with mmap\n");
	else if (error == ERR_TOO_LARGE)
		ft_dprintf(fd, "! - Cannot allocate: %zu is too large\n", size);
	return (0);

}
