#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Функция разбивает цисло на цифры и помечайт найденные цифры
uint16_t find_numbers (uint16_t find_mask, int number)
{
    do
    {
        int tmp;
        tmp = number % 10;
        find_mask &= ~(1 << tmp);
        number /= 10;
    } while (number != 0);
    return find_mask;
}

int main (void)
{
    int N;
    cin >> N;
    // Маска по 1 биту для каждого из 10 чисел
    uint16_t find_mask = 0b1111111111;

    // На ноль сразу бессонница
    if (N == 0)
    {
        cout << "INSOMNIA\n";
    }
    else
    {
        // 30 проходов и перебора чисел
        for (int i = 1; i < 30; i++)
        {
            // Перебираем число и редактируем маску в соответствии с найденными цифрами
            find_mask = find_numbers(find_mask, N*i);
            if (find_mask == 0)
            {
                cout << N*i << "\n";
                break;
            }
        }

        // Если за 30 проходов не нашли все цифры - БЕССОНИЦА
        if (find_mask != 0)
        {
            cout << "INSOMNIA\n";
        }
    }
    
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
