/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 19:10:56 by aulopez           #+#    #+#             */
/*   Updated: 2019/02/07 11:38:26 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static inline int	pf_get_base(t_printf *pf, char c)
{
	if (ft_strchr("ouxXbOUB", c))
	{
		if (c == 'o' || c == 'O')
			pf->base = 8;
		else if (c == 'u' || c == 'U')
			pf->base = 10;
		else if (c == 'x' || c == 'X')
			pf->base = 16;
		else
			pf->base = 2;
		return (1);
	}
	return (0);
}

static inline void	pf_parse_conversion(t_printf *pf)
{
	char	c;

	c = (char)pf->flag;
	pf->flag |= c < 97 && c != 'X' ? F_1LONG | F_2LONG : 0;
	if (!c)
		pf->format--;
	else if (c == 's' || c == 'S')
		(pf->flag & (F_1LONG | F_2LONG)) ? pf_putwstr(pf) : pf_putstr(pf);
	else if (c == 'c' || c == 'C')
		(pf->flag & (F_1LONG | F_2LONG)) ? pf_putwchar(pf) : pf_putchar(pf);
	else if (c == 'D' || c == 'I' || c == 'd' || c == 'i')
		pf_putnbr(pf);
	else if (pf_get_base(pf, c))
		pf_putnbr_base(pf);
	else if (c == 'p' || c == 'P')
		pf_putpointer(pf);
	else if (c == 'n' || c == 'N')
		pf_getlen(pf);
	else if (c == 'F' || c == 'f')
		pf_putdouble(pf);
	else if (c)
		pf_putvoid(pf);
}

static inline void	pf_parse_flag(t_printf *pf)
{
	int	i;

	while ((i = ft_strchri("-+0 #'*", (pf->format)[0])) && (++pf->format))
		pf->flag |= (1 << (21 + i));
	if (pf->flag & F_WILDCARD)
	{
		pf->flag &= ~F_WILDCARD;
		i = (int)va_arg(pf->ap, int);
		if (pf->flag & F_DOT)
			pf->precision = i;
		else
			pf->length = i;
	}
}

static inline void	pf_parse_length_precision(t_printf *pf)
{
	if ('0' < *pf->format && *pf->format < ':')
		pf->length = pf_parse_atoi(&pf->format);
	if (*pf->format == '.' && (pf->flag |= F_DOT) && pf->format++)
		pf->precision = pf_parse_atoi(&pf->format);
	pf_parse_flag(pf);
	while (1)
	{
		if (*pf->format == 'h')
			pf->flag |= (pf->format[1] == 'h'
				&& ++pf->format) ? F_2SHORT : F_1SHORT;
		else if (*pf->format == 'l')
			pf->flag |= (pf->format[1] == 'l'
				&& ++pf->format) ? F_2LONG : F_1LONG;
		else if (*pf->format == 'j')
			pf->flag |= F_INTMAX;
		else if (*pf->format == 'z')
			pf->flag |= F_SIZE_T;
		else if (*pf->format == 'L')
			pf->flag |= F_LDBL;
		else
			break ;
		++pf->format;
	}
}

void				pf_parse(t_printf *pf)
{
	int	i;

	pf->flag = 0;
	pf->length = 0;
	pf->precision = 0;
	pf_parse_flag(pf);
	pf_parse_length_precision(pf);
	i = pf->precision;
	pf->precision = (i >= 0) ? i : 0;
	pf->flag &= (i >= 0) ? pf->flag : ~F_DOT;
	i = pf->length;
	pf->length = (i >= 0) ? i : 0;
	(pf->flag & (F_MINUS | F_QUOTE)) ? pf->flag &= ~F_ZERO : 0;
	(pf->flag & F_PLUS) ? pf->flag &= ~F_SPACE : 0;
	pf->flag |= (pf->format)[0];
	pf_parse_conversion(pf);
}
