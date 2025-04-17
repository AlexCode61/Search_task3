#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <chrono>

int count_srav;
int iter;

// Заполение массива случайными числами
std::vector<int> createMassiv(int count) {
    int start = -100;
    int end = 100;

    std::vector<int> mas;

    for (int i = 0; i < count; i++) {
        int el = rand() % (end - start + 1);
        mas.push_back(el);
    }

    return mas;
}

// Вывод массива
void printMas(const std::vector<int> mas) {
    std::cout << std::endl;
    for (int element : mas) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Обычный линейный поиск
int linearSearch(const std::vector<int>& vec, int key) {
    count_srav = 0;
    iter = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        count_srav++;
        iter++;
        if (vec[i] == key) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int linearSearchWithBarrier(std::vector<int>& mas, int key) {
    count_srav = 0;
    iter = 0;

    mas.push_back(key);
    int i = 0;

    while (true) {
        count_srav++;
        iter++;
        if (mas[i] == key) {
            mas.pop_back();
            count_srav--;
            iter--;
            return (i == mas.size()) ? -1 : static_cast<int>(i);
        }
        i++;
    }
}

std::string spacesIndentation(int val, int length) {
    std::string str = std::to_string(val);
    int size = length - str.size();
    for (int i = 0; i < size; i++) {
        str += " ";
    }
    return str;
}

std::string spacesIndentationFloat(float val, int length) {
    std::string str = std::to_string(val);
    int size = length - str.size();
    for (int i = 0; i < size; i++) {
        str += " ";
    }
    return str;
}

void printTable(int search_el)
{
    std::vector<int> count_el = { 20,500,1000,3000,5000,10000 };

    std::cout << "\n+ ------------------+--------+-----------------+--------------+-----------+" << std::endl;
    std::cout << "| Метод поиска      | Размер | Искомый элемент | Сравнения    | Время (мс)|" << std::endl;
    std::cout << "+ ------------------+--------+-----------------+--------------+-----------+" << std::endl;
    for (int count : count_el)
    {
        std::vector<int> mas = createMassiv(count);
        std::vector<int> linear_mas = mas;
        std::vector<int> barier_mas = mas;

        auto start = std::chrono::high_resolution_clock::now();
        linearSearch(linear_mas, search_el);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        float time_linear = duration.count() * 1000;

        std::cout << "| Линейный поиск    |" << spacesIndentation(mas.size(), 8) << "|"<< spacesIndentation(search_el, 17) << "|"<< spacesIndentation(count_srav, 14) << "|"<< spacesIndentationFloat(time_linear, 11) << "|" << std::endl;

        std::cout << "+ ------------------+--------+-----------------+--------------+-----------+" << std::endl;
        
        start = std::chrono::high_resolution_clock::now();
        linearSearchWithBarrier(barier_mas, search_el);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float time_binary = duration.count() * 1000; 
        std::cout << "| Линейный поиск(Б) |" << spacesIndentation(mas.size(), 8) << "|"<< spacesIndentation(search_el, 17) << "|"<< spacesIndentation(count_srav, 14) << "|"<< spacesIndentationFloat(time_linear, 11) << "|" << std::endl;

        std::cout << "+ ------------------+--------+-----------------+--------------+-----------+" << std::endl;
    }
}

int checkInput(const std::string str) {
    int n;
    while (true) {
        std::cout << str;
        if (std::cin >> n) {
            return n;
        }
        else {
            std::cin.clear();
            std::cin.ignore(2000, '\n');
            std::cout << "Введено не число\n";
        }
    }
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "RU");

    int el = checkInput("Введите искомый элемент массива : ");
    printTable(el);
}