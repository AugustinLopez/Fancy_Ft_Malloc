/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_bigint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 12:20:20 by aulopez           #+#    #+#             */
/*   Updated: 2019/02/06 15:53:47 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_bigint.h"

char		*infnan(uint64_t sign, uint64_t mantissa)
{
	char		*str;

	if (mantissa >> 63 != 0)
		mantissa = 0;
	if (!(str = ft_strnew(4)))
		return (0);
	if (sign && !mantissa)
		ft_strcat(str, "-inf");
	else if (!mantissa)
		ft_strcat(str, "inf");
	else
		ft_strcat(str, "nan");
	return (str);
}

char		*exp_pos(uint32_t flags, int exp, uint64_t mantissa, int dbl_t)
{
	char	*str;
	char	*tmp;
	int		*unit;
	int		*stack;

	if ((dbl_t == LDBL_TAB && create_lstack_pos(&unit, &stack, exp, mantissa))
		|| (dbl_t == DBL_TAB && create_stack_pos(&unit, &stack, exp, mantissa)))
		return (0);
	free(unit);
	if (!(str = ft_strnew((stack[0] + 1) * 12 + 2)))
		return (free_and_return_char(stack, 0));
	tmp = str;
	ft_putnbr_pos(&stack, &tmp, dbl_t, flags);
	return (free_and_return_char(stack, str));
}

char		*exp_neg(uint64_t sign, int exp, uint64_t mantissa, int dbl_t)
{
	char	*str;
	char	*tmp;
	int		*unit;
	int		*stack;
	int		i;

	if ((dbl_t == LDBL_TAB && create_lstack_neg(&unit, &stack, exp, mantissa))
		|| (dbl_t == DBL_TAB && create_stack_neg(&unit, &stack, exp, mantissa)))
		return (0);
	free(unit);
	if (!(str = ft_strnew(((stack[0] + 1) * 9 + 3))))
		return (free_and_return_char(stack, 0));
	tmp = str;
	i = 0;
	if (sign)
		str[i++] = '-';
	ft_strcat(str + i, "0.");
	tmp = str + i + 2;
	i = 2;
	while (i < stack[0])
		ft_putnbr_neg(stack[i++], 0, &tmp);
	ft_putnbr_neg(stack[i], 1, &tmp);
	tmp[0] = 0;
	return (free_and_return_char(stack, str));
}

char		*ft_dbltoa(double x, size_t precision, uint32_t flags)
{
	uint64_t	sign;
	int			exposent;
	uint64_t	mantissa;
	char		*str;

	ft_memcpy(&mantissa, &x, sizeof(uint64_t));
	exposent = ((mantissa << 1) >> 53) - EXP_MAX;
	sign = (mantissa >> 63);
	mantissa = ((mantissa << 12) >> 12);
	if (exposent >= EXP_MAX + 1)
		str = infnan(sign, mantissa);
	else if (exposent >= 0)
		str = exp_pos(flags, exposent, mantissa, DBL_TAB);
	else
		str = exp_neg(sign, exposent, mantissa, DBL_TAB);
	if (!str || exposent >= EXP_MAX + 1)
		return (str);
	handle_precision(&str, precision, flags);
	return (str);
}

char		*ft_ldbltoa(long double x, size_t precision, uint32_t flags)
{
	uint64_t	sign;
	int			exposent;
	uint64_t	mantissa;
	char		*str;
	uint64_t	test[2];

	ft_memcpy(&test, &x, sizeof(uint64_t) * 2);
	exposent = (test[1] & 32767) - EXP2_MAX;
	sign = !(!(test[1] & 32768));
	mantissa = test[0];
	if ((!(mantissa >> 63) && exposent != -EXP2_MAX))
	{
		mantissa = 1;
		exposent = EXP2_MAX + 1;
	}
	if (exposent >= EXP2_MAX + 1)
		str = infnan(sign, mantissa);
	else if (exposent >= 0)
		str = exp_pos(flags, exposent, mantissa, LDBL_TAB);
	else
		str = exp_neg(sign, exposent, mantissa, LDBL_TAB);
	if (!str || exposent >= EXP2_MAX + 1)
		return (str);
	handle_precision(&str, precision, flags);
	return (str);
}
