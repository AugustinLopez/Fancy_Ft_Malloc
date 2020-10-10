/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:29:13 by aulopez           #+#    #+#             */
/*   Updated: 2019/10/14 17:40:11 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s++))
		i++;
	return (i);
}

/*
**size_t					ft_strlen(const char *s)
**{
**	size_t			n;
**	const uint64_t	*pll;
**
**	n = 0;
**	while ((uintptr_t)s & 0x7)
**	{
**		if (!*s++)
**			return (n);
**		++n;
**	}
**	pll = (const uint64_t *)s;
**	while (!(((*pll - ONE_EACH_BYTE) & ~*pll) & REV_EACH_BYTE))
**	{
**		++pll;
**		n += 8;
**	}
**	s = (const char *)pll;
**	while (*s++)
**		++n;
**	return (n);
**}
*/
