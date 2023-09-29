#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Проверка, можно ли прочитать заданное число
bool chech_readble(uint16_t hour, uint16_t min)
{
    char symb;
    string tmp_string = "";
    size_t position = 0;

    string s_unreadle_numbers = "34679";
    // Проходим часы проходим до 4 знака если он есть
    for (int i = 0; i < 4; i++)
    {
        if (hour == 0 && i >= 2) break;

        // Если найдено нечитаемое число - возвращаем False
        symb = hour % 10 + 0x30;
        if (s_unreadle_numbers.find(symb) != string::npos) 
        {
            position = s_unreadle_numbers.find(symb);
            return false;
        }

        // Срезаем разряд и чистим строку после каждого прохода
        hour /= 10;
        tmp_string = "";
    }

    // Аналогично для минут
    for (int i = 0; i < 2; i++)
    {
        // Получаем младший разряд, преобразуем в символ для поиска
        symb = min % 10 + 0x30;
        // Если найдено нечитаемое число - возвращаем False
        if (s_unreadle_numbers.find(symb) != string::npos) return false;
    }

    // Если нечитаемых символов не нашли - число читаемое
    return true;
}

string task_func(string str)
{
    uint16_t d_hour_format = 0;
    uint16_t d_minute_format = 0; 
    uint16_t d_hour = 0;
    uint16_t d_min = 0;

    uint8_t step = 0;

    string tmp_str; 

    // Парсинг принятой строки
    for (auto symb:str)
    {
        if (symb != ' ' && symb != ':')
        {
            tmp_str += symb;
        }
        else
        {
            switch (step)
            {
                case 0:
                    d_hour_format += stoi(tmp_str);
                    break;
                case 1:
                    d_minute_format += stoi(tmp_str);
                    break;
                case 2:
                    d_hour += stoi(tmp_str);
                    break;
                default:
                    break;
            }
            tmp_str = "";
            step++;
        }
    }
    d_min += stoi(tmp_str);

    // Ходим максимум целые сутки по заданному формату
    for (int i = 0; i < (d_hour_format*d_minute_format + d_minute_format); i++)
    {
        // Выходим из цикла, как только нашли читаемое в зеркале число
        if (chech_readble(d_hour, d_min) == true)
        {
            break;
        }
        // Если нечитаемое - проматываем время вперёд
        d_min++;
        if (d_min == d_minute_format)
        {
            d_min = 0;
            d_hour++;
            if (d_hour == d_hour_format)
            {
                d_hour = 0;
            }
        }
    }
    // Вывод результата
    printf("%02d:%02d", d_hour, d_min);
}

int main (void)
{
    task_func("90 80 52:26");
}