/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_operand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 12:11:28 by aulopez           #+#    #+#             */
/*   Updated: 2019/01/21 12:58:09 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_bigint.h"

int				multiply_unit_neg(int **unit)
{
	int	j;
	int	stack;

	stack = 0;
	j = (*unit)[0];
	while (j > 1)
	{
		(*unit)[j] = (*unit)[j] * 2 + stack;
		if ((*unit)[j] >= 1000000000)
		{
			stack = 1;
			(*unit)[j] -= 1000000000;
		}
		else
			stack = 0;
		j--;
	}
	return (0);
}

int				add_unit_neg(int **unit, int **stack)
{
	int	j;

	j = (*unit)[0];
	if (*(stack)[0] == 0)
		(*stack)[0] = (*unit)[0];
	while (j > 1)
	{
		(*stack)[j] += (*unit)[j];
		if ((*stack)[j] >= 1000000000)
		{
			(*stack)[j] -= 1000000000;
			(*stack)[j - 1] += 1;
		}
		j--;
	}
	return (0);
}

int				multiply_unit_pos(int **unit)
{
	int	j;
	int	stack;

	stack = 0;
	j = 0;
	while (j < (*unit)[0])
	{
		(*unit)[(*unit)[1] - j] = (*unit)[(*unit)[1] - j] * 2 + stack;
		if ((*unit)[(*unit)[1] - j] >= 1000000000)
		{
			stack = 1;
			(*unit)[(*unit)[1] - j] -= 1000000000;
		}
		else
			stack = 0;
		j++;
	}
	if (stack)
	{
		(*unit)[(*unit)[1] - (*unit)[0]] = 1;
		(*unit)[0]++;
	}
	return (0);
}

int				add_unit_pos(int **unit, int **stack)
{
	int	i;
	int	j;

	i = (*unit)[0];
	j = 0;
	while (j < i + 1)
	{
		(*stack)[(*unit)[1] - j] += (*unit)[(*unit)[1] - j];
		if ((*stack)[(*unit)[1] - j] >= 1000000000)
		{
			(*stack)[(*unit)[1] - j] -= 1000000000;
			(*stack)[(*unit)[1] - j - 1] += 1;
			if (j == i)
				(*unit)[0]++;
		}
		j++;
	}
	return (0);
}
