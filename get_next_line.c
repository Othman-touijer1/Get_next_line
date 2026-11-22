/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ottouije <ottouije@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:14:02 by ottouije          #+#    #+#             */
/*   Updated: 2026/11/21 18:12:17 by ottouije         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*end_read(char *arr, char *stash, ssize_t num)
{
	free(arr);
	if (num < 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*clean_stash(char *stash)
{
	char	*dest;
	int		i;
	int		j;

	if (!stash)
		return (NULL);
	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (!stash[i] || !stash[i + 1])
		return (NULL);
	dest = malloc((ft_strlen(stash + ++i) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (stash[i])
	{
		dest[j] = stash[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*extract_line(char *stash)
{
	char	*str;
	int		i;
	int		j;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
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

char	*read_and_stash(int fd, char *stash, size_t buffer_size)
{
	char	*arr;
	char	*temp;
	ssize_t	num;

	arr = malloc(buffer_size + 1);
	if (!arr)
	{
		free(stash);
		return (NULL);
	}
	num = 1;
	while (!ft_strchr(stash, '\n') && num > 0)
	{
		num = read(fd, arr, buffer_size);
		if (num > 0)
		{
			arr[num] = '\0';
			temp = stash;
			stash = ft_strjoin(temp, arr);
			if (!stash)
				num = -1;
		}
	}
	return (end_read(arr, stash, num));
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*str;
	char		*new_stash;
	size_t		buffer_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_size = (size_t)BUFFER_SIZE;
	stash = read_and_stash(fd, stash, buffer_size);
	if (!stash)
		return (NULL);
	str = extract_line(stash);
	if (!str)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	new_stash = clean_stash(stash);
	free(stash);
	stash = new_stash;
	return (str);
}

int	main(void)
{
	char *str;
	int fd = open("text.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}