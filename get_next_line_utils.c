/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssaavedr <ssaavedr@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 12:51:50 by ssaavedr          #+#    #+#             */
/*   Updated: 2026/11/24 09:28:14 by ssaavedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *str, int target_char)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)target_char)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)target_char == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (!stash)
	{
		stash = (char *)malloc(1 * sizeof(char));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	if (!buffer)
		return (free(stash), NULL);
	joined = malloc((ft_strlen(stash) + ft_strlen(buffer) + 1) * sizeof(char));
	if (!joined)
		return (free(stash), NULL);
	i = 0;
	j = 0;
	while (stash[j] != '\0')
		joined[i++] = stash[j++];
	j = 0;
	while (buffer[j] != '\0')
		joined[i++] = buffer[j++];
	joined[i] = '\0';
	return (free(stash), joined);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if (start >= str_len)
		len = 0;
	else if (len > str_len - start)
		len = str_len - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && str[start + i] != '\0')
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
