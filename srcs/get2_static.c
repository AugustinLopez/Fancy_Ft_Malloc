/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get2_static.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:18:13 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/19 13:39:40 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <fcntl.h>
#include <stdlib.h>

/*
** BONUS:
** When called for the first time, set the environment flag
** Return the environment flag.
**
** Calling the getenv function each time is wasteful and could create issue
** if the environment were to change between call. We store them in a static
** to prevent this issue.
**
** Scribble desactivated: it causes crash with the correction script...
*/

int	get_env(void)
{
	static int	flag = 0;

	if (flag == 0)
	{
		if (getenv(ENV_ZONE_TXT))
			flag |= ENV_ZONE;
		if (getenv(ENV_LOG_TXT))
			flag |= ENV_LOG;
		if (getenv(ENV_PRESCRIBBLE_TXT))
			flag |= ENV_PRESCRIBBLE;
		if (getenv(ENV_GUARD_TXT))
			flag |= ENV_GUARD;
		flag |= 1;
	}
	return (flag);
}

/*
** BONUS:
** When called for the first time, open and clear a log_malloc.txt file.
** Return the file descriptor of this file, or -1 if an error occured.
**
** Opening and closing the file each time is wasteful, so we keep it open and
** let the system close it when the program end.
*/

int	get_fd(void)
{
	static int	fd = -2;

	if ((get_env() & ENV_LOG) == 0)
		fd = -1;
	if (fd == -2)
		fd = open("log_malloc.txt", O_CREAT | O_RDWR | O_TRUNC);
	return (fd);
}
