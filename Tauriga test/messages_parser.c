#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "crc32.h"
#include "singly_linked_list.h"
#include "dynamic_array.h"

#define MIN(x,y) (x < y ? x:y)
#define MAX(x,y) (x > y ? x:y)

typedef enum {
    UNKNOWN = 0,
    MESSAGE = 1,
    MASK = 2
} input_type_t;

typedef struct {
    list_t *another_message;
    list_t *another_mask;
    size_t pair_number;
    size_t pair_counter;
} counters_t;

typedef struct {
    uint8_t type;
    size_t length;
    size_t final_length;
    uint8_t* data;
    uint32_t crc32;
} message_t;

typedef struct {
    char input_buf [258];
} buffers_t;

uint32_t mask_parsing (d_array_t *item, size_t position);
uint8_t pack_byte (d_array_t *item);
message_t *message_parsing (d_array_t *item, size_t position);
uint32_t mask_parsing (d_array_t *item, size_t position);
uint32_t mask_parsing (d_array_t *item, size_t position);

// Преобразует ascii символ в половину байта
uint8_t ascii_to_half_byte(const uint8_t symbol_code)
{
    if (symbol_code >= 0x41 && symbol_code <= 0x46)
    {
        return (symbol_code - 0x41 + 0x0A);
    }
    else if (symbol_code >= 0x30 && symbol_code <= 0x39)
    {
        return (symbol_code - 0x30);
    }
}

// Преобразует два идущих последовательно символа ввода в байт
uint8_t pack_byte (d_array_t *item)
{
    uint8_t result_byte = 0;
    result_byte = ascii_to_half_byte(get_array_element_with_shift(item)) << 4;
    result_byte |= ascii_to_half_byte(get_array_element_with_shift(item));
    return result_byte;
}

// Парсинг сообщения
message_t *message_parsing (d_array_t *item, size_t position){
    message_t *current_message = malloc(sizeof(message_t));

    uint8_t array[20] = {};
    // memcpy(array, item->array, 24);

    set_pointer_by_position(item, position);

    // Забираем из сообщения тип
    current_message->type = pack_byte(item);
    // Забираем из сообщения длину поля данных
    current_message->length = pack_byte(item);

    // Вычисляем итоговую длину массива данных, если исходная не кратная 4
    current_message->final_length = current_message->length;
    if (current_message->final_length % 4)
    {
        current_message->final_length += 4 - (current_message->final_length % 4);
    }

    // Выделяем память под данные
    uint32_t *data_pointer = malloc(sizeof(int*) * current_message->length);
    uint32_t *data_start = data_pointer;
    uint32_t tmp;
    
    // Сохраняем сначала реальные данные, а потом оставляем нулями остаток если он есть
    for (int i = 0; i < (current_message->final_length / 4); i++)
    {
        *data_pointer = 0;
        for (int j = 0; j < 4; j++)
        {
            if (((i * 4) + j) >= current_message->length) break;
            *data_pointer |= (uint32_t)pack_byte(item) << (24 - j * 8);
        }
        data_pointer++;
    }
    current_message->data = (uint8_t*)data_start;
    memcpy(array, current_message->data, 16);
    

    // Сохраняем CRC32
    current_message->crc32 = 0;
    for (int i = 0; i < 4; i++)
    {
        current_message->crc32 |= (pack_byte(item) << (24 - i * 8));
    }

    return current_message;
}


// Парсинг маски из ввода
uint32_t mask_parsing (d_array_t *item, size_t position){
    set_pointer_by_position(item, position);
    uint32_t result_mask = 0;
    uint8_t byte = 0;

    uint8_t array[2] = {};
    memcpy(array, item->array_pointer, 2);

    // Сохраняем маску
    for (int i = 0; i < 4; i++)
    {
        memcpy(array, item->array_pointer, 2);
        byte = pack_byte(item);
        result_mask |= (byte << (24 - i * 8));
    }

    return result_mask;
}


// Наложение одной маски на одно сообщение с генерацией нового сообщения
message_t *mask_overlay (message_t *recieved_message, uint32_t mask)
{
    // uint32_t array[20] = {};
    // memcpy(array, recieved_message->data, 12);
    message_t *new_message = malloc(sizeof(message_t));
    // Вывод данных в динамический массив для редактирования
    uint32_t *process_data = malloc(sizeof(uint32_t) * recieved_message->final_length);
    uint32_t *process_data_pointer = process_data;
    memcpy(process_data, recieved_message->data, recieved_message->final_length);
    // Инициализируем поля нового сообщения и выделяем под него память
    new_message->type = recieved_message->type;
    new_message->final_length = recieved_message->final_length;
    new_message->length = recieved_message->length;
    new_message->data = malloc(sizeof(uint32_t) * recieved_message->final_length);

    uint32_t temp;
    for (int i = 0; i < (recieved_message->final_length); i++)
    {
        temp = *process_data_pointer & mask;
        *process_data_pointer = *process_data_pointer & mask;
        process_data_pointer++;
    }

    uint32_t CRC32 = 0xFFFFFFFFull;
    CRC32 = crc32c(CRC32, new_message->type);
    CRC32 = crc32c(CRC32, new_message->final_length);

    uint8_t byte_block[4] = {};
    for (int i = 0; i < (recieved_message->final_length / 4); i++)
    {
        memcpy(byte_block, &process_data[i], 4);
        for (int j = 0; j < 4; j++)
        {
            CRC32 = crc32c(CRC32, byte_block[3 - j]);
        }
    }

    new_message->crc32 = CRC32;

    new_message->data = (uint8_t*)process_data;
    
    return new_message;
}

// Вывод совокупности обоих сообщений в файл
void print_message_to_file (message_t *old_message, message_t *new_message, FILE *target_file)
{
    uint32_t *data_pointer = NULL;
    
    fprintf(target_file, "Message type: %d\n", old_message->type);
    fprintf(target_file, "Initial message length: %d\n", old_message->length);
    fprintf(target_file, "Initial message data bytes: ");

    data_pointer = (uint32_t*)old_message->data;
    for (int i = 0; i < (old_message->length / 4); i++)
    {
        fprintf(target_file, "%08X ", *data_pointer);
        data_pointer++;
    }

    int remaining_bytes = old_message->length % 4;
    uint8_t remaining_part [4] = {((uint8_t*)data_pointer)[3], ((uint8_t*)data_pointer)[2], ((uint8_t*)data_pointer)[1], ((uint8_t*)data_pointer)[0]};
    if (remaining_bytes > 0) {
        uint8_t *byte_pointer = (uint8_t*)data_pointer;
        for (int i = 0; i < remaining_bytes; i++) {
            fprintf(target_file, "%02X", remaining_part[i]);
            byte_pointer++;
        }
    }

    fprintf(target_file, "\nInitial CRC-32: ");
    fprintf(target_file, "0x%08x\n", old_message->crc32);

    fprintf(target_file, "Modified message length: %d\n", new_message->final_length);
    fprintf(target_file, "Modified message data bytes with mask: ");

    data_pointer = (uint32_t*)new_message->data;
    for (int i = 0; i < (new_message->final_length / 4); i++)
    {
        fprintf(target_file, "%08X ", *data_pointer);
        data_pointer++;
    }

    fprintf(target_file, "\nModified CRC-32: ");
    fprintf(target_file, "0x%08x\n\n", new_message->crc32);
}

int main (void)
{
    // Открыть файл ввода
    FILE *input_file;
    input_file = fopen("input.txt", "r");
    // Открыть файл вывода на запись
    FILE *output_file;
    output_file = fopen("output.txt", "a");

    // Хранилище обрабатываемого символа
    char symbol;
    
    // Собираем весь ввод в динамический массив
    d_array_t *d_array_input = init_array(10);
    do {
        symbol = fgetc(input_file);
        add_element(d_array_input, symbol);
    } while (symbol != EOF);
    
    counters_t counters = {NULL, NULL, 0, 0};

    counters.pair_number = MIN(count_anchors(d_array_input, "mess="), count_anchors(d_array_input, "mask="));
    uint32_t mask = 0;

    size_t array_mess_position = 0;
    size_t array_mask_position = 0;
    message_t *new_message = NULL;
    message_t *old_mess = NULL;
    message_t *new_mess = NULL;
    uint32_t array[20] = {};
    // Проходим по каждой паре
    for (int i = 0; i < counters.pair_number; i++)
    {
        // Для каждого анкора ищем очередную позицию
        array_mess_position = get_anchor_position(d_array_input, "mess=", array_mess_position);
        // По позиции парсим сообщение и сохраняем его в выделенную область
        old_mess = message_parsing(d_array_input, array_mess_position);
        memcpy(array, old_mess->data, 20);
        // Находим ближайшую маску
        array_mask_position = get_anchor_position(d_array_input, "mask=", array_mask_position);
        // Парсим маску
        mask = mask_parsing(d_array_input, array_mask_position);
        // Накладываем маску на исходное сообщение и формируем новое
        new_mess = mask_overlay(old_mess, mask);
        // Выводим в файл результаты
        print_message_to_file(old_mess, new_mess, output_file);
        // Освобождаем память
        free(old_mess->data);
        free(old_mess);
        free(new_mess->data);
        free(new_mess);
    }

    // uint32_t crc_table [256];
    // make_crc_table(crc_table);
    // for (int i = 0; i < 256; i++)
    // {
    //     fprintf(output_file, "%08X ", crc_table[i]);
    //     if (i % 8 == 7) fprintf(output_file, "\n");
    // }

    // Освобождаем память
    free(d_array_input);
}