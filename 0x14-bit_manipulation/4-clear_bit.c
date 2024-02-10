#include "main.h"

/**
 * clear_bit - Clears the value of a bit to 0 at a given index
 * @n: The number to clear the bit in
 * @index: The index of the bit to clear
 *
 * Return: 1 if successful, or -1 if an error occurs
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index >= sizeof(*n) * 8)
		return (-1);

	*n &= ~(1 << index);

	return (1);
}
