/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_free_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 12:06:25 by aulopez           #+#    #+#             */
/*   Updated: 2019/01/21 12:06:27 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_bigint.h"

char			*free_and_return_char(int *a, char *str)
{
	if (a)
		free(a);
	return (str);
}

int				free_and_return_int(int *a, int b)
{
	if (a)
		free(a);
	return (b);
}

void			finalize_precision(char **str, size_t j)
{
	char	*tmp;

	(*str)[j] = 0;
	if ((*str)[0] == '-' + 1 || (*str)[0] == '9' + 1)
	{
		if ((*str)[0] == '-' + 1)
			tmp = ft_strjoin("-1", (*str) + 1);
		else
			tmp = ft_strjoin("10", (*str) + 1);
		free(*str);
		if (!tmp)
			return ;
		*str = tmp;
	}
}

void			handle_precision(char **str, size_t precision, uint32_t flags)
{
	size_t	i;
	size_t	j;
	size_t	b;
	size_t	len;

	len = ft_strlen(*str);
	b = ft_strchri(*str, '.');
	i = precision + b;
	if (i <= len)
	{
		j = i;
		(*str)[i] += 5;
		while (i > 0 && (*str)[i] > '9')
		{
			(*str)[i] -= 10;
			if ((*str)[i - 1] == '.' || (*str)[i - 1] == ',')
				i--;
			(*str)[--i] += 1;
		}
		finalize_precision(str, j);
	}
	if (precision == 0 && !(flags & F_SHARP))
		(*str)[b - 1] = 0;
	else if (precision == 0)
		(*str)[b] = 0;
}
