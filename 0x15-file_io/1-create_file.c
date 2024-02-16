#include "main.h"

/**
 * create_file - creates a file and writes text_content to it
 * @filename: name of the file to create
 * @text_content: NULL-terminated string to write to the file
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int fd, n_write;
	mode_t mode = S_IRUSR | S_IWUSR;
	int len = 0;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
	if (fd == -1)
		return (-1);

	if (text_content)
	{
		while (text_content[len])
			len++;
		n_write = write(fd, text_content, len);
		if (n_write == -1 || n_write != len)
			return (-1);
	}

	close(fd);
	return (1);
}
