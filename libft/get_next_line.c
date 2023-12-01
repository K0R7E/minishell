/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:05:57 by akortvel          #+#    #+#             */
/*   Updated: 2023/10/30 13:39:28 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct s_data{
	int		i;
	int		j;
	int		len;
	char	*line;
	char	*buffer;
	int		read;
	char	*ln;
	int		k;
	int		b;
};

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

char	*ft_data(char *backup)
{
	struct s_data	data;

	data.i = 0;
	data.j = 0;
	data.len = ft_strlen_gnl(backup);
	while (backup[data.i] && backup[data.i] != '\n')
		data.i++;
	if (!backup[data.i])
	{
		free(backup);
		return (NULL);
	}
	data.line = malloc(sizeof(char) * ((data.len - data.i) + 1));
	if (!data.line)
		return (NULL);
	data.i++;
	while (backup[data.i])
		data.line[data.j++] = backup[data.i++];
	data.line[data.j] = '\0';
	free(backup);
	return (data.line);
}

char	*ft_read(int fd, char *backup)
{
	struct s_data	data;

	data.buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!data.buffer)
		return (NULL);
	data.buffer[0] = '\0';
	data.read = 1;
	while (!(ft_strchr_gnl(data.buffer, '\n')) && data.read)
	{
		data.read = read(fd, data.buffer, BUFFER_SIZE);
		if (data.read == -1)
		{
			free(data.buffer);
			free(backup);
			return (NULL);
		}
		data.buffer[data.read] = '\0';
		backup = ft_strjoin_gnl(backup, data.buffer);
	}
	free(data.buffer);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char		*backup;
	struct s_data	data;

	data.ln = NULL;
	data.k = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = ft_read(fd, backup);
	if (!backup)
		return (NULL);
	if (*backup)
	{
		while (backup[data.k] && backup[data.k] != '\n')
			data.k++;
		data.ln = malloc(sizeof(char) * (data.k + 2));
		if (!data.ln)
		{
			free(backup);
			return (NULL);
		}
		data.ln = ft_strcpy_ptr(data.ln, backup);
	}
	backup = ft_data(backup);
	return (data.ln);
}
