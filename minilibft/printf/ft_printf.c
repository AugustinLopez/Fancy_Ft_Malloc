/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 19:11:18 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/12 13:20:07 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		ft_printf(const char *format, ...)
{
	t_printf	pf;

	ft_bzero(&pf, sizeof(pf));
	pf.fd = 1;
	if (!(pf.format = (char *)format))
		return (-1);
	va_start(pf.ap, format);
	while (*pf.format)
	{
		if (*pf.format == '%')
		{
			++pf.format;
			if (!*pf.format)
				break ;
			else
				pf_parse(&pf);
		}
		else
			pf_buffer_write(&pf, pf.format, 1);
		++pf.format;
	}
	pf.flag = write(pf.fd, pf.buff, pf.index);
	va_end(pf.ap);
	return (pf.len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	t_printf	pf;

	ft_bzero(&pf, sizeof(pf));
	pf.fd = fd;
	if (!(pf.format = (char *)format))
		return (-1);
	va_start(pf.ap, format);
	while (*pf.format)
	{
		if (*pf.format == '%')
		{
			++pf.format;
			if (!*pf.format)
				break ;
			else
				pf_parse(&pf);
		}
		else
			pf_buffer_write(&pf, pf.format, 1);
		++pf.format;
	}
	pf.flag = write(pf.fd, pf.buff, pf.index);
	va_end(pf.ap);
	return (pf.len);
}

int		ft_nprintf(const char *format, ...)
{
	t_printf	pf;

	ft_bzero(&pf, sizeof(pf));
	pf.noprint = 1;
	if (!(pf.format = (char *)format))
		return (-1);
	va_start(pf.ap, format);
	while (*pf.format)
	{
		if (*pf.format == '%')
		{
			++pf.format;
			if (!*pf.format)
				break ;
			else
				pf_parse(&pf);
		}
		else
			pf_buffer_write(&pf, pf.format, 1);
		++pf.format;
	}
	va_end(pf.ap);
	return (pf.len);
}

void	end_sprintf(t_printf *pf)
{
	if (pf->pc)
	{
		(pf->buff)[pf->index] = 0;
		pf_char_write(pf);
	}
}

char	*ft_sprintf(const char *format, ...)
{
	t_printf	pf;

	ft_bzero(&pf, sizeof(pf));
	pf.noprint = 2;
	if (!(pf.format = (char *)format))
		return (0);
	pf.pc = ft_strnew(PF_BUFF_SIZE);
	va_start(pf.ap, format);
	while (*pf.format)
	{
		if (*pf.format == '%')
		{
			++pf.format;
			if (!*pf.format)
				break ;
			pf_parse(&pf);
		}
		else
			pf_buffer_write(&pf, pf.format, 1);
		++pf.format;
	}
	end_sprintf(&pf);
	va_end(pf.ap);
	return (pf.pc);
}
