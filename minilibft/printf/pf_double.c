/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 19:08:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/18 10:41:37 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static inline void	pf_load_string(t_printf *pf, char **str)
{
	double		x;
	long double	xx;
	int			dot;

	pf->precision = !(pf->flag & F_DOT) ? 6 : pf->precision;
	if (pf->flag & F_LDBL)
	{
		xx = va_arg(pf->ap, long double);
		*str = ft_ldbltoa((xx < 0 ? -xx : xx), pf->precision, pf->flag);
		pf->flag |= xx < 0 ? F_NEGATIF : 0;
	}
	else
	{
		x = va_arg(pf->ap, double);
		*str = ft_dbltoa((x < 0 ? -x : x), pf->precision, pf->flag);
		pf->flag |= x < 0 ? F_NEGATIF : 0;
	}
	dot = ft_strchri((const char *)(*str), '.');
	pf->printed = dot + ft_strlen(*str + dot);
	pf->precision = dot ? dot + pf->precision : pf->printed;
}

static inline int	minus_edge_case(t_printf *pf, char *str)
{
	if (str[1] != '0')
	{
		pf->flag &= ~(F_NEGATIF | F_PLUS | F_SPACE);
		return (0);
	}
	pf->padding = pf->length - pf->precision;
	pf->flag |= F_NEGATIF;
	!(pf->flag & F_ZERO) ? pf_padding(pf, 0) : 0;
	pf_sign(pf);
	((pf->flag & F_ZERO)) ? pf_padding(pf, 0) : 0;
	pf->padding = pf->precision - pf->printed;
	pf_buffer_write(pf, str + 1, pf->printed - 1);
	pf->option_padding = 1;
	pf_padding(pf, 0);
	pf->option_padding = 0;
	pf->padding = pf->length - pf->precision;
	pf_padding(pf, 1);
	free(str);
	return (1);
}

void				pf_putdouble(t_printf *pf)
{
	char	*str;

	pf_load_string(pf, &str);
	if (str && str[0] == '-' && minus_edge_case(pf, str))
		return ;
	(pf->flag & (F_NEGATIF | F_PLUS | F_SPACE)) ? --pf->length : 0;
	pf->padding = pf->length - pf->precision;
	!(pf->flag & F_ZERO) ? pf_padding(pf, 0) : 0;
	(pf->flag & (F_NEGATIF | F_PLUS | F_SPACE)) ? pf_sign(pf) : 0;
	((pf->flag & F_ZERO)) ? pf_padding(pf, 0) : 0;
	pf->padding = pf->precision - pf->printed;
	str ? pf_buffer_write(pf, str, pf->printed) : 0;
	pf->option_padding = 1;
	str ? pf_padding(pf, 0) : 0;
	pf->option_padding = 0;
	pf->padding = pf->length - pf->precision;
	pf_padding(pf, 1);
	if (str)
		free(str);
}
