#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H
#endif

typedef struct list_s
{
        struct list_s *next; /* NULL for the last item in a list */
        int data;
}
list_t;

list_t *init_list(int data);
int count_list_items(const list_t *head);
int get_data_by_index(list_t *head, const int index);
list_t *get_item_by_index(list_t *head, const int index);
void insert_next_to_list(list_t *item, int data);
list_t *add_to_list_end(list_t *item, int data);
void remove_next_from_list(list_t *item);
char *get_item_data(const list_t *list);
list_t *get_item_after_anchor(const list_t *list, char *anchor);