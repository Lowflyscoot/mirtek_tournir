#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main (void)
{
    // Общий список
    vector <int> kuski;
    // Металлолом Юрия и Антона, только чтобы восстановить у кого что было
    vector <int> jurii_stuff;
    vector <int> anton_stuff;
    // Рабочие суммы нагрузок
    int jurii_summ = 0;
    int anton_summ = 0;
    // Общее число кусков
    int num = 0;
    // Временная переменная
    int metal = 0;

    // Вводим количество металлоломин и всё грузим на Юрия
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> metal;
        jurii_summ += metal;
        kuski.push_back(metal);
    }
    // Сортируем всё по возрастанию
    sort(kuski.begin(), kuski.end());

    bool complete = false;

    // Перекладываем по куску от Юрия к Антону и проверяем, не установилось ли соотношение с обоих сторон
    for (auto kusok:kuski)
    {
        if (complete == false)
        {
            jurii_summ -= kusok;
            anton_summ += kusok;
            // Так как раньше по векторам не раскладывали - кладём Антону всё что перекладываем из суммы Юрия
            anton_stuff.push_back(kusok);
            float tmp1 = (float)jurii_summ / (float)anton_summ;
            float tmp2 = (float)anton_summ / (float)jurii_summ;
            if ((float)jurii_summ / (float)anton_summ <= 1.5 && (float)anton_summ / (float)jurii_summ <= 1.5)
            {
                complete = true;
            }
        }
        else
        {
            // Всё остальное после распределения достаётся Юрию
            jurii_stuff.push_back(kusok);
        }
    }

    // Если соотношение было найдено - вывод результата или impossible
    if (complete == true)
    {
        printf("%i:", jurii_summ);
        for (auto kusok:jurii_stuff)
        {
            printf(" %i", kusok);
        }
        printf("\n");
        printf("%i:", anton_summ);
        for (auto kusok:anton_stuff)
        {
            printf(" %i", kusok);
        }
        printf("\n");
    }
    else
    {
        printf("IMPOSSIBLE\n");
    }
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
