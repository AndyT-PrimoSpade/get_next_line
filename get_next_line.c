/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andtan <andtan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:48:33 by andtan            #+#    #+#             */
/*   Updated: 2024/07/13 15:34:41 by andtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*handle_read_error(char *buffer, char *stored)
{
	if (buffer)
		free(buffer);
	if (stored)
		free(stored);
	return (NULL);
}

static char	*read_and_store(int fd, char *stored)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (handle_read_error(NULL, stored));
	bytes_read = 1;
	while (!ft_strchr(stored, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (handle_read_error(buffer, stored));
		buffer[bytes_read] = '\0';
		stored = ft_join_or_dup(stored, buffer);
		if (!stored)
			return (handle_read_error(buffer, NULL));
	}
	free(buffer);
	return (stored);
}

static char	*extract_line(char *stored)
{
	char	*line;
	size_t	i;

	if (!stored || !stored[0])
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (stored[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
	{
		line[i] = stored[i];
		i++;
	}
	if (stored[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*save_remaining(char *stored)
{
	char	*remaining;
	size_t	i;
	size_t	j;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i] || !stored[i + 1])
	{
		free(stored);
		return (NULL);
	}
	remaining = malloc(ft_strlen(stored) - i);
	if (!remaining)
	{
		free(stored);
		return (NULL);
	}
	i++;
	j = 0;
	while (stored[i])
		remaining[j++] = stored[i++];
	remaining[j] = '\0';
	free(stored);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = read_and_store(fd, stored);
	if (!stored)
		return (NULL);
	line = extract_line(stored);
	if (!line)
	{
		free(stored);
		stored = NULL;
		return (NULL);
	}
	stored = save_remaining(stored);
	return (line);
}
