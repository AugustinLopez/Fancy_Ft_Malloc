/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 19:08:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/02/06 11:26:31 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int					pf_parse_atoi(char **str)
{
	long	i;

	i = 0;
	while (**str >= '0' && **str <= '9')
	{
		if (i > 2147483647)
		{
			i = 2147483648;
			(*str)++;
		}
		else
			i = i * 10 + *(*str)++ - '0';
	}
	if (i == 2147483648)
		return (-1);
	return ((int)i);
}

void				pf_putvoid(t_printf *pf)
{
	pf->padding = pf->length - 1;
	if (pf->padding > 0)
	{
		pf_padding(pf, 0);
		pf_buffer_write(pf, pf->format, 1);
		pf_padding(pf, 1);
	}
	else
		pf_buffer_write(pf, pf->format, 1);
}

void				pf_putpointer(t_printf *pf)
{
	void	*pv;

	pv = va_arg(pf->ap, void *);
	pf->flag |= F_SHARP;
	pf->flag &= ~F_QUOTE;
	pf->printed = 1;
	pf->length -= 2;
	pf_itoa_base((uintmax_t)pv, 16, pf);
}

void				pf_getlen(t_printf *pf)
{
	int			*pi;
	intmax_t	*pm;
	size_t		*pz;

	if (!(pf->flag & (F_INTMAX | F_SIZE_T)))
	{
		pi = va_arg(pf->ap, int *);
		*pi = (pf->len);
	}
	else if (pf->flag & F_INTMAX)
	{
		pm = va_arg(pf->ap, intmax_t *);
		*pm = (pf->len);
	}
	else if (pf->flag & F_SIZE_T)
	{
		pz = va_arg(pf->ap, size_t *);
		*pz = (pf->len);
	}
}
