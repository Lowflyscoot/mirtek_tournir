#include "dynamic_array.h"

d_array_t *check_length (d_array_t *item)
{
    if (item->array_pointer > (item->array + item->size))
    {
        reset_pointer(item);
    }
    if (item->used_memory >= item->size)
    {
        size_t pointer_shift = item->array_pointer - item->array;
        uint8_t *temporary_array = malloc(item->size);
        memcpy(temporary_array, item->array, item->size);
        free (item->array);

        item->array = malloc(item->size + 10);
        memcpy(item->array, temporary_array, item->size);
        item->size += 10;
        item->array_pointer = item->array + pointer_shift;
    }
    return item;
}

d_array_t *init_array (size_t size)
{
    d_array_t *dynamic_array = malloc(sizeof(d_array_t));
    dynamic_array->array = malloc(size);
    dynamic_array->array_pointer = dynamic_array->array;
    dynamic_array->size = size;
    dynamic_array->used_memory = 0;
}

void add_element (d_array_t *array, uint8_t byte)
{
    array = check_length(array);
    *array->array_pointer = byte; // Corrected line
    array->array_pointer++;
    array->used_memory++;
}

void reset_pointer(d_array_t *array)
{
    array->array_pointer = array->array;
}

void set_pointer_by_position(d_array_t *array, size_t position)
{
    array->array_pointer = array->array + position;
    array = check_length(array);
}

uint8_t get_array_element_with_shift(d_array_t *array)
{
    uint8_t result = *array->array_pointer++;
    array = check_length(array);
    return result;
}

// void set_arra

size_t get_anchor_position(d_array_t *array, char *anchor, size_t start_pos)
{
    int anchor_len = strlen(anchor) + 1;
    char *found_part = malloc(anchor_len);
    uint8_t *pointer = array->array;
    size_t result = 0;

    for (int i = start_pos; i < (array->size - anchor_len); i++)
    {
        memcpy(found_part, &pointer[i], anchor_len);
        found_part[anchor_len - 1] = '\0';

        if (strcmp(found_part, anchor) == 0)
        {
            result = i + anchor_len - 1;
            break;
        }
    }

    free(found_part);
    return result;
}

size_t count_anchors(d_array_t *array, char *anchor)
{
    int anchor_len = strlen(anchor) + 1;
    char *found_part = malloc(anchor_len);
    uint8_t *pointer = array->array;
    size_t result = 0;

    for (int i = 0; i < (array->size - anchor_len); i++)
    {
        memcpy(found_part, &pointer[i], anchor_len);
        found_part[anchor_len - 1] = '\0';

        if (strcmp(found_part, anchor) == 0)
        {
            result++;
        }
    }

    free(found_part);
    return result;
}