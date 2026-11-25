/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottouije <ottouije@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 14:40:24 by ottouije          #+#    #+#             */
/*   Updated: 2026/11/25 16:46:45 by ottouije         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*clean_stash(const char *stash)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!stash || !stash[i + 1])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	dest = malloc((ft_strlen(stash + i) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (stash[i])
	{
		dest[j] = stash[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*extract_line(char *stash)
{
	int		i;
	int		j;
	char	*str;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = stash[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static char	*end_read(char *arr, char *stash, int num)
{
	free(arr);
	if (num < 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*read_and_stash(int fd, char *stash)
{
	ssize_t	num;
	char	*arr;
	char	*temp;

	arr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!arr)
	{
		free(stash);
		return (NULL);
	}
	num = 1;
	while (!ft_strchr(stash, '\n') && num > 0)
	{
		num = read(fd, arr, BUFFER_SIZE);
		if (num > 0)
		{
			arr[num] = '\0';
			temp = stash;
			stash = ft_strjoin(temp, arr);
			free(temp);
			if (!stash)
				num = -1;
		}
	}
	return (end_read(arr, stash, num));
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*arr;
	char		*rest;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	arr = extract_line(stash[fd]);
	if (!arr)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	rest = clean_stash(stash[fd]);
	free(stash[fd]);
	stash[fd] = rest;
	return (arr);
}
