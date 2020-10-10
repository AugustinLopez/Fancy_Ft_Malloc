/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:01:38 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/06 12:21:23 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>

/*
** Basic implementation
*/

/*
**void *ft_memccpy(void *s1, const void *s2, int c, size_t n)
**{
**	unsigned char	*cs1;
**	unsigned char	*cs2;
**
**	cs1 = (unsigned char *)s1;
**	cs2 = (unsigned char *)s2;
**	while (n--)
**	{
**		if ((*cs1 = *cs2) == (unsigned char)c)
**			return (cs1 + 1);
**		++cs1;
**		++cs2;
**	}
**	return (NULL);
**}
*/

static inline int	align_address(unsigned char **cs1,
						unsigned char **cs2,
						const unsigned char c, size_t *n)
{
	while ((uintptr_t)*cs1 & 0x7)
	{
		if ((**cs1 = **cs2) == c)
			return (1);
		++(*cs1);
		++(*cs2);
		--(*n);
	}
	return (0);
}

static inline void	loopword(unsigned char **cs1, unsigned char **cs2,
						const unsigned char c, size_t *n)
{
	uint64_t	*lls1;
	uint64_t	*lls2;
	uint64_t	one_each_byte;
	uint64_t	c_each_byte;
	uint64_t	zero_mask;

	lls1 = (uint64_t *)*cs1;
	lls2 = (uint64_t *)*cs2;
	one_each_byte = 0x0101010101010101L;
	c_each_byte = c | (c << 8);
	c_each_byte |= c_each_byte << 16;
	c_each_byte |= c_each_byte << 32;
	while (*n >= 8)
	{
		zero_mask = *lls2 ^ c_each_byte;
		if (((zero_mask - one_each_byte) & ~zero_mask) & (one_each_byte << 7))
			break ;
		*lls1++ = *lls2++;
		*n -= 8;
	}
	*cs1 = (unsigned char *)lls1;
	*cs2 = (unsigned char *)lls2;
}

void				*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	if ((n >= 8) && (((uintptr_t)s1 & 0x7) == ((uintptr_t)s2 & 0x7)))
	{
		if (align_address(&cs1, &cs2, (unsigned char)c, &n))
			return (cs1 + 1);
		loopword(&cs1, &cs2, (const unsigned char)c, &n);
	}
	while (n--)
	{
		if ((*cs1 = *cs2) == (unsigned char)c)
			return (cs1 + 1);
		++cs1;
		++cs2;
	}
	return (NULL);
}
