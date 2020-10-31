# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 13:11:21 by aulopez           #+#    #+#              #
#    Updated: 2020/10/31 11:12:58 by aulopez          ###   ########.fr        #
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
		free \
		realloc \
		show_alloc_mem \
		print \
		log1 \
		log2_meta \
		get1 \
		get2_static \
		get3_size \
		mmap \
		metablock \
		metabody \
		metadata \
		calloc
LIBFT=	ft_bzero ft_memalloc ft_memccpy ft_memcpy ft_memmove ft_memset \
		ft_strcat ft_strchr ft_strchri ft_strjoin ft_strlen ft_strncpy \
		ft_strnew ft_wstrlen ft_wcharlen ft_strcpy
PRINTF=	ft_printf pf_buffer pf_number pf_number_2 pf_other pf_parsing \
		pf_string pf_string_2 pf_double
FTOA=	f_bigint f_create_unit f_operand f_create_stack f_free_precision \
		f_putnbr
SRC_X= $(MALLOC) $(LIBFT) $(PRINTF) $(FTOA)
INC=$(PATH_HDR)malloc.h
OBJ=$(SRC_X:%=$(PATH_OBJ)%.o)
SRC= $(MALLOC:%=src/%) $(LIBFT:%=minilibft/%) $(PRINTF:%=minilibft/printf/%) $(FTOA:%=minilibft/printf/ftoa/%)
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
	$(CC_O) $< -o $@

test:
	gcc resources/correction/test0.c -o test0
	gcc resources/correction/test1.c -o test1
	gcc resources/correction/test2.c -o test2
	gcc resources/correction/test3.c -o test3
	gcc resources/correction/test3bis.c -o test3bis
	gcc resources/correction/test4.c -o test4
	gcc resources/correction/test5.c -L. -lft_malloc -I./includes -o test5
	gcc resources/correction/test6.c -L. -lft_malloc -I./includes -o test6

p_test:
	gcc resources/correction/p_test0.c -o p_test0
	gcc resources/correction/p_test1.c -o p_test1
	gcc resources/correction/p_test2.c -o p_test2
	gcc resources/correction/p_test3.c -o p_test3
	gcc resources/correction/p_test4.c -o p_test4

clean:
	-@printf " ===> Removing object file(s)\n"
	@rm -f $(OBJ) $(DEP)
	-@printf " ===> Removing link(s)\n"
	@rm -f $(LINK)

fclean: clean
	-@printf " ===> Removing $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)
