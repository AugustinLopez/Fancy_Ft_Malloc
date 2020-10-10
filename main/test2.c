/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 22:07:43 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/11 00:32:29 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minilibft.h"

int	main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while(i < 1024)
	{
		addr = (char *)malloc(1024);
		addr[0] = 42;
		ft_printf("%p\n", addr);
		free(addr);
		i++;
	}
	return (0);
}
