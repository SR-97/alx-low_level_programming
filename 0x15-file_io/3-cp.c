#include "main.h"

/**
 * cp_error - prints error message to standard error
 * @code: error code
 * @file: file name
 * Return: error code
 */
int cp_error(int code, char *file)
{
    switch (code)
    {
        case 97:
            dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
            break;
        case 98:
            dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
            break;
        case 99:
            dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
            break;
        case 100:
            dprintf(STDERR_FILENO, "Error: Can't close fd %s\n", file);
            break;
    }
    exit(code);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 97-100 on failure
 */
int main(int argc, char *argv[])
{
    int fd_from, fd_to, n_read, n_write;
    char buffer[1024];

    if (argc != 3)
        cp_error(97, NULL);

    fd_from = open(argv[1], O_RDONLY);
    if (fd_from == -1)
        cp_error(98, argv[1]);

    fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd_to == -1)
        cp_error(99, argv[2]);

    do {
        n_read = read(fd_from, buffer, 1024);
        if (n_read == -1)
            cp_error(98, argv[1]);

        n_write = write(fd_to, buffer, n_read);
        if (n_write == -1 || n_write != n_read)
            cp_error(99, argv[2]);
    } while (n_read == 1024);

    if (close(fd_from) == -1)
        cp_error(100, argv[1]);
    if (close(fd_to) == -1)
        cp_error(100, argv[2]);

    return (0);
}
