/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_string_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 19:11:45 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/22 10:40:31 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

inline static int	pf_char_padding(t_printf *pf, char c)
{
	if (pf->padding > 0)
		if (!(pf->flag & F_MINUS))
			while (pf->padding--)
				pf_buffer_write(pf, &c, 1);
	return (0);
}

void				pf_putchar(t_printf *pf)
{
	unsigned	c;

	c = va_arg(pf->ap, unsigned);
	pf->printed = 1;
	pf->padding = pf->length - 1;
	(pf->flag & F_SHARP) ? pf_char_padding(pf, c) : pf_padding(pf, 0);
	pf_buffer_write(pf, &c, 1);
	pf_padding(pf, 1);
}
