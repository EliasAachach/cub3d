/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:54:13 by elaachac          #+#    #+#             */
/*   Updated: 2021/06/09 16:11:14 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	ft_free(void **var, int ret_value)
{
	if (*var)
	{
		free(*var);
		*var = NULL;
	}
	return (ret_value);
}

static	int	get_line(char **rest, char **line, size_t start)
{
	char	*tmp;

	tmp = ft_strchr(*rest + start, (int) '\n');
	if (!tmp)
		return (0);
	*line = ft_substr(*rest, 0, tmp - *rest);
	ft_memcpy(*rest, tmp + 1, ft_strlen(tmp));
	return (1);
}

static	int	read_fd(int fd, char **line, char **rest)
{
	char		*buf;
	ssize_t		total_len;
	ssize_t		len;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	total_len = 0;
	if (*rest)
		total_len = ft_strlen(*rest);
	while ((len = read(fd, buf, BUFFER_SIZE)))
	{
		*rest = ft_realloc(*rest, total_len + len + 1, total_len);
		ft_memcpy(*rest + total_len, buf, len);
		(*rest)[total_len + len] = '\0';
		if (get_line(rest, line, total_len))
			return (ft_free((void **)&buf, 1));
		total_len += len;
	}
	return (ft_free((void **)&buf, 0));
}

int	get_next_line(int fd, char **line)
{
	static char	*rest = NULL;
	int			ret;

	if (line == NULL || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if (rest && get_line(&rest, line, 0))
		return (1);
	if ((ret = read_fd(fd, line, &rest)))
		return (ret);
	*line = rest;
	if (*line == NULL)
	{
		*line = (char *)malloc(sizeof(char) * 1);
		if (!line)
			return (-1);
		(*line)[0] = '\0';
		return (0);
	}
	rest = NULL;
	return (0);
}
