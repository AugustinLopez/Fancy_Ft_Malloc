/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:56:45 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/06 09:19:12 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>

/*
** Basic implementation
*/

/*
**void	*ft_memset(void *s, int c, size_t n)
**{
**	unsigned char	*pc;
**
**	pc = (unsigned char *)s;
**	while (n--)
**		*pc++ = (unsigned char)c;
**	return (s);
**}
*/

static inline uint64_t	set_byte(unsigned char c)
{
	uint64_t	c_each_byte;

	c_each_byte = c & 0xff;
	c_each_byte = (c_each_byte << 8) | c_each_byte;
	c_each_byte = (c_each_byte << 16) | c_each_byte;
	c_each_byte = (c_each_byte << 32) | c_each_byte;
	return (c_each_byte);
}

void					*ft_memset(void *s, int c, size_t n)
{
	uint64_t		c_each_byte;
	uint64_t		*pll;
	unsigned char	*pc;

	pc = (unsigned char *)s;
	if (n >= 8)
	{
		while (((uintptr_t)pc & 0x7))
		{
			*pc++ = (unsigned char)c;
			--n;
		}
		c_each_byte = set_byte((unsigned char)c);
		pll = (uint64_t *)pc;
		while (n >= 8)
		{
			*pll++ = c_each_byte;
			n -= 8;
		}
		pc = (unsigned char *)pll;
	}
	while (n--)
		*pc++ = (unsigned char)c;
	return (s);
}
