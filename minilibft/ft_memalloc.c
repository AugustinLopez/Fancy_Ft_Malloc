/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:20:58 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/10 15:54:27 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "minilibft.h"

void	*ft_memalloc(size_t size)
{
	void	*p;

	if (!(p = (void *)malloc(size)))
		return (NULL);
	ft_bzero(p, size);
	return (p);
}
