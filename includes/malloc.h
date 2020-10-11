/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:59:43 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/12 00:05:26 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <pthread.h>
# include <stdint.h>


/*
** - Metadata :
**     > 1 Page containing : 1 Head Metadata - 15 Zones Metadata
**     > 256 bytes aligned / returned memory is allocated separately 
**     > Additional metadata page are created as needed
** - Zone Size:
**     > Every Power Of 2 between 16 (TINY) and 2048 (SMALL).
**     > 256 addresses for 16 bytes, 128 otherwise. Everything is aligned.
**     > At most 1.0625 bytes of metadata per address below 16.
       > At most 2.0625 bytes of metadata per address below or equal to 2048.
**     > Anything above 2049 is one allocation in a zone. Page aligned.
**     > 273.067 bytes of metadata per address above 2048.
** - Possible development:
**     > Anything above 2049: allocate 64 pages and implement fragmentation.
**       so large would be larger than 262144 bytes would be large allocation.
**       It could "probably" fit on 256 bytes: assuming 512 bytes, this is about
**       0.2% of metadata for up to 64 allocations aligned on a page basis.
** - Note:
**     > Implementation fragmentation below the page level seems like a waste.
**       With my model, each allocation above 7 consume at least 50% of its
**       dedicated memory, the ptr are aligned, the metadata can be moved in
**       a safe location protected against most involuntary buffer overflow.
**       My metadata overhead is also extremely low and constrained by the need
**       to save the size.
*/

/*
** - We use Z-value as both bytes limit and flags: ZLARGE is anything above 2048
** - We can fit 16 metadatas of 256 bytes in a 4096 bytes page. one of them
**   is used to handle the metadata's metadata (duh) leaving us with 15.
** - We can with 256 address of 16 bytes in a pages. No point in wasting half
**   the page. In this situation we need 256 bits of data, 32 * 8.
*/

# define Z4 16
# define Z5 32
# define Z6 64
# define Z7 128
# define Z8 256
# define Z9 512
# define Z10 1024
# define Z11 2048
# define ZMAX Z11
# define ZLARGE 2049

# define AVAILABLE 15
# define MAX_Z4 32
# define MAX_OTHER 16

/*
** - We use union to enforce alignment.
** - We store size as (size - 1) so the value '0' is not wasted.
** - We store the free boolean status as a single bit.
** - We store 4 bits size in 0.5 byte.
** - We store 9, 10, 11 bits size in 1,5 bytes (using store).
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
void					*malloc(const size_t zu);

void					mono_free(void *p);
void					free(void *p);

#endif
