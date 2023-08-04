#include "include/list_node.h"

ListNode *ListNode_AddNode(ListNode **head, const char *data)
{ 
    ListNode *new_node = malloc(sizeof(ListNode));
    if (head == NULL) // empty list
    {
        if (new_node == NULL)
        {
            perror("Couldn't create a new node");
            return NULL;
        }
        new_node->data = strdup(data);
        new_node->next = NULL;
    }
    else // List not empty
    {
        if (new_node == NULL)
        {
            perror("Couldn't create a new node");
            return NULL;
        }
        new_node->data = strdup(data);
        new_node->next = *head;
        *head = new_node;
    }

    return new_node;
}

void ListNode_RemoveAll(ListNode *head)
{
    while (head != NULL)
    {
        ListNode *temp = head;
        head = head->next;
        free((void *)temp->data);
        free(temp);
    }
}

void ListNode_PrintAll(ListNode *head)
{
    ListNode *current = head;
    while (current != NULL)
    {
        printf("%s\n", current->data);
        current = current->next;
    }
}
