/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_number_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 19:11:32 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/18 10:48:43 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void				pf_itoa_quote(uintmax_t n, int b, char s[70], t_printf *pf)
{
	int		quote;
	int		len;
	int		c;

	c = (char)pf->flag;
	len = pf->printed;
	if (len < 4)
		quote = -3;
	else
		quote = 0;
	c = (c == 'P' || c == 'X') ? 55 : 87;
	while (len--)
	{
		s[len] = n % b;
		s[len] += (s[len] < 10) ? '0' : c;
		if (len && ++quote == 3)
		{
			s[--len] = ',';
			quote = 0;
		}
		n /= b;
	}
}

int					pf_sign(t_printf *pf)
{
	if (pf->flag & F_NEGATIF)
		pf_buffer_write(pf, "-", 1);
	else if (pf->flag & F_PLUS)
		pf_buffer_write(pf, "+", 1);
	else
		pf_buffer_write(pf, " ", 1);
	return (0);
}

void				pf_itoa_fill(uintmax_t n, int b, char s[70], t_printf *pf)
{
	int		len;
	int		c;

	if (!(pf->flag & F_QUOTE))
	{
		c = (char)pf->flag;
		len = pf->printed;
		c = (c == 'P' || c == 'X') ? 55 : 87;
		while (len--)
		{
			s[len] = n % b;
			s[len] += (s[len] < 10) ? '0' : c;
			n /= b;
		}
	}
	else
		pf_itoa_quote(n, b, s, pf);
}
