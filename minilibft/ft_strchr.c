/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 01:22:00 by aulopez           #+#    #+#             */
/*   Updated: 2019/10/14 17:39:58 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	if ((unsigned char)*s == c)
		return ((char *)s);
	while (*(s++))
		if ((unsigned char)*s == c)
			return ((char *)s);
	return (NULL);
}
/*
**static inline char	*basic_strchr(char *s, int c)
**{
**	if ((unsigned char)*s == c)
**		return (s);
**	while (*(s++))
**		if ((unsigned char)*s == c)
**			return (s);
**	return (NULL);
**}
**
**static inline char	*loopword(char *s, unsigned char c)
**{
**	const uint64_t	*pll;
**	uint64_t		c_each_byte;
**	uint64_t		zero_mask;
**
**	pll = (const uint64_t *)s;
**	c_each_byte = c | (c << 8);
**	c_each_byte |= c_each_byte << 16;
**	c_each_byte |= c_each_byte << 32;
**	while (1)
**	{
**		zero_mask = *pll ^ c_each_byte;
**		if (((zero_mask - ONE_EACH_BYTE) & ~zero_mask) & REV_EACH_BYTE)
**			break ;
**		else if (((*pll - ONE_EACH_BYTE) & ~*pll) & REV_EACH_BYTE)
**			return (NULL);
**		++pll;
**	}
**	s = (char *)pll;
**	return (s);
**}
**
**char				*ft_strchr(const char *s, int c)
**{
**	while ((uintptr_t)s & 0x7)
**	{
**		if ((unsigned char)*s == c)
**			return ((char *)s);
**		if (!*s++)
**			return (NULL);
**	}
**	if (!(s = (const char *)loopword((char *)s, (unsigned char)c)))
**		return (NULL);
**	return (basic_strchr((char *)s, c));
**}
*/
