/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:52:07 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 19:57:04 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "minilibft.h"

int main()
{
	void *m[30];
	size_t	i;

	m[i++] = malloc(32);
	m[i++] = malloc(29);
	m[i++] = ft_sprintf("Hello World! %32d\n", 42);
	ft_memset(m[1], 0, 32);
	show_alloc_mem_ex();
	free(m[1]);
	ft_printf("%s\n", m[1]);
	return (0);
}
