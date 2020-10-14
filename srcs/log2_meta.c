/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log2_meta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 01:29:30 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 19:07:33 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"
#include "malloc.h"

int			log_metadata_set(t_metadata *data, void *l, void *r)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	if (l != NULL && r != NULL)
		ft_dprintf(fd, "\n>>> New metadata: (%p| [%p] |%p)\n\n",
			l, (void *)data, r);
	else if (l != NULL)
		ft_dprintf(fd, "\n>>> New metadata: (%p| [%p]\n\n", l, (void *)data);
	else if (r != NULL)
		ft_dprintf(fd, "\n>>> New metadata: [%p] |%p)\n\n", (void *)data, r);
	else
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

int			log_metadata_free(t_metadata *data, void *l, void *r)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	if (l != NULL && r != NULL)
		ft_dprintf(fd, "\n>>> Freed metadata: (%p| [%p] |%p)\n\n",
			l, (void *)data, r);
	else if (l != NULL)
		ft_dprintf(fd, "\n>>> Freed metadata: (%p| [%p]\n\n", l, (void *)data);
	else if (r != NULL)
		ft_dprintf(fd, "\n>>> Freed metadata: [%p] |%p)\n\n", (void *)data, r);
	else
		ft_dprintf(fd, "\n>>> Freed metadata: [%p]\n\n", (void *)data);
	return (0);
}
/*
int			log_metadata_guard(void *r, void *l, int option)
{
	int	fd;

	fd = get_fd();
	if (fd == -1)
		return (1);
	if (option == 0)
		ft_dprintf(fd, "\n>>> Set guard: [%p] [%p]\n\n", r, l);
	if (option == 1)
		ft_dprintf(fd, "\n>>> Freed guard: [%p] [%p]\n\n", r, l);
	return (0);
}*/
