/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 12:53:41 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 14:03:05 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** --- Headers -----------------------------------------------------------------
*/

/*
** unistd for write
** stdarg for va_list
** wchar for wide character
** stdint for intmax_t, uintmax_t, uint32_t
** stdlib for free
*/

# include "minilibft.h"
# include <unistd.h>
# include <stdarg.h>
# include <wchar.h>
# include <stdint.h>
# include <stdlib.h>

/*
** --- Flags & buffers ---------------------------------------------------------
*/

/*
** We start at the 16th bit so we can use the first 16 to stock 2 char.
** 1st char : conversion specifier. 2nd char : base specifier.
** A buffer is used to reduce the number of call to write (performance hungry).
*/

# define F_1LONG	0x10000
# define F_2LONG	0x20000
# define F_1SHORT	0x40000
# define F_2SHORT	0x80000
# define F_LDBL		0x100000
# define F_DOT		0x200000
# define F_MINUS	0x400000
# define F_PLUS		0x800000
# define F_ZERO		0x1000000
# define F_SPACE	0x2000000
# define F_SHARP	0x4000000
# define F_QUOTE	0x8000000
# define F_WILDCARD 0x10000000
# define F_INTMAX	0x20000000
# define F_SIZE_T	0x40000000
# define F_NEGATIF	0x80000000
# define PF_BUFF_SIZE 64

/*
** --- Colors ------------------------------------------------------------------
*/

# define PF_RED			"\033[31m"
# define PF_GREEN		"\033[32m"
# define PF_YELLOW		"\033[33m"
# define PF_BLUE		"\033[34m"
# define PF_PURPLE		"\033[35m"
# define PF_CYAN		"\033[36m"
# define PF_EOC			"\033[0m"

/*
** --- Structure & Typedef -----------------------------------------------------
*/

/*
** len is the current amount of character printed.
** index & buff are used to reduce the number of call to write.
** flag contains the flag, the base and the conversion specifier.
** padding is used to print length or precision.
** printed is used to memorize the length of the string to be printed (w/o pad).
** We will use function pointer to reduce the volume of code.
*/

typedef struct			s_printf
{
	int					len;
	int					length;
	int					precision;
	int					fd;
	int					index;
	int					padding;
	int					printed;
	int					option_padding;
	int					noprint;
	char				buff[PF_BUFF_SIZE];
	va_list				ap;
	char				*format;
	char				*pc;
	int32_t				flag;
	unsigned			base;
}						t_printf;

/*
** --- Prototypes --------------------------------------------------------------
*/

void					pf_char_write(t_printf *pf);
int						pf_parse_atoi(char **str);
void					pf_parse(t_printf *pf);
int						pf_buffer_write(t_printf *pf, void *str, size_t size);
int						pf_padding(t_printf *pf, int n);
void					pf_itoa_base(uintmax_t n, int base, t_printf *pf);
char					*ft_dbltoa(double x, size_t precision, uint32_t flags);
char					*ft_ldbltoa(long double x, size_t precision,
						uint32_t flags);
int						pf_sign(t_printf *pf);
void					pf_itoa_quote(uintmax_t n, int b, char s[70],
						t_printf *pf);
void					pf_itoa_fill(uintmax_t n, int b, char s[70],
						t_printf *pf);
void					pf_putpointer(t_printf *pf);
void					pf_putvoid(t_printf *pf);
void					pf_putchar(t_printf *pf);
void					pf_putwchar(t_printf *pf);
void					pf_putstr(t_printf *pf);
void					pf_putwstr(t_printf *pf);
void					pf_putnbr(t_printf *pf);
void					pf_putnbr_base(t_printf *pf);
void					pf_getlen(t_printf *pf);
void					pf_putdouble(t_printf *pf);

#endif
