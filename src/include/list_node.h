#ifndef FCD_LIST_NODE_H
#define FCD_LIST_NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "strstuff.h"

/**
 * @brief Singly linked list
 *
 */
typedef struct list_node
{
    char *data;
    
    // pointer to the last node in the list so we can append to the list
    struct list_node *last;

    struct list_node *next;
} ListNode;

/**
 * @brief Adds a node to the beginning of the linked list
 *
 * @param head
 * @param data
 * @return ListNode*
 */
ListNode *ListNode_AddNode(ListNode **head, const char *data);

/**
 * @brief Adds a node to the end of the linked list
 *
 * @param head
 * @param data
 * @return ListNode*
 */
ListNode *ListNode_AppendNode(ListNode **head, const char *data);

/**
 * @brief Removes all nodes from the linked list
 * 
 * @param head
 */
void ListNode_RemoveAll(ListNode *head);

/**
 * @brief Prints all nodes in the linked list
 *
 * @param head
 */
void ListNode_PrintAll(ListNode *head);

/**
 * @brief Search for a substring in any list node
 *
 * @param head
 * @param searchterm 
 * @return ListNode* (A list node object that contains all the search results)
 */
ListNode *ListNode_Search(ListNode *head, const char *searchterm);

#endif
