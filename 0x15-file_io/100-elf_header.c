#include "main.h"
#include <string.h>
#include <elf.h>

/**
 * print_magic - prints the ELF magic numbers
 * @e_ident: ELF identification array
 */
void print_magic(unsigned char *e_ident)
{
    int i;

    printf("  Magic:   ");
    for (i = 0; i < EI_NIDENT; i++)
    {
        printf("%02x", e_ident[i]);
        if (i < EI_NIDENT - 1)
            printf(" ");
    }
    printf("\n");
}

/**
 * print_class - prints the ELF file class
 * @e_ident: ELF identification array
 */
void print_class(unsigned char *e_ident)
{
    printf("  Class:                             ");
    switch (e_ident[EI_CLASS])
    {
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_CLASS]);
            break;
    }
}

/**
 * print_data - prints the ELF data encoding
 * @e_ident: ELF identification array
 */
void print_data(unsigned char *e_ident)
{
    printf("  Data:                              ");
    switch (e_ident[EI_DATA])
    {
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_DATA]);
            break;
    }
}

/**
 * print_version - prints the ELF version
 * @e_ident: ELF identification array
 */
void print_version(unsigned char *e_ident)
{
    printf("  Version:                           %d (current)\n", e_ident[EI_VERSION]);
}

/**
 * print_osabi - prints the ELF OS/ABI
 * @e_ident: ELF identification array
 */
void print_osabi(unsigned char *e_ident)
{
    printf("  OS/ABI:                            ");
    switch (e_ident[EI_OSABI])
    {
        case ELFOSABI_NONE:
            printf("UNIX - System V\n");
            break;
        case ELFOSABI_HPUX:
            printf("UNIX - HP-UX\n");
            break;
        case ELFOSABI_NETBSD:
            printf("UNIX - NetBSD\n");
            break;
        case ELFOSABI_LINUX:
            printf("UNIX - Linux\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("UNIX - Solaris\n");
            break;
        case ELFOSABI_AIX:
            printf("UNIX - AIX\n");
            break;
        case ELFOSABI_IRIX:
            printf("UNIX - IRIX\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("UNIX - FreeBSD\n");
            break;
        case ELFOSABI_TRU64:
            printf("UNIX - TRU64\n");
            break;
        case ELFOSABI_MODESTO:
            printf("Novell - Modesto\n");
            break;
        case ELFOSABI_OPENBSD:
            printf("UNIX - OpenBSD\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_OSABI]);
            break;
    }
}

/**
 * print_abiversion - prints the ELF ABI version
 * @e_ident: ELF identification array
 */
void print_abiversion(unsigned char *e_ident)
{
    printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

/**
 * print_type - prints the ELF type
 * @e_type: ELF type
 */
void print_type(unsigned int e_type)
{
    printf("  Type:                              ");
    switch (e_type)
    {
        case ET_NONE:
            printf("NONE (Unknown type)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown: %#x>\n", e_type);
            break;
    }
}

/**
 * print_entry - prints the ELF entry point address
 * @e_entry: ELF entry point address
 */
void print_entry(Elf64_Addr e_entry)
{
    printf("  Entry point address:               %#lx\n", (unsigned long)e_entry);
}

/**
 * elf_header - displays the ELF header information
 * @filename: name of the ELF file
 * Return: 0 on success, 98 on failure
 */
int elf_header(const char *filename)
{
    int fd;
    Elf64_Ehdr ehdr;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        dprintf(STDERR_FILENO, "Error: Could not open file '%s'\n", filename);
        return (98);
    }

    if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr))
    {
        dprintf(STDERR_FILENO, "Error: Could not read ELF header from file '%s'\n", filename);
        close(fd);
        return (98);
    }

    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0)
    {
        dprintf(STDERR_FILENO, "Error: '%s' is not an ELF file\n", filename);
        close(fd);
        return (98);
    }

    printf("ELF Header:\n");
    print_magic(ehdr.e_ident);
    print_class(ehdr.e_ident);
    print_data(ehdr.e_ident);
    print_version(ehdr.e_ident);
    print_osabi(ehdr.e_ident);
    print_abiversion(ehdr.e_ident);
    print_type(ehdr.e_type);
    print_entry(ehdr.e_entry);

    close(fd);
    return (0);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 98 on failure
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        dprintf(STDERR_FILENO, "Usage: %s elf_filename\n", argv[0]);
        return (98);
    }

    return (elf_header(argv[1]));
}
