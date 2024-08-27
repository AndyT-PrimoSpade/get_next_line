#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	test_file(const char *filename, int buffer_size)
{
	int		fd;
	char	*line;
	int		line_number;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	line_number = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Buffer Size %d, Line %d: %s", buffer_size, line_number++, line);
		free(line);
	}
	close(fd);
}

int	main(void)
{
	const char	*files[] = {"test/1char.txt", "test/empty.txt",
			"test/giant_line.txt", "test/giant_line_nl.txt",
			"test/lines_around_10.txt", "test/multiple_nl.txt",
			"test/one_line_no_nl.txt", "test/only_nl.txt",
			"test/read_error.txt", "test/variable_nls.txt"};
	int			buffer_sizes[] = {10, 42, 1000, 1000000};

	for (long unsigned int i = 0; i < sizeof(files) / sizeof(files[0]); i++)
	{
		for (long unsigned int j = 0; j < sizeof(buffer_sizes)
			/ sizeof(buffer_sizes[0]); j++)
		{
			printf("Testing file: %s with buffer size: %d\n", files[i],
				buffer_sizes[j]);
			test_file(files[i], buffer_sizes[j]);
			printf("\n");
		}
	}
	return (0);
}
