/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_static.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:18:13 by aulopez           #+#    #+#             */
/*   Updated: 2020/10/14 16:15:30 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int			get_fd()
{
	static int fd = -2;

	if (LOG_MEMORY == 0)
		fd = -1;
	if (fd == -2)
		fd = open("log_malloc.txt", O_CREAT | O_RDWR | O_TRUNC);
	return (fd);
}

int		get_env(void)
{
	static int flag = 0;

	if (flag == 0)
	{
		if (getenv(ENV_ZONE_TXT))
			flag |= ENV_ZONE;
		if (getenv(ENV_LOG_TXT))
			flag |= ENV_LOG;
		if (getenv(ENV_SCRIBBLE_TXT))
			flag |= ENV_SCRIBBLE;
		if (getenv(ENV_PRESCRIBBLE_TXT))
			flag |= ENV_PRESCRIBBLE;
		flag |= 1;
	}
	return (flag);
}

