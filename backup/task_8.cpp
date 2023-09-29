#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

bool check_passability (vector<int> way)
{
    int zero_cnt = 0;
    for (auto element:way)
    {
        if (element == 0)
        {
            zero_cnt++;
            if (zero_cnt > 3) return false;
        }
        else
        {
            zero_cnt = 0;
        }
    }
    return true;
}

void task_func(void)
{
    int num;
    cin >> num;

    const size_t length = num;
    vector<int> goods;

    // Принимаем на ввод массив
    for (int i = 0; i < num; i++)
    {
        int tmp = 0;
        cin >> tmp;
        goods.push_back(tmp);
    }

    // Промежуточный вектор для сортировки и вектор избранных элементов
    vector<int> goods_copy = goods;
    vector<int> selected_goods;
 
    selected_goods.resize(num);
    // Сортируем промежуточный вектор
    sort(goods_copy.begin(), goods_copy.end());

    // Идём по сортированному вектору, пропуская повторы
    int last_element = 0;
    for (auto sorted_good:goods_copy)
    {
        if (last_element == sorted_good && last_element != 0) continue;

        // Переносим одинаковые элементы с наименьшего к наибольшему в пустой массив, пока через них нельзя
        // будет сформировать выборку 3 и менее пропущенными коробками
        for (int i = 0; i < num; i++)
        {
            if (goods[i] == sorted_good) selected_goods[i] = goods[i];
        }
        if (check_passability(selected_goods) == true)
        {
            break;
        }

        last_element = sorted_good;
    }

    vector<int> way;
    int summ = 0;

    for (int i = 0; (i + 3) < num; i++)
    {
        int index = i;
        int minimal = 0;
        for (int j = 0; j < 4; j++)
        {
            if ((selected_goods[i + j] <= minimal || minimal == 0) && selected_goods[i + j] != 0)
            {
                minimal = selected_goods[i + j];
                index = i + j;
            }
        }
        way.push_back(selected_goods[index]);
        summ += selected_goods[index];
        i = index;
    }

    for (auto tmp:selected_goods)
    {
        cout << tmp << " ";
    }
    cout << "\n";
    for (auto tmp:way)
    {
        cout << tmp << " ";
    }
    cout << "\n" << summ << "\n";

    return;
}

int main (void)
{
    task_func();
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
