/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:11:22 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 18:52:29 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/resource.h>
#include <sys/mman.h>
#include <sys/resource.h>

void		*mmap_malloc(const size_t requested, int bonus)
{
	void			*ret;
	struct rlimit	limit;

	if (getrlimit(RLIMIT_AS, &limit) != 0)
	{
		log_mmap_failed(0, ERR_RLIMIT);
		return (NULL);
	}
	if (requested > limit.rlim_cur)
	{
		log_mmap_failed(requested, ERR_TOO_LARGE);
		return (NULL);
	}
	if (bonus == 0)
		ret = mmap(NULL, requested, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	else
		ret = mmap(NULL, requested, PROT_NONE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ret == MAP_FAILED)
	{
		log_mmap_failed(0, ERR_MMAP);
		return (NULL);
	}
	return (ret);
}
