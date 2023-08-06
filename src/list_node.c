#include "include/list_node.h"

ListNode *ListNode_AddNode(ListNode **head, const char *data)
{ 
    ListNode *new_node = malloc(sizeof(ListNode));
    if (new_node == NULL)
    {
        perror("Couldn't create a new node");
        return NULL;
    }

    new_node->data = strdup(data);
    if (head == NULL) // empty list
    {
        // is node the last and first of the list
        new_node->last = new_node;
        new_node->next = NULL;
    }
    else // List not empty
    {
        new_node->next = *head;
        *head = new_node;
    }

    return new_node;
}

ListNode *ListNode_AppendNode(ListNode **head, const char *data)
{
    ListNode *new_node = malloc(sizeof(ListNode));

    if (new_node == NULL)
    {
        perror("Couldn't create a new node");
        return NULL;
    }

    new_node->data = strdup(data);
    new_node->next = NULL;

    if (*head == NULL) // List empty
    {
        *head = new_node; 
        new_node->last = new_node;
    }
    else 
    {
        (*head)->last->next = new_node;
        (*head)->last = new_node;
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
        printf("%s\n\r", current->data);
        current = current->next;
    }
}

ListNode *ListNode_Search(ListNode *head, const char *searchterm)
{
    ListNode *current = head;
    ListNode *res = NULL;
    while (current != NULL) 
    {
        char *str = current->data;
        if (strstr(str, searchterm) != NULL) 
        {
            // Add highlight 
            //! BEWARE the highlight plays with the string 
            // so i just removed it
            ListNode_AddNode(&res, str);
        }
        current = current->next;
    }

    return res; // NULL if nothing is found 
    // you see big brain
}

