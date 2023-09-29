#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Функция для поиска всех возможных проходов
vector <int32_t> find_moves (int32_t steps_down, int32_t steps_right, int bits_num)
{
    int32_t start = 0;

    // Формируем последовательность с которой начинаем искать, где единицы - шаг вниз, нули - шаг вправо
    for (int i = 0; i < bits_num; i++)
    {
        if (i >= steps_right)
        {
            start |= 1 << i;
        }
    }
    vector <int32_t> v_result;
    
    int j = 0;
    
    // Сохраняем нулевую на случай если идти только направо
    if (start == 0)
    {
        v_result.push_back(start);
        return v_result;
    }

    while (start > 0)
    {
        int tmp_cnt = 0;
        // Перебираем все числа и проверяем в каких из них нужное соотношение шагов
        for (int i = 0; i < bits_num; i++)
        {
            // Считаем единички в очередном числе
            if ((start & (1 << i)) != 0) tmp_cnt++;
            if (tmp_cnt > steps_down) break;
        }
        // Если правильное - сохраняем алгоритм
        if (tmp_cnt == steps_down)
        {
            v_result.push_back(start);
        }
        // Следующее число
        start--;
    }

    return v_result;
}

// Проход лабиринта с возвратом набранной суммы монет
int run_field (vector <vector<int8_t>> field, int32_t move, int steps_num)
{
    int h = 0;
    int v = 0;
    int money_summ = 0;

    // Учитываем стартовую клетку
    money_summ += field[h][v];
    for (int i = 0; i < steps_num; i++)
    {
        // На 1 ходим вниз, на 0 вправо
        if ((move & (1 << i)) != 0) v++;
        else h++;
        int price = field[v][h];
        money_summ += price;
    }
    return money_summ;
}

int main (void)
{
    int steps_down;
    int steps_right;
    int width;
    int height;
    // Вводим параметры поля
    cin >> width;
    steps_right = width - 1;
    cin >> height;
    steps_down = height - 1;

    // Вводим поле
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

    // Находим алгоритмы проходов для данной конфигурации
    vector <int32_t> v_moves = find_moves(steps_down, steps_right, steps_right+steps_down);

    // Проходим варианты и ищем максимальную сумму
    int max_money = 0;
    for (auto move:v_moves)
    {
        int summ = run_field(field, move, steps_right+steps_down);
        if (summ > max_money) max_money = summ;
    }
    printf("%i\n", max_money);
    
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}
