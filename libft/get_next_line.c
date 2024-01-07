/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:05:57 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/06 16:17:33 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy_ptr(char *dst, const char *src)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (src[i] && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
		dst[i++] = '\n';
	dst[i] = '\0';
	return (dst);
}

char	*ft_data1(char *backup)
{
	struct s_data1	data1;

	data1.i = 0;
	data1.j = 0;
	data1.len = ft_strlen_gnl(backup);
	while (backup[data1.i] && backup[data1.i] != '\n')
		data1.i++;
	if (!backup[data1.i])
	{
		free(backup);
		return (NULL);
	}
	data1.line = malloc(sizeof(char) * ((data1.len - data1.i) + 1));
	if (!data1.line)
		return (NULL);
	data1.i++;
	while (backup[data1.i])
		data1.line[data1.j++] = backup[data1.i++];
	data1.line[data1.j] = '\0';
	free(backup);
	return (data1.line);
}

char	*ft_read(int fd, char *backup)
{
	struct s_data1	data1;

	data1.buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!data1.buffer)
		return (NULL);
	data1.buffer[0] = '\0';
	data1.read = 1;
	while (!(ft_strchr_gnl(data1.buffer, '\n')) && data1.read)
	{
		data1.read = read(fd, data1.buffer, BUFFER_SIZE);
		if (data1.read == -1)
		{
			free(data1.buffer);
			free(backup);
			return (NULL);
		}
		data1.buffer[data1.read] = '\0';
		backup = ft_strjoin_gnl(backup, data1.buffer);
	}
	free(data1.buffer);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char		*backup;
	struct s_data1	data1;

	data1.ln = NULL;
	data1.k = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = ft_read(fd, backup);
	if (!backup)
		return (NULL);
	if (*backup)
	{
		while (backup[data1.k] && backup[data1.k] != '\n')
			data1.k++;
		data1.ln = malloc(sizeof(char) * (data1.k + 2));
		if (!data1.ln)
		{
			free(backup);
			return (NULL);
		}
		data1.ln = ft_strcpy_ptr(data1.ln, backup);
	}
	backup = ft_data1(backup);
	return (data1.ln);
}
