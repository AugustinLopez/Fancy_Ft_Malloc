/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_putnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 12:14:14 by aulopez           #+#    #+#             */
/*   Updated: 2019/02/06 15:21:36 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_bigint.h"

void		ft_putnbr_neg(int n, int end, char **tmp)
{
	size_t			len;
	int				buf;
	char			c;

	buf = n;
	buf = 100000000;
	len = 9;
	if (end)
	{
		while (n % 10 == 0 && n != 0)
		{
			n /= 10;
			buf /= 10;
			len--;
		}
		if (n == 0)
			len = 6 * (len == 9);
	}
	while (len--)
	{
		c = n / buf + '0';
		((*tmp)++)[0] = c;
		n %= buf;
		buf /= 10;
	}
}

void		ft_putnbr_pos_addentum(int **stack, int *i, char **tmp, int dbl_tab)
{
	int				len;
	int				buf;
	char			c;
	int				dot;
	int				n;

	buf = 100000000;
	len = 9;
	dot = 6;
	n = (*stack)[*i];
	while (*i == dbl_tab - (*stack)[0] + 1 && buf > n && len--)
		buf /= 10;
	while (*i == dbl_tab - (*stack)[1] && dot > 0 && n % 10 == 0
			&& (n /= 10) && len-- && dot--)
		buf /= 10;
	while (len--)
	{
		c = n / buf + '0';
		((*tmp)++)[0] = c;
		if (*i == dbl_tab - (*stack)[1] && len == dot)
			((*tmp)++)[0] = '.';
		n %= buf;
		buf /= 10;
	}
	(*i)++;
}

static void	initialize_addentum2(int *buf, int *len, int *dot)
{
	*buf = 100000000;
	*len = 9;
	*dot = 6;
}

void		ft_putnbr_pos_addentum2(int **stack, int *i, char **tmp, int dbl_t)
{
	int				len;
	int				buf;
	char			c;
	int				dot;
	int				n;

	initialize_addentum2(&buf, &len, &dot);
	n = (*stack)[*i];
	while (*i == dbl_t - (*stack)[0] + 1 && buf > n && len--)
		buf /= 10;
	while (*i == dbl_t - (*stack)[1]
			&& dot > 0 && n % 10 == 0 && (n /= 10) && len-- && dot--)
		buf /= 10;
	while (len--)
	{
		c = n / buf + '0';
		((*tmp)++)[0] = c;
		if (*i == dbl_t - (*stack)[1] && len == dot)
			((*tmp)++)[0] = '.';
		else if (*i < dbl_t - (*stack)[1] && (len == 6 || len == 3 || len == 0))
			((*tmp)++)[0] = ',';
		n %= buf;
		buf /= 10;
	}
	(*i)++;
}

void		ft_putnbr_pos(int **stack, char **tmp, int dbl_tab, uint32_t flags)
{
	int		i;
	char	*test;

	test = *tmp;
	i = 6 + (dbl_tab == LDBL_TAB);
	(*stack)[1] = i;
	i = dbl_tab - (*stack)[0] + 1;
	if ((*stack)[i - 1])
	{
		(*stack)[0]++;
		i--;
	}
	if (flags & F_QUOTE)
	{
		while (i <= dbl_tab)
			ft_putnbr_pos_addentum2(stack, &i, &test, dbl_tab);
	}
	else
	{
		while (i <= dbl_tab)
			ft_putnbr_pos_addentum(stack, &i, &test, dbl_tab);
	}
	test[0] = 0;
}
