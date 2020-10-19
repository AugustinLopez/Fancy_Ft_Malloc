/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_test0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 19:11:29 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/11 01:17:26 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "malloc.h"
int main(void)
{
	void *m[300];
	size_t	i;

	while (i < 30)
	{
		m[i] = mono_malloc(1024);
		printf("%3zu - %p\n", i, m[i]);
		memset(m[i], 0xff, 1024);
		printf("%3zu - %p\n", i, m[i]);
		mono_free(m[i]);
		i++;
	}
	return (0);
}
