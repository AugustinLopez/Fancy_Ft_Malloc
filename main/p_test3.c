/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_test3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 19:11:29 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/12 16:57:34 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
int main(void)
{
	void *m[30];
	size_t	i;

	i = 0;
	while (i < 10)
	{
		m[i] = malloc(4097);
		memset(m[i], 0xff, 4097);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		free(m[i*2]);
		i++;
	}
	i = 15;
	while (i < 20)
	{
		m[i] = malloc(4097);
		i++;
	}
	return (0);
}
