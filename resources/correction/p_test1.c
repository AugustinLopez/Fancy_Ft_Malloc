/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_test1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 19:11:29 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/12 15:32:19 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
int main(void)
{
	void *m[300];
	size_t	i;

	i = 0;
	m[i++] = malloc(1024);
	m[i++] = malloc(1024);
	m[i++] = malloc(1024);
	i = 0;
	free(m[i++]);
	free(m[i++]);
	free(m[i++]);
/*	i = 0;
	while (i < 30)
	{
		m[i] = malloc(1024);
		memset(m[i], 0xff, 1024);
		free(m[i]);
		i++;
	}*/
	return (0);
}
