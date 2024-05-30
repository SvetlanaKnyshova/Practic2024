#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
 
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string line, max_line;

    std::ifstream file("Text.txt");
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл.";
        return 1;
    }
    else {
        while (std::getline(file, line))
        {
            if (line.size() > max_line.size())
                max_line = line;
        }
     
        std::cout << "Самая длинная строка:" << std::endl; 
        std::cout << max_line << std::endl; 
        std::cout << "Максимальная длина: " << max_line.size() << std::endl;
    }
 
    return 0;
}