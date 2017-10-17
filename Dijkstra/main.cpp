//Система двусторонних дорог такова, что для любой пары городов можно указать соединяющий их путь. Найдите такой город, сумма расстояний от которого до остальных городов минимальна.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

// Главное меню
int Menu()
{
    cout << "---------------------------------------\n";
    cout << "                 МЕНЮ                  \n";
    cout << "---------------------------------------\n";
    cout << "1 - Загрузить текст из файла.\n";
    cout << "2 - Ввести текст в консоли.\n";
    cout << "---------------------------------------\n";
    int p;
    do {
        cin >> p;
        if ((p != 1) && (p != 2))
            cout << "Введенное значение неверно. Повторите ввод.\n";
    } while ((p != 1) && (p != 2));
    getchar();
    cout << "\n";
    return p;
}

// Ответ на вопрос (txt)
bool Question(const char *txt)
{
    char ans; // Переменная, содержащая ответ на вопрос
    cout << txt << endl;
    do {
        cin >> ans;
        if ((ans != 'N') && (ans != 'n') && (ans != 'Y') && (ans != 'y'))
            cout << "Введеное значение неверно. Повторите ввод.\n";
    } while ((ans != 'N') && (ans != 'n') && (ans != 'Y') && (ans != 'y'));
    getchar();
    if ((ans == 'Y') || (ans == 'y'))
        return true; // Если ответ положительный, то вернуть функции true
    else
        return false;
}

int **CreateMatrix(int n)
{
    int **Matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        Matrix[i] = new int[n];
    }
    
    for (int i = 0; i < n; i++) {
        Matrix[i][i] = 0;
        
    }
    return Matrix;
}

bool AddElem(int **Matr, int a, int i, int j)
{
    if (a < 0) return false;
    Matr[i][j] = a;
    Matr[j][i] = a;
    return true;
}

int main()
{
    setlocale(LC_ALL, "");
    int **Matrix;
    int SIZE;
    int m = Menu();
    switch (m) {
        case 1:
        {
            string str;
            cout << "Введите имя файла:\n";
            cin >> str;
            // Открытие введенного пользователем файла
            ifstream file(str);
            if (!file.good())
            {
                cout << "Не удается открыть файл.\n";
                return 0;
            }
            else
            {
                // Инициализация матрицы дорог
                file >> SIZE;
                Matrix = CreateMatrix(SIZE);
                bool ok = true;
                int i = 0, j = 0;
                while (i <SIZE - 1 && !file.eof() && ok)
                {
                    j = i + 1;
                    while (j < SIZE  && !file.eof() && ok)
                    {
                        int a;
                        file >> a;
                        ok = (AddElem(Matrix, a, i, j));
                        j++;
                    }
                    i++;
                }
                if (i < SIZE - 1)
                {
                    cout << "В файле недостаточно данных.\n" << endl;
                    ok = false;
                }
                file.close();
                if (!ok)
                {
                    return 0;
                }
            }
            break;
        }
        case 2:
        {
            // Инициализация матрицы дорог
            cout << "Введите количество городов:" << endl;
            cin >> SIZE;
            Matrix = CreateMatrix(SIZE);
            cout << "Введите длину дороги между городами:" << endl;
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i + 1; j < SIZE; j++)
                {
                    int a;
                    cout << i + 1 << " и " << j + 1 << ", если дороги нет, введите 0." << endl;
                    do
                    {
                        cin >> a;
                    } while (!AddElem(Matrix,a,i,j));
                    
                }
            }
            break;
        }
    }
    
    int d[SIZE]; // Минимальное расстояние
    int v[SIZE]; // Посещенные города
    int temp;
    int minindex, min;
    // Вывод матрицы дорог
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
    int Minimum=10000;
    int Gorod=0;
    for (int k = 0; k<SIZE; k++)
    {
        // Инициализация городов и расстояний
        for (int i = 0; i<SIZE; i++)
        {
            d[i] = 10000;
            v[i] = 1;
        }
        d[k] = 0;
        // Шаг алгоритма
        do {
            minindex = 10000;
            min = 10000;
            for (int i = 0; i<SIZE; i++)
            { // Если город ещё не обошли и вес меньше min
                if ((v[i] == 1) && (d[i]<min))
                { // Переприсваиваем значения
                    min = d[i];
                    minindex = i;
                }
            }
            // Добавляем найденный минимальный вес к текущему весу города и сравниваем с текущим минимальным весом города
            if (minindex != 10000)
            {
                for (int i = 0; i<SIZE; i++)
                {
                    if (Matrix[minindex][i] > 0)
                    {
                        temp = min + Matrix[minindex][i];
                        if (temp < d[i])
                            d[i] = temp;
                    }
                }
                v[minindex] = 0;
            }
        } while (minindex < 10000);
        // Сумма кратчайших расстояний до города
        int s=0;
        for (int i = 0; i<SIZE; i++)
            s=s+d[i];
        // Если это миниальное расстояние, то присваиваем
        if (s<Minimum)
        {
            Minimum=s;
            Gorod=k+1;
        }
        
    }
    cout << "Город - " << Gorod <<"\nСумма расстояний - " << Minimum <<"\n";
    getchar();
    return 0;
}

