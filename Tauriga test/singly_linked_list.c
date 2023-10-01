#include "singly_linked_list.h"

	/* Counts the number of items in a list.
	 */
int count_list_items(const list_t *head) {
    int num_of_elements = 1;
    list_t *next_element = head->next;
    while (next_element)
    {
        next_element = next_element->next;
        num_of_elements++;
    }
    return num_of_elements;
}

	/* Getting element inside the list by index.
	 */
list_t *get_item_by_index(list_t *head, const int index) {
    int number_of_element = 0;
    list_t *next_element = head;
    while (next_element)
    {
        if (number_of_element == index)
        {
            return next_element;
        }
        next_element = next_element->next;
        number_of_element++;
    }
    return NULL;
}

	/* Getting element's data inside the list by index.
	 */
int get_data_by_index(list_t *head, const int index) {
    int number_of_element = 0;
    list_t *next_element = head;
    while (next_element)
    {
        if (number_of_element == index)
        {
            return next_element->data;
        }
        next_element = next_element->next;
        number_of_element++;
    }
    return 0;
}

    /* Inserts a new list item after the one specified as the argument.
	 */
void insert_next_to_list(list_t *item, int data) {
    if (!item)
    {
        item = init_list(data);
    }

    if (item->next)
	{
        list_t *old_next_element = item->next;
        item->next = malloc(sizeof(list_t));
        item->next->next = old_next_element;
        item->next->data = data;    
	}
    else
    {
        item->next = malloc(sizeof(list_t));
        item->next->data = data;    
        item->next->next = NULL;
    }
}

list_t *init_list(int data)
{
    list_t *item = malloc(sizeof(list_t));
    item->next = NULL;
    item->data = data;
    return item;
}

    /* Added element to end of list. Returns pointer to next element
	 */
list_t *add_to_list_end(list_t *item, int data) {
    if (!item)
    {
        item = init_list(data);
        item->data = data;
        item->next = NULL;
        return item;
    }

    list_t *current_element = item;
    while (current_element->next)
    {
        current_element = current_element->next;
    }
    current_element->next = malloc(sizeof(list_t));
    current_element->next->data = data;
    current_element->next->next = NULL;
    return current_element->next;
}

    /* Removes an item following the one specificed as the argument.
	 */
void remove_next_from_list(list_t *item) {
    if (item->next) {
        list_t* allocated_addr = item->next;
        item->next = item->next->next;
        free(allocated_addr);
    }
}

	/* Returns item data as text.
	 */
char *get_item_data(const list_t *list)
{
	char *buf = (char*)malloc(count_list_items(list));
	sprintf(buf, "%d", list->data);
	return buf;
}


void free_all_list (list_t *list)
{
    while (list->next)
    {
        remove_next_from_list(list);
    }
    free(list);
}



list_t *get_item_after_anchor(const list_t *list, char *anchor)
{
    int anchor_len = strlen(anchor) + 1;
    char *found_part = malloc(anchor_len);

    int number_of_element = 0;
    list_t *current_element = list;
    list_t *next_element = list;

    char tmp1 [10] = {};
    char tmp2 [10] = {};

    list_t *result = NULL;

    while (current_element)
    {
        next_element = current_element;
        for (int i = 0; i < (anchor_len - 1); i++)
        {
            found_part[i] = (char)next_element->data;

            next_element = next_element->next;
            if (next_element == NULL)
            {
                break;
            }
        }
        found_part[anchor_len - 1] = '\0';

        memcpy(tmp1, found_part, 10);
        memcpy(tmp2, anchor, 10);

        if (strcmp(found_part, anchor) == 0)
        {
            result = next_element;
            break;
        }
        // if (number_of_element == index)
        // {
        //     return next_element->data;
        // }
        current_element = current_element->next;
        number_of_element++;
    }
    free(found_part);
    return result;
    // return 0;
}