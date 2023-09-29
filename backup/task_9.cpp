#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

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

void task_func(void)
{
    int N;
    cin >> N;
    uint16_t find_mask = 0b1111111111;

    if (N == 0)
    {
        cout << "\nINSOMNIA\n";
        return;
    }

    for (int i = 1; i < 30; i++)
    {
        find_mask = find_numbers(find_mask, N*i);
        if (find_mask == 0)
        {
            cout << "\n" << N*i << "\n";
            return;
        }
    }

    cout << "\nINSOMNIA\n";
    return;
}

int main (void)
{
    task_func();
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
