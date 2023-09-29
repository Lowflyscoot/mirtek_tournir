#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main (void)
{
    // Монеты отсортированны по ценности на единицу веса, пятаки убраны за неэффективностью
    int nominals [8] = {100, 50, 20, 25, 7, 2, 10, 1};
    float weights [8] = {29.7, 23.2, 15.7, 20.1, 6.0, 3.0, 19.4, 2.0};
    int nums[8] = {};

    int N;
    cin >> N;
    int summ = 0;
    float weight = 0.0;

    // Собираем сумму, двигаясь от большего номинала к меньшему и забивая сумму максимально крупными монетами, т.к. на общуюсумму они наиболее легкие
    // и отмечаем сколько каких взяли
    for (int i = 0; i < 8; i++)
    {
        if ((N - summ) >= nominals[i])
        {
            int tmp;
            tmp = (N - summ) / nominals[i];
            summ += nominals[i] * tmp;
            weight += weights[i] * (float)tmp;
            nums[i] += tmp;
        }
        if (N == summ)
        {
            cout << weight << "\n";
            for (int j = 0; j < 8; j++)
            {
                if (nums[j] > 0) printf("%i-%i ", nominals[j], nums[j]);
            }
            cout << "\n";
            break;
        }
    }
    
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
