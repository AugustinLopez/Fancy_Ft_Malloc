/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_create_unit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 12:09:06 by aulopez           #+#    #+#             */
/*   Updated: 2019/06/06 12:29:13 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_bigint.h"

int				*create_unit_neg_addentum(int dbl_tab)
{
	int	*unit;
	int	j;
	int	i;

	i = dbl_tab;
	if (!(unit = (int*)malloc(sizeof(int) * (i + 2))))
		return (0);
	j = 0;
	while (j < i + 2)
		unit[j++] = 0;
	unit[2] = 500000000;
	unit[0] = 2;
	return (unit);
}

int				*create_unit_neg(int exposent, int dbl_tab)
{
	int	*unit;
	int	j;

	if (!(unit = create_unit_neg_addentum(dbl_tab)))
		return (0);
	if (dbl_tab == DBL_TAB)
		exposent -= MIN_EXP;
	else if (dbl_tab == LDBL_TAB)
		exposent -= MIN2_EXP;
	while (exposent++)
	{
		j = 2;
		while (j <= unit[0])
		{
			if (unit[j] & 1)
				unit[j + 1] += 1000000000;
			unit[j] = unit[j] / 2;
			if (++j == unit[0] + 1 && unit[j] == 1000000000 && unit[0]++)
				unit[j + 1] /= 2;
		}
	}
	return (unit);
}

int				*create_unit_pos_addentum(void)
{
	int	*unit;
	int	j;

	if (!(unit = (int*)malloc(sizeof(int) * (DBL_TAB + 2))))
		return (0);
	j = 0;
	while (j < DBL_TAB + 2)
		unit[j++] = 0;
	unit[0] = 5;
	unit[1] = DBL_TAB;
	unit[DBL_TAB] = 500000000;
	unit[DBL_TAB - 1] = 618164062;
	unit[DBL_TAB - 2] = 84726333;
	unit[DBL_TAB - 3] = 925031308;
	unit[DBL_TAB - 4] = 222044604;
	return (unit);
}

int				*create_lunit_pos_addentum(void)
{
	int	*unit;
	int	j;

	if (!(unit = (int*)malloc(sizeof(int) * (LDBL_TAB + 2))))
		return (0);
	j = 0;
	while (j < LDBL_TAB + 2)
		unit[j++] = 0;
	unit[0] = 6;
	unit[1] = LDBL_TAB;
	unit[LDBL_TAB] = 125000000;
	unit[LDBL_TAB - 1] = 171142578;
	unit[LDBL_TAB - 2] = 280086994;
	unit[LDBL_TAB - 3] = 443400745;
	unit[LDBL_TAB - 4] = 217248550;
	unit[LDBL_TAB - 5] = 108420;
	return (unit);
}

int				*create_unit_pos(int exposent, int dbl_tab)
{
	int	*unit;
	int	j;
	int	stack;

	unit = (dbl_tab == DBL_TAB)
		? create_unit_pos_addentum() : create_lunit_pos_addentum();
	if (!unit || !unit[0])
		return (0);
	while (exposent--)
	{
		stack = 0;
		j = 0;
		while (j++ < unit[0])
		{
			unit[unit[1] - j + 1] = unit[unit[1] - j + 1] * 2 + stack;
			if (unit[unit[1] - j + 1] >= 1000000000 && (stack = 1))
				unit[unit[1] - j + 1] -= 1000000000;
			else
				stack = 0;
		}
		if (stack)
			unit[unit[1] - unit[0]++] = 1;
	}
	return (unit);
}
