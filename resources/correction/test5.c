/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:04:37 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/12 22:14:03 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int main()
{
	malloc(1);
	malloc(8);
	malloc(9);
	malloc(16);
	malloc(32);
	malloc(64);
	malloc(128);
	malloc(129);
	malloc(256);
	malloc(512);
	malloc(1024);
	malloc(1024 * 2);
	malloc(1024 * 16);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}