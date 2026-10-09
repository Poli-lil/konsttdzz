#include <iostream>
#include <fstream>
#include "Reservoir.h"

using namespace std;

void addReservoir(Reservoir*& arr, int& size)
{
    Reservoir* newArr = new Reservoir[size + 1];

    for (int i = 0; i < size; i++)
        newArr[i] = arr[i];

    char name[100];
    int type;
    double width, length, depth;

    cout << "Введите название: ";
    cin.ignore();
    cin.getline(name, 100);

    cout << "Выберите тип:\n";
    cout << "0 - Море\n";
    cout << "1 - Озеро\n";
    cout << "2 - Река\n";
    cout << "3 - Пруд\n";
    cout << "4 - Бассейн\n";
    cout << "Ваш выбор: ";
    cin >> type;

    cout << "Введите ширину: ";
    cin >> width;

    cout << "Введите длину: ";
    cin >> length;

    cout << "Введите максимальную глубину: ";
    cin >> depth;

    newArr[size].setName(name);
    newArr[size].setType((ReservoirType)type);
    newArr[size].setWidth(width);
    newArr[size].setLength(length);
    newArr[size].setMaxDepth(depth);

    delete[] arr;

    arr = newArr;
    size++;

    cout << "Водоем добавлен!\n";
}

void deleteReservoir(Reservoir*& arr, int& size)
{
    if (size == 0)
    {
        cout << "Массив пуст!\n";
        return;
    }

    int index;

    cout << "Введите номер водоема для удаления: ";
    cin >> index;

    if (index < 0 || index >= size)
    {
        cout << "Неверный номер!\n";
        return;
    }

    Reservoir* newArr = new Reservoir[size - 1];

    int j = 0;

    for (int i = 0; i < size; i++)
    {
        if (i != index)
        {
            newArr[j] = arr[i];
            j++;
        }
    }

    delete[] arr;

    arr = newArr;
    size--;

    cout << "Водоем удален!\n";
}

void showAll(Reservoir* arr, int size)
{
    if (size == 0)
    {
        cout << "Массив пуст!\n";
        return;
    }

    for (int i = 0; i < size; i++)
    {
        cout << "\n===== Водоем #" << i << " =====\n";
        arr[i].show();
    }
}

void compareReservoirs(Reservoir* arr, int size)
{
    if (size < 2)
    {
        cout << "Нужно минимум 2 водоема!\n";
        return;
    }

    int first, second;

    cout << "Введите номер первого водоема: ";
    cin >> first;

    cout << "Введите номер второго водоема: ";
    cin >> second;

    if (first < 0 || first >= size ||
        second < 0 || second >= size)
    {
        cout << "Неверный номер!\n";
        return;
    }

    if (!arr[first].isSameType(arr[second]))
    {
        cout << "Водоемы относятся к разным типам!\n";
        return;
    }

    int result = arr[first].compareSurfaceArea(arr[second]);

    if (result == 1)
        cout << "Площадь первого водоема больше.\n";
    else if (result == -1)
        cout << "Площадь второго водоема больше.\n";
    else
        cout << "Площади водоемов одинаковые.\n";
}

void copyReservoir(Reservoir* arr, int size)
{
    if (size == 0)
    {
        cout << "Массив пуст!\n";
        return;
    }

    int index;

    cout << "Введите номер водоема для копирования: ";
    cin >> index;

    if (index < 0 || index >= size)
    {
        cout << "Неверный номер!\n";
        return;
    }

    Reservoir copy(arr[index]);

    cout << "\nКопия водоема:\n";
    copy.show();
}

void saveTextFile(Reservoir* arr, int size)
{
    ofstream file("reservoirs.txt");

    if (!file)
    {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    for (int i = 0; i < size; i++)
    {
        arr[i].saveText(file);
    }

    file.close();

    cout << "Данные записаны в reservoirs.txt\n";
}

void saveBinaryFile(Reservoir* arr, int size)
{
    ofstream file("reservoirs.bin", ios::binary);

    if (!file)
    {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    file.write((char*)&size, sizeof(size));

    for (int i = 0; i < size; i++)
    {
        arr[i].saveBinary(file);
    }

    file.close();

    cout << "Данные записаны в reservoirs.bin\n";
}

int main()
{
    Reservoir* reservoirs = nullptr;
    int size = 0;

    int choice;

    do
    {
        cout << "\n========== МЕНЮ ==========\n";
        cout << "1. Добавить водоем\n";
        cout << "2. Удалить водоем\n";
        cout << "3. Показать все водоемы\n";
        cout << "4. Сравнить водоемы\n";
        cout << "5. Скопировать водоем\n";
        cout << "6. Записать в текстовый файл\n";
        cout << "7. Записать в бинарный файл\n";
        cout << "0. Выход\n";
        cout << "===========================\n";

        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addReservoir(reservoirs, size);
            break;

        case 2:
            deleteReservoir(reservoirs, size);
            break;

        case 3:
            showAll(reservoirs, size);
            break;

        case 4:
            compareReservoirs(reservoirs, size);
            break;

        case 5:
            copyReservoir(reservoirs, size);
            break;

        case 6:
            saveTextFile(reservoirs, size);
            break;

        case 7:
            saveBinaryFile(reservoirs, size);
            break;

        case 0:
            cout << "Выход...\n";
            break;

        default:
            cout << "Неверный выбор!\n";
        }

    } while (choice != 0);

    delete[] reservoirs;

    return 0;
}