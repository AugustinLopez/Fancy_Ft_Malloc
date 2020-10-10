/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 19:11:45 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/18 10:39:33 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
** The following tables shows how to decompose an unsigned into a wchar :
** -----------------------------------------------------------------------------
** 000000 --  00007F : 0xxxxxxx
** 000080 --  0007FF : 110xxxxx 10xxxxxx
** 000800 --  00FFFF : 1110xxxx 10xxxxxx 10xxxxxx
** 010000 --  1FFFFF : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
**
**      0 --     127 : 0aaaaaaa
**    128 --    2047 : 00000aaa aabbbbbb
**   2048 --   65535 : aaaabbbb bbcccccc
**  65536 -- 2097151 : 000aaabb bbbbcccc ccdddddd
** -----------------------------------------------------------------------------
** MB_CUR_MAX = Max number of byte to represent a wide character.
** It is possible that MB_CUR_MAX = 1, meaning no wide character.
*/

static inline void	pf_lenwchar(t_printf *pf, unsigned int wc,
								unsigned int wlen, unsigned int nb_bytes)
{
	char	tmp[4];

	if (nb_bytes <= wlen)
	{
		if (nb_bytes == 1)
			tmp[0] = wc;
		else
		{
			if (nb_bytes == 2)
				tmp[0] = ((wc & (0x1F << 6)) >> 6) | 0xC0;
			else
			{
				if (nb_bytes == 3)
					tmp[0] = ((wc >> 12) & 0xF) | 0xE0;
				else if (nb_bytes == 4)
				{
					tmp[0] = ((wc >> 18) & 7) | 0xF0;
					tmp[1] = ((wc >> 12) & 0x3F) | 0x80;
				}
				tmp[nb_bytes - 2] = ((wc >> 6) & 0x3F) | 0x80;
			}
			tmp[nb_bytes - 1] = (wc & 0x3F) | 0x80;
		}
		pf_buffer_write(pf, tmp, nb_bytes);
	}
}

static inline void	pf_putnull(t_printf *pf)
{
	pf->printed = 6;
	(pf->flag & F_DOT && pf->precision < 6) ? pf->printed = pf->precision : 0;
	pf->padding = pf->length - pf->printed;
	pf_padding(pf, 0);
	if (!(pf->flag & F_ZERO))
		pf_buffer_write(pf, "(null)", pf->printed);
	pf_padding(pf, 1);
}

void				pf_putwstr(t_printf *pf)
{
	wchar_t	*str;
	int		clen;

	if (!(str = va_arg(pf->ap, wchar_t *)))
	{
		pf_putnull(pf);
		return ;
	}
	pf->printed = (int)(ft_wstrlen((unsigned *)str));
	if (pf->flag & F_DOT)
		pf->printed = pf->printed > pf->precision ? pf->precision : pf->printed;
	pf->printed = pf->printed < 0 ? 0 : pf->printed;
	if ((pf->padding = (pf->length - pf->printed)) < 0)
		pf->padding = 0;
	pf->flag &= (pf->length > pf->precision) ? ~F_DOT : pf->flag | F_DOT;
	pf_padding(pf, 0);
	clen = 0;
	while ((*str && (pf->printed -= clen) > 0))
	{
		clen = ft_wcharlen(*str);
		pf_lenwchar(pf, *str++, pf->printed, clen);
	}
	pf_padding(pf, 1);
}

void				pf_putwchar(t_printf *pf)
{
	unsigned	c;

	c = va_arg(pf->ap, unsigned);
	pf->printed = ft_wcharlen(c);
	pf->padding = pf->length - pf->printed;
	pf_padding(pf, 0);
	pf_lenwchar(pf, c, pf->printed, pf->printed);
	pf_padding(pf, 1);
}

void				pf_putstr(t_printf *pf)
{
	char	*str;

	if (!(str = va_arg(pf->ap, char *)))
	{
		pf_putnull(pf);
		return ;
	}
	pf->printed = (int)(ft_strlen(str));
	if (pf->flag & F_DOT && pf->printed > pf->precision)
		pf->printed = pf->precision;
	pf->padding = pf->length - pf->printed;
	pf_padding(pf, 0);
	pf_buffer_write(pf, str, pf->printed);
	pf_padding(pf, 1);
}
