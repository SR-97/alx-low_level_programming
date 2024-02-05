#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * free_listint_safe - frees a listint_t list safely (handles loops)
 * @h: pointer to the head of the linked list
 *
 * Return: the size of the list that was freed
 */
size_t free_listint_safe(listint_t **h)
{
    listint_t *current, *temp;
    size_t count = 0;

    if (h == NULL || *h == NULL)
        return 0;

    current = *h;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        count++;

        if (temp->next == temp)
        {
            *h = NULL;
            free(temp);
            break;
        }

        temp->next = NULL;
        free(temp);
    }

    *h = NULL;

    return count;
}
