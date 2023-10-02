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
    const uint8_t* data;
    uint32_t crc32;
} message_t;


typedef struct {
    char input_buf [258];
} buffers_t;

// // Функция для подсчёта количества анкоров в списке
// int count_anchors (list_t *list, char *anchor){
//     if (!list) return 0;

//     size_t result = 0;

//     // Пытаемся получить первый анкор
//     list_t *current_item = get_item_after_anchor(list, anchor);
    
//     // Проверяем нашёлся ли хотя бы 1 и ищем следующий
//     // в 1 проход при найденном анкоре результат в любом случае инкрементируется
//     // если за анкором не идёт символов - он недействительный
//     while (current_item) {
//         current_item = get_item_after_anchor(current_item, anchor);
//         result++;
//     }

//     return result;
// }

// Преобразует ascii символ в половину байта
uint8_t ascii_to_half_byte(const uint8_t symbol_code)
{
    if (symbol_code >= 0x65 && symbol_code <= 0x70)
    {
        return (symbol_code - 0x65 + 0x0A);
    }
    else if (symbol_code >= 0x30 && symbol_code <= 0x39)
    {
        return (symbol_code - 0x30);
    }
}

// Преобразует два идущих последовательно символа ввода в байт
uint8_t pack_byte (list_t *asccii_item)
{
    uint8_t result_byte = 0;
    result_byte = ascii_to_half_byte(asccii_item->data) << 4;
    result_byte |= ascii_to_half_byte(asccii_item->next->data);
    return result_byte;
}

// Парсинг сообщения
message_t *message_parsing (list_t *item){
    message_t *current_message = malloc(sizeof(message_t));
    list_t *current_item = item;

    // Забираем из сообщения тип
    current_message->type = pack_byte(current_item);
    if (!current_item->next->next || !current_item->next) return current_message;
    current_item = current_item->next->next;
    // Забираем из сообщения длину поля данных
    current_message->length = pack_byte(current_item);
    if (!current_item->next->next || !current_item->next) return current_message;
    current_item = current_item->next->next;

    // Вычисляем итоговую длину массива данных, если исходная не кратная 4
    current_message->final_length = current_message->length;
    if (current_message->final_length % 4)
    {
        current_message->final_length += 4 - (current_message->final_length % 4);
    }

    // Выделяем память под данные
    current_message->data = malloc(sizeof(int*) * current_message->length);
    uint32_t *data_pointer = current_message->data;
    unsigned __int32 tmp;
    // Сохраняем сначала реальные данные, а потом добиваем нулями остаток если он есть
    for (int i = 0; i < current_message->length; i++)
    {
        *data_pointer = 0;
        for (int j = 0; j < 4; j++)
        {
            if (((i * 4) + j) >= current_message->length) break;
            tmp = (__int32)pack_byte(current_item) << (24 - j * 8);
            *data_pointer |= (__int32)pack_byte(current_item) << (24 - j * 8);
            if (!current_item->next->next || !current_item->next) return current_message;
            current_item = current_item->next->next;
        }
        data_pointer++;
    }

    // Сохраняем CRC32
    current_message->crc32 = 0;
    for (int i = 0; i < 4; i++)
    {
        current_message->crc32 |= (pack_byte(current_item) << (24 - i * 8));
        if (!current_item->next->next || !current_item->next) return current_message;
        current_item = current_item->next->next;
    }

    return current_message;
}


void print_message_to_file (message_t *printing_message, FILE *target_file)
{
    fprintf(target_file, "Message type: %d\n", printing_message->type);
    fprintf(target_file, "Message length: %d\n", printing_message->length);
    fprintf(target_file, "Data: ");
    uint32_t *data_pointer = printing_message->data;
    for (int i = 0; i < (printing_message->final_length / 4); i++)
    {
        fprintf(target_file, "%08X ", *data_pointer);
        data_pointer++;
    }
    fprintf(target_file, "\nCRC: ");
    fprintf(target_file, "0x%08x\n\n", printing_message->crc32);
}

int main (void)
{
    // Открыть файл ввода
    FILE *input_file;
    input_file = fopen("input.txt", "r");
    // Открыть файл вывода на запись
    FILE *output_file;
    output_file = fopen("output.txt", "w+");

    // Хранилище обрабатываемого символа
    char symbol;
    
    // Собираем весь ввод в динамический массив
    d_array_t *d_array_input = init_array(10);
    do {
        symbol = fgetc(input_file);
        add_element(d_array_input, symbol);
    } while (symbol != EOF);
    
    uint8_t tmparray [100];
    memcpy(tmparray, d_array_input->array, 100);

    int temp2 = get_anchor_position(d_array_input, "mess=", 0);
    temp2 = count_anchors(d_array_input, "mess=");

    counters_t counters = {NULL, NULL, 0, 0};

    counters.pair_number = MIN(count_anchors(d_array_input, "mess="), count_anchors(d_array_input, "mask="));
}

// int main (void)
// {
//     // Создаём указатель на список, он будет проинициализирован при первой попытке добавления чего-либо
//     list_t *input_list = NULL;

//     // Открыть файл ввода
//     FILE *input_file;
//     input_file = fopen("input.txt", "r");
//     // Открыть файл вывода на запись
//     FILE *output_file;
//     output_file = fopen("output.txt", "w+");

//     // Хранилище обрабатываемого символа
//     char symbol;

//     // Вычитка из ввода всех символов подряд и сохранение их в динамическом массиве
//     // Первый символ, который инициализирует список, вычитываем вручную
//     input_list = init_list(fgetc(input_file));
//     do {
//         symbol = fgetc(input_file);
//         add_to_list_end(input_list, (int)symbol);
//     } while (symbol != EOF);

//     // Получаем длину данных
//     int length = count_list_items(input_list);

//     // Указатель на очередной элемент списка
//     list_t *current_item = input_list;

//     // Считаем сколько анкоров на сообщения и маски есть во вводе
//     counters_t counters = {NULL, NULL, 0, 0};

//     // Число пар равно минимальному из числа сообщений и масок
//     counters.pair_number = MIN(count_anchors(input_list, "mess="), count_anchors(input_list, "mask="));
    
//     counters.another_message = get_item_after_anchor(input_list, "mess=");
//     // counters.another_mask = get_item_after_anchor(input_list, "mess=");

//     // Выделяем память под все сообщения которые будут вычитываться
//     const message_t *messages_array = malloc(sizeof(message_t*) * counters.pair_number);

//     message_t *test_message = message_parsing(counters.another_message);

//     print_message_to_file(test_message, output_file);

//     // todo доработать и надыбать функцию расчёта срс которая будет принимать предыдущее срс

//     test_message->crc32 = gen_crc(test_message->data, test_message->final);

//     print_message_to_file(test_message, output_file);

//     // for (int i = 0; i < counters.pair_number; i++)
//     // {

//     // }


//     free_all_list(input_list);
//     free(messages_array);
//     free(test_message);
// }