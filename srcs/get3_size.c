/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get3_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:11:22 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 18:17:42 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Return the size of a given zone of memory.
*/

size_t	get_body_size(t_metabody *body)
{
	if (body->id == ZLARGE)
		return (*((size_t *)(body->store)));
	else if (body->id == Z4)
		return (body->id * 256);
	else
		return (body->id * 128);
}
