#include <iostream>

int ObisCodeCheck (int* bufer, char* checking_obis_code)
{
    int i = 0;
    int j = 5;
    int k = 0;
    int factor = 1;
    int frame = 0;
    int or_bytes [10] = {};

    // Доходим до конца строки
    for (i = 0; i <= 23; i++)
    {
        if (checking_obis_code[i] == 0) break;
        if (i == 23) return 0;
    }

    for (i; i > 0; i--)
    {
        if (checking_obis_code[i - 1] >= 0x30 && checking_obis_code[i - 1] <= 0x39)
        {
            if (factor > 100) return 0;
            frame += (checking_obis_code[i - 1] - 0x30) * factor;
            factor *= 10;
            if (i > 1) continue;
        }
        if (checking_obis_code[i - 1] == '.' || i == 1) //|| i == 1
        {
            // Если не было вариантов для "или" - то при несовпадении прерываемся
            if (bufer[j] != frame && k == 0) return 0;
            // Если варианты были - надо их перебрать
            else if (k > 0)
            {
                or_bytes[k] = frame;
                k++;
                for (k; k > 0; k--)
                {
                // Если нашли хотя бы одно совпадение - прерываем цикл
                if (or_bytes[k - 1] == bufer[j]) break;
                }
                // Если до конца так и не нашли - значит код не бьётся
                if (or_bytes[k - 1] != bufer[j]) return 0;
            }
            frame = 0;
            factor = 1;
            k = 0;
            if (j > 0) j--;
        }
        // Через слеш - список вариантов одного байта
        else if (checking_obis_code[i - 1] == '/')
        {
            or_bytes[k] = frame;
            frame = 0;
            factor = 1;
            k++;
            if (k > 9) return 0;
        }
        else if (checking_obis_code[i - 1] == 'x' || checking_obis_code[i - 1] == 'X')
        {
            while (checking_obis_code[i - 1] != '.' && i > 0) i--;
            j--;
            frame = 0;
            factor = 1;
            k = 0;
        }
    }
    if (j == 0 && i == 0) return 1;
    else return 0;
}

int main (void)
{
    int array [6] = {0x00, 0x00, 0x00, 0x08, 0x05, 0xFF};
    int result = 0;
    result = ObisCodeCheck(array, "1.0.0.8.5/1/2/3/4.255");
    if (result == 1) std::cout << "correct";
    if (result == 0) std::cout << "incorrect";
}