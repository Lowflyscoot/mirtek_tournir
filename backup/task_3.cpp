#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

void task_func(void)
{
    vector <int> kuski;
    vector <int> jurii_stuff;
    vector <int> anton_stuff;
    int jurii_summ = 0;
    int anton_summ = 0;
    int num = 0;
    int metal = 0;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> metal;
        jurii_summ += metal;
        kuski.push_back(metal);
    }
    sort(kuski.begin(), kuski.end());

    bool complete = false;

    for (auto kusok:kuski)
    {
        if (complete == false)
        {
            jurii_summ -= kusok;
            anton_summ += kusok;
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
            jurii_stuff.push_back(kusok);
        }
    }

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
        printf("\nIMPOSSIBLE\n");
    }
    return;
}

int main (void)
{
    task_func();
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
