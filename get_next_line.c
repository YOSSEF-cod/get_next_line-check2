/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:14:22 by ybounite          #+#    #+#             */
/*   Updated: 2024/11/27 20:58:54 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


#include "get_next_line.h"

int	ft_strchar(char	*str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return 1;
		i++;
	}
	return 0;
}

char	*check_if_newline(char	*line)
{
	char	*save;
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return NULL;
	save = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!save)
		return (NULL);
	line[i + 1] = '\0';
	if (save && save[0] == '\0')
	{
		free(save);
		save = NULL;
	}
	return (save);
}
char	*ft_full_buffer_line(int	fd, char	*buffer, char	*save)
{
	ssize_t	len;
	char	*ptr;
	while (!(ft_strchar(buffer, '\n')))
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len <= 0)
			break ;
		buffer[len] = '\0';
		if (!save)
			save = ft_strdup("");
		ptr = save;
		save = ft_strjoin(ptr, buffer);
		if (!save)
			return (free(save), save = NULL, NULL);
		free(ptr);
		}
	return (save);
}

char	*get_next_line(int	fd)
{
	static char *save;
	char	*buffer;
	char	*line;
	if (fd < 0 || BUFFER_SIZE <= 0 ||  read(fd, NULL, 0) < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(save), save = NULL, NULL);
	line = ft_full_buffer_line(fd, buffer, save);
	free(buffer);
	buffer = NULL;
	if (!line)
		return NULL;
	save = check_if_newline(line);
	if (!save && ft_strlen(line) == 0)
		return (NULL);
	return (line);
}
