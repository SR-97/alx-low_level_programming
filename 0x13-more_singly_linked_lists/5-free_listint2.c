#include "lists.h"
#include <stdlib.h>

/**
 * free_listint2 - Frees a listint_t list and sets the head to NULL.
 * @head: Pointer to the head of the listint_t list.
 */
void free_listint2(listint_t **head)
{
    listint_t *current, *next;

    if (head == NULL || *head == NULL)
        return;

    current = *head;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}
