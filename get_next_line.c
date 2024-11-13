/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdausque <tdausque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:40:06 by tdausque          #+#    #+#             */
/*   Updated: 2024/11/13 12:17:56by tdausque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*fill_stash(int fd, char *buff, char *stash)
{
	int		b_reads;

	b_reads = 1;
	while (!ft_strchr(buff, '\n') && b_reads != 0)
	{
		b_reads = read(fd, buff, BUFFER_SIZE);
		if (b_reads <= 0)
		{
			free(buff);
			return (0);
		}
		buff[b_reads] = 0;
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*extract_line(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	// if (line[i] == '\0' || line[0] == '\0')
	// {
	// 	free(line);
	// 	return (0);
	// }
	tmp = ft_substr(line, i + 1, ft_strlen(line));
	if (!tmp)
	{
		free(line);
		return (0);
	}
	line[i + 1] = 0;
	return (tmp);
}

char	*get_next_line(int fd)
{
	char			*buff;
	char			*line;
	static char		*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		return (0);
	}
	if (stash == NULL)
	{
		stash = malloc(1);
		if (!stash)
			return (0);
		stash[0] = '\0';
	}
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (0);
	buff[0] = '\0';
	line = fill_stash(fd, buff, stash);
	if (!line)
		return (0);
	stash = extract_line(line);
	return (line);
}

int	main(void)
{
	char	*buff;
	int		fd;

	fd = open("tests/test.txt", O_RDONLY);
	buff = get_next_line(fd);
	while (buff)
	{
		printf("%s", buff);
		free(buff);
		buff = get_next_line(fd);
	}
	printf("%s", buff);
	return (0);
}
