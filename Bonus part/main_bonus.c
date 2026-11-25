#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

static void	show(int fd, char *name)
{
	char	*line;

	line = get_next_line(fd);
	printf("%s : [%s]\n", name, line ? line : "NULL");
	free(line);
}

int	main(void)
{
	int	a;
	int	b;
	int	c;

	a = open("a.txt", O_RDONLY);
	b = open("b.txt", O_RDONLY);
	c = open("c.txt", O_RDONLY);
	show(a, "a");
	show(b, "b");
	show(c, "c");
	show(a, "a");
	show(b, "b");
	show(c, "c");
	show(a, "a");
	show(b, "b");
	show(c, "c");
	show(a, "a");
	show(b, "b");
	show(c, "c");
	close(a);
	close(b);
	close(c);
	return (0);
}