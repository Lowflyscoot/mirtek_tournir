#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int check_near_trees (vector <vector<char>> field, uint8_t R, uint8_t C, uint8_t i, uint8_t j)
{
    uint8_t count_of_neiboors = 0;
    if (j != 0 && field[i][j-1] == '^') count_of_neiboors++;
    if (j != (C - 1) && field[i][j+1] == '^') count_of_neiboors++;
    if (i != 0 && field[i-1][j] == '^') count_of_neiboors++;
    if (i != (R - 1) && field[i+1][j] == '^') count_of_neiboors++;
    return count_of_neiboors;
}

int main (void)
{
    // // Высота и ширина, указатель на один из параметров
    uint16_t d_params [2] = {0, 0};
    int cnt_planted_trees = 0;

    cin >> d_params[0];
    cin >> d_params[1];

    // Двумерный массив в виде вектора векторов char
    vector <vector<char>> field;
    field.resize(d_params[0]);
    // Вектор для хранения первоначальных позиций деревьев
    vector <int> v_trees;

    // Проходим по каждой строке
    for (int i = 0; i < d_params[0]; i++)
    {
        // Выделяем место
        field[i].resize(d_params[1]);
        
        for (int j = 0; j < d_params[1]; j++)
        {
            // Получаем символ
            char c_tmp;
            cin >> c_tmp;
            // Для начальных деревьев сразу сохраняем координаты
            if (c_tmp == '^') v_trees.push_back(((i << 4) & 0xF0) | (j & 0x0F));
            // Вместо пустых мест сразу высаживаем дерево
            if (c_tmp == '.') 
            {
                c_tmp = '^';
                cnt_planted_trees++;
            }
            // Сохраняем итоговый символ
            field[i][j] = c_tmp;
        }
    }

    // Удаление всех деревьев (кроме начальных), у которых не хватает соседей
    bool was_delete_of_tree;
    do
    {
        was_delete_of_tree = false;
        for (int i = 0; i < d_params[0]; i++)
        {
            for (int j = 0; j < d_params[1]; j++)
            {
                // Получаем в байте координату текущего тайла
                int coord = (((i << 4) & 0xF0) | (j & 0x0F));
                // Если среди сохранённых координат стартовых деревьев есть текущая координата или наступили на камень - пропускаем итерацию
                if (find(v_trees.begin(), v_trees.end(), coord) != v_trees.end() || field[i][j] == '#') continue;
                // В остальных случаях, находя дерево - проверяем его соседей и выкорчёвываем, если их меньше двух
                if (check_near_trees(field, d_params[0], d_params[1], i, j) < 2 &&  field[i][j] == '^')
                {
                    field[i][j] = '.';
                    was_delete_of_tree = true;
                    cnt_planted_trees--;
                }
            }
        }
    } while (was_delete_of_tree == true); // Повторяем пока не будет ни одного выкорчеванного дерева за проход

    // cout << "\n";
    if (cnt_planted_trees > 0)
    {
        for (auto vector:field)
        {
            for (auto symb:vector)
            {
                cout << symb << " ";
            }
            cout << "\n";
        }
    }
    else cout << "IMPOSSIBLE\n";

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
    system("pause");
#endif
}