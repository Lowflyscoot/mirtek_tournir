#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef enum {
    UNKNOWN = 0,
    MESSAGE = 1,
    MASK = 2
} input_type_t;

typedef struct {
    int input_counter;
    int output_counter;
    int message_counter;
    int mask_counter;
} counters_t;

typedef struct buffers
{
    char input_buf [258];
    
};


int main (void)
{
    FILE *input_file;
    input_file = fopen("input.txt", "r");

    char input_buffer [100] = {};
    char message [100] = {};
    char mask [100] = {};
    char find_sign [5]= "";
    counters_t counters = {0, 0, 0, 0};
    int msg_pointer = 0;
    int msk_pointer = 0;
    int input_pointer = 0;
    input_type_t input_type;
    char symbol;
    do {
        symbol = fgetc(input_file);
        input_buffer[input_pointer] = symbol;
        if (input_pointer >= 4)
        {
            memcpy(find_sign, &input_buffer[input_pointer - 4], 5);
            find_sign[5] = 0;

            if (strcasecmp(find_sign, "mess=") == 0)
            {
                input_type = MESSAGE;
            }
            else if (strcmp(find_sign, "mask=") == 0)
            {
                input_type = MASK;
            }
            else
            {
                switch (input_type)
                {
                    case MESSAGE:
                        message[msg_pointer++] = symbol;
                        break;
                    case MASK:
                        mask[msk_pointer++] = symbol;
                        break;
                    default:
                        break;
                }
            }
        }
        // printf("%c ", symbol);
        input_pointer++;
    } while (symbol != EOF);
    input_pointer++;
}