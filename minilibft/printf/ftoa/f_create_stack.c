/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_create_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 12:17:22 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/23 10:53:15 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_bigint.h"

int				create_stack_pos(int **unit, int **stack, int exposent,
					uint64_t mantissa)
{
	uint64_t	ll;
	int			i;

	if (!(*stack = (int*)malloc(sizeof(int) * (DBL_TAB + 1))))
		return (1);
	if (!(*unit = create_unit_pos(exposent, DBL_TAB)))
		return (free_and_return_int(*stack, 1));
	i = 0;
	while (i < DBL_TAB + 1)
		(*stack)[i++] = 0;
	ll = 1;
	while (ll < MTS_MAX)
	{
		if ((ll & mantissa))
			add_unit_pos(unit, stack);
		multiply_unit_pos(unit);
		ll *= 2;
	}
	add_unit_pos(unit, stack);
	(*stack)[0] = (*unit)[0];
	return (0);
}

int				create_lstack_pos(int **unit, int **stack, int exposent,
					uint64_t mantissa)
{
	uint64_t	ll;
	int			i;

	if (!(*stack = (int*)malloc(sizeof(int) * (LDBL_TAB + 1))))
		return (1);
	if (!(*unit = create_unit_pos(exposent, LDBL_TAB)))
		return (free_and_return_int(*stack, 1));
	i = 0;
	while (i < LDBL_TAB + 1)
		(*stack)[i++] = 0;
	ll = 1;
	while (ll < MTS2_MAX)
	{
		if ((ll & mantissa))
			add_unit_pos(unit, stack);
		multiply_unit_pos(unit);
		ll *= 2;
	}
	add_unit_pos(unit, stack);
	(*stack)[0] = (*unit)[0];
	return (0);
}

int				create_lstack_neg(int **unit, int **stack, int exposent,
					uint64_t mantissa)
{
	uint64_t	ll;
	int			i;

	if (!(*stack = (int*)malloc(sizeof(int) * (LDBL_TAB + 1))))
		return (1);
	if (!(*unit = create_unit_neg(exposent, LDBL_TAB)))
		return (free_and_return_int(*stack, 1));
	i = 0;
	while (i < LDBL_TAB + 1)
		(*stack)[i++] = 0;
	ll = 1;
	if (exposent == -EXP2_MAX)
		multiply_unit_neg(unit);
	while (ll < MTS2_MAX)
	{
		if (ll & mantissa)
			add_unit_neg(unit, stack);
		multiply_unit_neg(unit);
		ll *= 2;
	}
	if (exposent != -EXP2_MAX)
		add_unit_neg(unit, stack);
	while ((*stack)[(*stack)[0]] == 0 && (*stack)[0] != 0)
		(*stack)[0]--;
	return (0);
}

int				create_stack_neg(int **unit, int **stack, int exposent,
					uint64_t mantissa)
{
	uint64_t	ll;
	int			i;

	if (!(*stack = (int*)malloc(sizeof(int) * (DBL_TAB + 1))))
		return (1);
	if (!(*unit = create_unit_neg(exposent, DBL_TAB)))
		return (free_and_return_int(*stack, 1));
	i = 0;
	while (i < DBL_TAB + 1)
		(*stack)[i++] = 0;
	ll = 1;
	if (exposent == -EXP_MAX)
		multiply_unit_neg(unit);
	while (ll < MTS_MAX)
	{
		if (ll & mantissa)
			add_unit_neg(unit, stack);
		multiply_unit_neg(unit);
		ll *= 2;
	}
	if (exposent != -EXP_MAX)
		add_unit_neg(unit, stack);
	while ((*stack)[(*stack)[0]] == 0 && (*stack)[0] != 0)
		(*stack)[0]--;
	return (0);
}
