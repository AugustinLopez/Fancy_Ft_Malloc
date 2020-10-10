/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:33:47 by aulopez           #+#    #+#             */
/*   Updated: 2019/08/06 12:21:47 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

/*
** Basic implementation
*/

/*
**void	*ft_memmove(void *s1, const void *s2, size_t n)
**{
**	unsigned char		*cs1;
**	const unsigned char	*cs2;
**
**	if (s1 < s2)
**		return (ft_memcpy(s1, s2, n));
**	if (!n || (s1 == s2))
**		return (s1);
**	cs1 = (unsigned char *)s1;
**	cs2 = (const unsigned char *)s2;
**	while (n--)
**		cs1[n] = cs2[n];
**	return (s1);
**}
*/

static inline void	longword(unsigned char **cs1, const unsigned char **cs2,
						size_t *n)
{
	uint64_t		*lls1;
	const uint64_t	*lls2;

	while (((uintptr_t)*cs1 & 0x7))
	{
		*((*cs1)--) = *((*cs2)--);
		--(*n);
	}
	**cs1 = **cs2;
	lls1 = (uint64_t *)*cs1 - 1;
	lls2 = (const uint64_t *)*cs2 - 1;
	while (*n >= 8)
	{
		*lls1-- = *lls2--;
		*n -= 8;
	}
	if (*n)
	{
		*cs1 = (unsigned char *)lls1 - 1;
		*cs2 = (const unsigned char *)lls2 - 1;
	}
}

void				*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char		*cs1;
	const unsigned char	*cs2;

	if (s1 < s2)
		return (ft_memcpy(s1, s2, n));
	else if (!n || (s1 == s2))
		return (s1);
	cs1 = (unsigned char *)s1 + n - 1;
	cs2 = (const unsigned char *)s2 + n - 1;
	if ((n >= 15) && (((uintptr_t)s1 & 0x7) == ((uintptr_t)s2 & 0x7)))
		longword(&cs1, &cs2, &n);
	while (n--)
		*cs1-- = *cs2--;
	return (s1);
}
