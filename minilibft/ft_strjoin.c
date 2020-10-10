/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:24:15 by aulopez           #+#    #+#             */
/*   Updated: 2019/07/06 11:13:45 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*pc;
	size_t	n1;
	size_t	n2;

	n1 = s1 ? ft_strlen(s1) : 0;
	n2 = s2 ? ft_strlen(s2) : 0;
	if (n1 + n2 == 0)
		return (0);
	if (!(pc = (char *)malloc(sizeof(char) * (n1 + n2 + 1))))
		return (0);
	ft_strncpy(pc, s1, n1);
	ft_strncpy(pc + n1, s2, n2);
	pc[n1 + n2] = 0;
	return (pc);
}
