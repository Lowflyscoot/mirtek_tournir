#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Проверка, можно ли прочитать заданное число
bool chech_readble(uint16_t hour, uint16_t min)
{
    char symb;
    string tmp_string = "";
    size_t position = 0;

    string s_unreadle_numbers = "34679";
    // Проходим часы до 4 знака если он есть
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

int main (void)
{
    uint16_t d_hour_format = 0;
    uint16_t d_minute_format = 0; 
    uint16_t d_hour = 0;
    uint16_t d_min = 0;

    string tmp_str; 

    cin >> d_hour_format;
    cin >> d_minute_format;

    cin >> tmp_str;

    // Парсинг принятой строки времени
    for (auto symb:tmp_str)
    {
        if (symb != ':')
        {
            tmp_str += symb;
        }
        else
        {
            d_hour += stoi(tmp_str);
            tmp_str = "";
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
        // Если нечитаемое - проматываем время вперёд на минуту
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

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}