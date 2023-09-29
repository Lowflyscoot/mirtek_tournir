#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector <int32_t> find_moves (int32_t steps_down, int32_t steps_right, int bits_num)
{
    int32_t start = 0;
    for (int i = 0; i < bits_num; i++)
    {
        if (i >= steps_right)
        {
            start |= 1 << i;
        }
    }
    vector <int32_t> v_result;
    
    int j = 0;
    
    if (start == 0)
    {
        v_result.push_back(start);
        return v_result;
    }

    while (start > 0)
    {
        int tmp_cnt = 0;
        for (int i = 0; i < bits_num; i++)
        {
            // Считаем единички в очередном числе
            if ((start & (1 << i)) != 0) tmp_cnt++;
            if (tmp_cnt > steps_down) break;
        }
        if (tmp_cnt == steps_down)
        {
            v_result.push_back(start);
        }
        start--;
    }

    return v_result;
}

int run_field (vector <vector<int8_t>> field, int32_t move, int steps_num)
{
    int h = 0;
    int v = 0;
    int money_summ = 0;

    money_summ += field[h][v];
    for (int i = 0; i < steps_num; i++)
    {
        if ((move & (1 << i)) != 0) v++;
        else h++;
        int price = field[v][h];
        money_summ += price;
    }
    return money_summ;
}

void task_func(void)
{
    int steps_down;
    int steps_right;
    int width;
    int height;
    cin >> width;
    steps_right = width - 1;
    cin >> height;
    steps_down = height - 1;

    vector <vector<int8_t>> field;
    field.resize(height);
    for (int i = 0; i < height; i++)
    {
        field[i].resize(width);
        for (int j = 0; j < width; j++)
        {
            int tmp;
            cin >> tmp;
            field[i][j] = tmp;
        }
    }

    vector <int32_t> v_moves = find_moves(steps_down, steps_right, steps_right+steps_down);

    for (auto move:v_moves)
    {
        int summ = run_field(field, move, steps_right+steps_down);
        if (summ == 0)
        {
            printf("YES\n");
            return;
        }
    }
    printf("NO\n");
    return;
}

int main (void)
{
    task_func();
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
