#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

void task_func(void)
{
    int N;
    cin >> N;

    vector <int> input;
    vector <vector<int>> lines;

    int max_level = 0;
    int neft_value = 0;

    for (int i = 0; i < N; i++)
    {
        int tmp = 0;
        cin >> tmp;
        if (tmp > max_level) max_level = tmp;
        input.push_back(tmp);
    }

    cout << "\n";

    lines.resize(max_level);

    for (int i = 0; i < max_level; i++)
    {
        lines[i].resize(N);
        int j = 0;
        for (auto collumn_high:input)
        {
            if ((i + 1) <= collumn_high)
            {
                lines[i][j] = 1;
            }
            else
            {
                lines[i][j] = 2;
                neft_value++;
            }
            j++;
        }
    }

    for (int i = 0; i < max_level; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (lines[i][j] == 2)
            {
                lines[i][j] = 0;
                neft_value--;
            }
            if (lines[i][j] == 1) break;
        }
        for (int j = N; j > 0; j--)
        {
            if (lines[i][j-1] == 2)
            {
                lines[i][j-1] = 0;
                neft_value--;
            }
            if (lines[i][j-1] == 1) break;
        }
    }

    float time_hour = (float)neft_value * 0.5;

    // for (auto line:lines)
    // {
    //     for (auto tile:line)
    //     {
    //         cout << tile << " ";
    //     }
    //     cout << "\n";
    // }
    printf("\n%0.1f\n", time_hour);
    cout << "\n";

    return;
}

int main (void)
{
    task_func();
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
