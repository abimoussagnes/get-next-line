/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabi-mou <aabi-mou@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:52:08 by aabi-mou          #+#    #+#             */
/*   Updated: 2025/12/03 15:58:17 by aabi-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *storage)
{
	int		i = 0;
	char	*line;

	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = malloc(i + (storage[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*clean_storage(char *storage)
{
	int		i = 0;
	int		j = 0;
	char	*new_storage;

	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	new_storage = malloc(ft_strlen_gnl(storage) - i);
	if (!new_storage)
		return (NULL);
	i++; // skip newline
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}

static char	*read_and_join(int fd, char *storage)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	bytes = 1;
	while (!ft_strchr_gnl(storage, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[bytes] = '\0';
		storage = ft_strjoin_gnl(storage, buffer);
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	storage = read_and_join(fd, storage);
	if (!storage)
		return (0);
	line = extract_line(storage);
	storage = clean_storage(storage);
	return (line);
}
