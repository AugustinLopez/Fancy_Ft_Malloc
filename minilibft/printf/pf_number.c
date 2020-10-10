/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 19:11:32 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/18 10:36:39 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static inline void	finish_printf(uintmax_t n, int b, char s[70], t_printf *pf)
{
	(pf->flag & F_ZERO) ? pf_padding(pf, 0) : 0;
	pf->padding = pf->precision - pf->printed;
	pf->option_padding = 1;
	pf_padding(pf, 0);
	pf->option_padding = 0;
	pf_itoa_fill(n, b, s, pf);
	pf_buffer_write(pf, s, pf->printed);
	pf->padding = pf->length - pf->precision;
	pf_padding(pf, 1);
}

static inline void	pf_itoa(uintmax_t n, t_printf *pf)
{
	char		s[70];
	uintmax_t	tmp;

	tmp = n;
	while ((tmp /= 10))
		pf->printed++;
	if (pf->flag & F_QUOTE)
		pf->printed += pf->printed > 3 ? (pf->printed - 1) / 3 : 0;
	if (!n && (pf->flag & F_DOT) && !(pf->precision))
	{
		pf->padding = pf->length;
		pf_padding(pf, 0);
		(pf->flag & (F_PLUS | F_SPACE | F_NEGATIF)) ? pf_sign(pf) : 0;
		pf_padding(pf, 1);
	}
	else
	{
		(pf->flag & (F_PLUS | F_SPACE | F_NEGATIF)) ? --pf->length : 0;
		pf->precision < pf->printed ? pf->precision = pf->printed : 0;
		pf->padding = pf->length - pf->precision;
		!(pf->flag & F_ZERO) ? pf_padding(pf, 0) : 0;
		(pf->flag & (F_PLUS | F_SPACE | F_NEGATIF)) ? pf_sign(pf) : 0;
		finish_printf(n, 10, s, pf);
	}
}

void				pf_itoa_base(uintmax_t n, int b, t_printf *pf)
{
	char		s[70];
	uintmax_t	tmp;

	tmp = n;
	while ((tmp /= b))
		++pf->printed;
	if (pf->flag & F_QUOTE)
		pf->printed += pf->printed > 3 ? (pf->printed - 1) / 3 : 0;
	(!n && (pf->flag & F_DOT) && !(pf->precision)) ? pf->printed = 0 : 0;
	tmp = (b == 8 && !(pf->printed)) ? 1 : 0;
	(tmp && pf->flag & F_SHARP) ? pf->length-- : 0;
	pf->precision < pf->printed ? pf->precision = pf->printed : 0;
	pf->padding = pf->length - pf->precision;
	!(pf->flag & F_ZERO) ? pf_padding(pf, 0) : 0;
	if ((n || tmp || (char)pf->flag == 'P' || (char)pf->flag == 'p')
	&& (pf->flag & F_SHARP))
	{
		pf_buffer_write(pf, "0", 1);
		if (b == 2)
			pf_buffer_write(pf, (char)pf->flag == 'B' ? "B" : "b", 1);
		else if (b == 16)
			pf_buffer_write(pf, ft_strchr("XP", (char)pf->flag) ? "X" : "x", 1);
	}
	finish_printf(n, b, s, pf);
}

void				pf_putnbr(t_printf *pf)
{
	intmax_t	n;

	if (pf->flag & F_1LONG)
		n = (intmax_t)va_arg(pf->ap, long);
	else if (pf->flag & F_2LONG)
		n = (intmax_t)va_arg(pf->ap, long long);
	else if (pf->flag & F_1SHORT)
		n = (short)va_arg(pf->ap, int);
	else if (pf->flag & F_2SHORT)
		n = (char)va_arg(pf->ap, int);
	else if (pf->flag & F_INTMAX)
		n = (intmax_t)va_arg(pf->ap, intmax_t);
	else if (pf->flag & F_SIZE_T)
		n = (intmax_t)va_arg(pf->ap, ssize_t);
	else
		n = (intmax_t)va_arg(pf->ap, int);
	if (pf->flag & F_DOT)
		pf->flag &= ~F_ZERO;
	if (n < 0 && (pf->flag |= F_NEGATIF))
		n = -n;
	pf->printed = 1;
	pf_itoa((uintmax_t)n, pf);
}

void				pf_putnbr_base(t_printf *pf)
{
	uintmax_t	n;

	if (pf->flag & F_1LONG)
		n = (uintmax_t)va_arg(pf->ap, unsigned long);
	else if (pf->flag & F_2LONG)
		n = (uintmax_t)va_arg(pf->ap, unsigned long long);
	else if (pf->flag & F_1SHORT)
		n = (unsigned short)va_arg(pf->ap, int);
	else if (pf->flag & F_2SHORT)
		n = (unsigned char)va_arg(pf->ap, int);
	else if (pf->flag & F_INTMAX)
		n = (uintmax_t)va_arg(pf->ap, uintmax_t);
	else if (pf->flag & F_SIZE_T)
		n = (uintmax_t)va_arg(pf->ap, size_t);
	else
		n = (uintmax_t)va_arg(pf->ap, unsigned);
	pf->flag &= pf->flag & F_DOT ? ~F_ZERO : pf->flag;
	pf->flag &= (pf->base != 10) ? ~F_QUOTE : ~F_SHARP;
	pf->printed = 1;
	if ((pf->flag & F_SHARP) && n)
	{
		pf->length -= (pf->base == 8) + (pf->base == 2 || pf->base == 16) * 2;
		pf->precision -= (pf->base == 8);
	}
	pf_itoa_base(n, pf->base, pf);
}
