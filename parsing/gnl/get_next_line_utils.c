/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:22:23 by elaachac          #+#    #+#             */
/*   Updated: 2020/03/10 13:54:33 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const	char *s)
{
	size_t count;

	count = 0;
	if (!(s))
		return (0);
	while (s[count])
		count++;
	return (count);
}

char		*ft_substr(const char *s, unsigned int start, size_t n)
{
	char			*str;

	if (!(str = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	str[n] = '\0';
	ft_memcpy(str, s + start, n);
	return (str);
}

char		*ft_strchr(const char *s, int c)
{
	if ((char)c == '\0')
		return ("\0");
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char		*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void *tmp;

	if ((tmp = (void *)malloc(sizeof(void) * size)))
		ft_memcpy(tmp, ptr, old_size);
	free(ptr);
	return (tmp);
}

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str2;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	str = (unsigned char *)src;
	str2 = (unsigned char *)dest;
	while (i < n)
	{
		str2[i] = str[i];
		i++;
	}
	return (dest);
}
