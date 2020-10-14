/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:52:07 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 15:56:04 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "minilibft.h"

int main()
{
	void *m[30];
	size_t	i;

	m[i++] = ft_sprintf("Hello World! %32d\n", 42);
	show_alloc_mem();
	return (0);
}
