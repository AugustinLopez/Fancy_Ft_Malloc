/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:51:21 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/10 16:09:51 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "minilibft.h"

int main(void)
{
	size_t	i;
	size_t	j;
	void	*m[500];

	i = 0;
	j = 0;
	while (i < 14)
	{
		m[i++] = mono_malloc(4097);
		ft_memset(m[i - 1], 0xff, 4096 * 2);
	}
	i = 0;
	while (i < 300)
		m[i++] = mono_malloc(16);
	while (j < i)
	{
		ft_printf("%3zu. %p\n", j, m[j]);
		j++;
	}
	return (0);
}
