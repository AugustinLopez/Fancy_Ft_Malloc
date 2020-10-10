/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:25:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/02/06 12:27:16 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strchri(const char *s, int c)
{
	size_t	n;

	n = 2;
	if (!c)
		return (0);
	if ((unsigned char)*s == (unsigned char)c)
		return (1);
	while (*(s++))
	{
		if ((unsigned char)*s == (unsigned char)c)
			return (n);
		n++;
	}
	return (0);
}
