# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 13:11:21 by aulopez           #+#    #+#              #
#    Updated: 2020/10/10 15:35:01 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE:= $(shell uname -m)_$(shell uname -s)
endif

NAME=libft_malloc_$(HOSTTYPE).so
LINK=libft_malloc.so
COMPILER=clang
FLAGS=-g3 -pedantic -Wall -Wextra -Werror -MMD -MP -fPIC

VPATH=srcs:minilibft:minilibft/printf:minilibft/printf/ftoa
PATH_HDR=./includes/
PATH_OBJ=./.object/
PATH_TEST=./test/

CC_O=$(COMPILER) $(FLAGS) -c -I$(PATH_HDR)
CC_C=$(COMPILER) -shared $(OBJ) -I$(PATH_HDR)

MALLOC=	extern \
		malloc \
		miscellaneous_get \
		ptr_malloc_get \
		metabody_malloc_get
LIBFT=	ft_bzero ft_memalloc ft_memccpy ft_memcpy ft_memmove ft_memset \
		ft_strcat ft_strchr ft_strchri ft_strjoin ft_strlen ft_strncpy ft_strnew
PRINTF=	ft_printf pf_buffer pf_number pf_number_2 pf_other pf_parsing \
		pf_string pf_string_2 pf_double
FTOA=	f_bigint f_create_unit f_operand f_create_stack f_free_precision \
		f_putnbr
SRC= $(MALLOC) $(LIBFT) $(PRINTF) $(FTOA)
INC=$(PATH_HDR)malloc.h
OBJ=$(SRC:%=$(PATH_OBJ)%.o)
DEP=$(OBJ:%.o=%.d)

# --- 4.Rules ------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJ)
	-@printf " ===> Creating $(NAME)\n"
	@$(CC_C) -o $(NAME)
	-@printf " ===> Creating $(LINK)\n"
	@rm -f $(LINK)
	@ln -s $(NAME) $(LINK)

$(PATH_OBJ)%.o:%.c
	-@printf " >O $(FLAGS) $*\n"
	@$(CC_O) $< -o $@

clean:
	-@printf " ===> Removing object file(s)\n"
	@rm -f $(OBJ) $(DEPS)
	-@printf " ===> Removing link(s)\n"
	@rm -f $(LINK)

fclean: clean butter
	-@printf " ===> Removing $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)
