/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigint.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 12:56:14 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/12 22:35:13 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BIGINT_H
# define FT_BIGINT_H

/*
** --- Header ------------------------------------------------------------------
*/

/*
** ft_printf for flags, stdint and stdlib (malloc)
*/

# include <ft_printf.h>

/*
** --- Define ------------------------------------------------------------------
*/

/*
** Double have to be 64 bits and long double 80 bits.
** If not the case, as long as the mantissa contain a hidden bit for double but
**	not for long double, adjusting the define values should be enough.
** MTS_MAX is the maximum value of the mantissa.
** EXP_MAX is the highest (and lowest for -EXP_MAX) value of the exponent.
** EXP_MAX + 1 : the value will be inf or nan.
** MIN_EXP is the number of bits in the mantissa - 1, not including the first
**	(hidden or not) bit.
** For rounding conflict: I round to upper border.
** Rounding to the even/odd number would be better to avoid systematic errors.
*/

# define DBL_TAB 121
# define LDBL_TAB 1850
# define MTS_MAX 4503599627370496L
# define MTS2_MAX 9223372036854775807L
# define EXP_MAX 1023
# define EXP2_MAX 16383
# define MIN_EXP 51
# define MIN2_EXP 62

/*
** --- Prototypes  -------------------------------------------------------------
*/

/*
** This program is NOT optimized !
** -------------------------------
** if the sign of the exponent is positive, we use pos functions.
** if negatif, neg functions. It makes things easier conceptually.
** if long double, we use l function.
** The available operator are addition and multiply by 2
** We use divided by 2 to create our units.
** --------------------------------------------
** 31/01/2019 - I should probably optimize this thing. Later.
*/

char		*free_and_return_char(int *a, char *str);
int			free_and_return_int(int *a, int b);
void		finalize_precision(char **str, size_t j);
void		handle_precision(char **str, size_t precision, uint32_t flags);

int			*create_unit_pos(int exposent, int dbl_tab);
int			*create_unit_pos_addentum(void);
int			*create_lunit_pos_addentum(void);
int			*create_unit_neg(int exposent, int dbl_tab);
int			*create_unit_neg_addentum(int dbl_tab);

int			multiply_unit_pos(int **unit);
int			add_unit_pos(int **unit, int **stack);
int			multiply_unit_neg(int **unit);
int			add_unit_neg(int **unit, int **stack);

void		ft_putnbr_pos_addentum(int **stack, int *i, char **tmp,
										int dbl_tab);
void		ft_putnbr_pos_addentum2(int **stack, int *i, char **tmp,
										int dbl_tab);
void		ft_putnbr_pos(int **stack, char **tmp, int dbl_tab, uint32_t flags);
void		ft_putnbr_neg(int n, int end, char **tmp);

char		*infnan(uint64_t sign, uint64_t mantissa);
char		*exp_neg(uint64_t sign, int exp, uint64_t mantissa, int dbl_t);
char		*exp_pos(uint32_t flags, int exp, uint64_t mantissa, int dbl_t);

int			create_stack_neg(int **unit, int **stack, int exposent,
								uint64_t mantissa);
int			create_stack_pos(int **unit, int **stack, int exposent,
								uint64_t mantissa);
int			create_lstack_neg(int **unit, int **stack, int exposent,
								uint64_t mantissa);
int			create_lstack_pos(int **unit, int **stack, int exposent,
								uint64_t mantissa);

#endif
