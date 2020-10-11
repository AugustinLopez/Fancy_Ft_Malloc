/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:59:43 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/11 02:22:43 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

/*
** I assume that:
** - A page size is 4096 bytes,
** - size_t / void * are less than 8 bytes.
*/

# include <pthread.h>
# include <stdint.h>

# define Z4 16
# define Z5 32
# define Z6 64
# define Z7 128
# define Z8 256
# define Z9 512
# define Z10 1024
# define Z11 2048
# define Z12 4096

# define AVAILABLE 15

# define MAX_Z4 32
# define MAX_OTHER 16

/*
** You don't need as much metadata for a large allocation, but I'm not
** interested in implementing it: it is merely an extension of my model,
** and nobody would use it anyway.
**
** Still, if you keep the same metahead, you could probably fit 60 aligned
** large alloc in a single page. I recommend using dedicated pages
** for large alloc to avoid fragmentation.
*/

typedef uint8_t			t_256bytes[256];

typedef struct			s_metahead
{
	struct s_metahead	*prev;
	struct s_metahead	*next;
	void				*container;
	void				*r_protect;
	void				*l_protect;
	size_t				available_heap;
	uint16_t			id[AVAILABLE];
	uint16_t			full;
}						t_metahead;

typedef struct			s_metabody
{
	uint16_t			id;
	uint16_t			index;
	uint16_t			block_count;
	void				*address;
	t_metahead			*head;
	uint8_t				free[32];
	uint8_t				size[128];
	uint8_t				store[64];
}						t_metabody;

typedef union			u_head
{
	t_metahead			data;
	t_256bytes			align;
}						t_head;

typedef union			u_body
{
	t_metabody			data;
	t_256bytes			align;
}						t_body;

typedef struct			s_metadata
{
	t_head				head;
	t_body				body[AVAILABLE];
}						t_metadata;

extern t_metadata		*g_metadata;
extern pthread_mutex_t	g_thread_mutex;

int						get_rlimit(const size_t zu);
size_t					get_page(const size_t zu);
uint16_t				get_flag(const size_t zu);
uint16_t				get_block(const size_t zu);

t_metabody				*metabody_get(const size_t zu);
void					*ptr_get(t_metabody *b, const size_t zu);

int						log_metadata_set(t_metadata *d);
int						log_metabody_set(t_metabody *b, t_metahead *h);
int						log_malloc(t_metabody *b, void *p, size_t zu);
int						log_free(t_metabody *b, void *p);
int						fd_get(void);

void					*mono_malloc(const size_t zu);
//void					*malloc(const size_t zu);

void					mono_free(void *p);
//void					free(void *p);

#endif
