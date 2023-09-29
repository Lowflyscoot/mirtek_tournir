#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

void task_func (void)
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

    if(N > (K * 2))
    {
        cout << "\nNO\n";
        return;
    } 
    
    int find_element = 0;
    int elements_cnt = 0;

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
                cout << "\nNO\n";
                return;
            }
        }
    } while (find_element != 0);
    cout << "\nYES\n";
    return;
}

int main (void)
{
    task_func();
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
