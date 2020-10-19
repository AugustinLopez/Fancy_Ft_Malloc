/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 12:49:39 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/04 15:01:24 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define M (1024 * 1024)
# include <unistd.h>
# include <string.h>
#include <stdlib.h>

int main(void)
{
	char	*addr1;
	char	*addr2;
	char	*addr3;

	addr1 = (char *)malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	write(1, addr1, strlen(addr1));
	addr2 = (char *)malloc(16 * M);
	addr3 = (char *)realloc(addr1, 128 * M);
	addr3[127 * M]=42;
	write(1, addr3, strlen(addr3));
	return (0);
}
