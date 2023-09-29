#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main (void)
{
    int N;
    int K;

    cin >> N;
    cin >> K;

    vector <int> goods;

    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        goods.push_back(tmp + 1);
    }

    // Если суммарно всё не помещается в коробки - сразу финиш
    if(N > (K * 2))
    {
        cout << "\nNO\n";
    } 
    else
    {    
        int find_element = 0;
        int elements_cnt = 0;

        // Перебираем типы и считаем сколько штук каждого, если больше 2 - No
        do
        {
            find_element = 0;
            elements_cnt = 0;
            for (int i = 0; i < N; i++)
            {
                int tmp = goods[i];
                if (find_element == 0 && goods[i] != 0)
                {
                    find_element = goods[i];
                    goods[i] = 0;
                    elements_cnt++;
                }
                else if (find_element == goods[i] && find_element > 0 && goods[i] > 0)
                {
                    elements_cnt++;
                    goods[i] = 0;
                }
                if(elements_cnt > 2)
                {
                    // Какого-то элемента больше 2 единиц - вывод и find_element = 0 чтобы выйти из внешнего цикла
                    cout << "NO\n";
                    find_element = 0;
                    // Выходим из for
                    break;
                }
            }
        } while (find_element != 0);
        if (elements_cnt <= 2) cout << "YES\n";
    }
    
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}