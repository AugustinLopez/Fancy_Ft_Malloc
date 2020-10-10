/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:37:09 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/10 15:56:47 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdint.h>
# include <sys/types.h>

/*
** --- Color Macro -------------------------------------------------------------
*/

# define ONE_EACH_BYTE	0x0101010101010101L
# define REV_EACH_BYTE	0x8080808080808080L
# define LOG_UINT32_MAX	10
# define LOG_UINT_MAX	LOG_UINT32_MAX
# define LOG_UINT64_MAX	20
# define POW10_LOG_SIZE_MAX 10000000000000000000UL

# define FT_EOC			"\033[0m"
# define FT_BOLD		"\033[1m"
# define FT_DIM			"\033[2m"
# define FT_ITALIC		"\033[3m"
# define FT_UNDER		"\033[4m"
# define FT_REV			"\033[7m"
# define FT_HIDE		"\033[8m"
# define FT_STRIKE		"\033[9m"
# define FT_R_BOLD		"\033[21m"
# define FT_R_DIM		"\033[22m"
# define FT_R_ITALIC	"\033[23m"
# define FT_R_UNDER		"\033[24m"
# define FT_R_REV		"\033[27m"
# define FT_R_HIDE		"\033[28m"
# define FT_R_STRIKE	"\033[29m"

# define FT_R_COLOR		"\033[39m"
# define FT_BLACK		"\033[30m"
# define FT_RED			"\033[31m"
# define FT_GREEN		"\033[32m"
# define FT_YELLOW		"\033[33m"
# define FT_BLUE		"\033[34m"
# define FT_PURPLE		"\033[35m"
# define FT_CYAN		"\033[36m"
# define FT_GRAY		"\033[90m"
# define FT_WHITE		"\033[97m"
# define FT_LGRAY		"\033[37m"
# define FT_LRED		"\033[91m"
# define FT_LGREEN		"\033[92m"
# define FT_LYELLOW		"\033[93m"
# define FT_LBLUE		"\033[94m"
# define FT_LPURPLE		"\033[95m"
# define FT_LCYAN		"\033[96m"

# define FT_R_BCOLOR	"\033[49m"
# define FT_BBLACK		"\033[40m"
# define FT_BRED		"\033[41m"
# define FT_BGREEN		"\033[42m"
# define FT_BYELLOW		"\033[43m"
# define FT_BBLUE		"\033[44m"
# define FT_BPURPLE		"\033[45m"
# define FT_BCYAN		"\033[46m"
# define FT_BGRAY		"\033[100m"
# define FT_BWHITE		"\033[107m"
# define FT_BLGRAY		"\033[47m"
# define FT_BLRED		"\033[101m"
# define FT_BLGREEN		"\033[102m"
# define FT_BLYELLOW	"\033[103m"
# define FT_BLBLUE		"\033[104m"
# define FT_BLPURPLE	"\033[105m"
# define FT_BLCYAN		"\033[106m"

/*
** --- Raw Memory Functions ----------------------------------------------------
*/

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *s1, const void *s2, size_t n);
void				*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void				*ft_memmove(void *s1, const void *s2, size_t len);
void				*ft_memalloc(size_t size);

/*
** --- Print Functions ---------------------------------------------------------
*/

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
char				*ft_sprintf(const char *format, ...);
int					ft_nprintf(const char *format, ...);

/*
** --- String Functions --------------------------------------------------------
*/

char				*ft_strcat(char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_pathjoin(char const *s1, char const *s2);
char				*ft_strchr(const char *s, int c);
size_t				ft_strchri(const char *s, int c);
size_t				ft_strlen(const char *s);
char				*ft_strnew(size_t size);
size_t				ft_wstrlen(unsigned *str);
size_t				ft_wcharlen(unsigned wc);

#endif
