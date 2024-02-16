#include "main.h"

/**
 * read_textfile - reads a text file and prints it to the POSIX standard output
 * @filename: name of the file to read
 * @letters: number of letters to read and print
 * Return: actual number of letters read and printed; 0 if failed
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd, n_read;
	char *buffer = malloc(sizeof(char) * letters);

	if (!filename || !buffer)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(buffer);
		return (0);
	}

	n_read = read(fd, buffer, letters);
	if (n_read == -1)
	{
		free(buffer);
		close(fd);
		return (0);
	}

	write(STDOUT_FILENO, buffer, n_read);

	free(buffer);
	close(fd);
	return (n_read);
}
