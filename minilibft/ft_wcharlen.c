/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 12:55:16 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/10 15:57:44 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

/*
** 000000 -- 00007F : 0xxxxxxx
** 000080 -- 0007FF : 110xxxxx 10xxxxxx
** 000800 -- 00FFFF : 1110xxxx 10xxxxxx 10xxxxxx
** 010000 -- 1FFFFF : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
**
**     0 --     127 : 0aaaaaaa
**   128 --    2047 : 00000aaa aabbbbbb
**  2048 --   65535 : aaaabbbb bbcccccc
** 65536 -- 2097151 : 000aaabb bbbbcccc ccdddddd
*/

size_t	ft_wcharlen(unsigned wc)
{
	if (wc < 0x80)
		return (1);
	if (wc < 0x800)
		return (2);
	if (wc < 0x10000)
		return (3);
	return (4);
}
