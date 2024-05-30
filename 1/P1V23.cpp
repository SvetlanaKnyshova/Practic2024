#include <iostream>
#include <cmath>
#include <vector> 
#include <windows.h>

using namespace std;

bool check_is_numeric(char value[])
{
	for (int i = 0; i < strlen(value); i++) {
		if (isdigit(value[i])) {
			continue;
		}
		if (value[i] == *strdup(".")) {
			continue;
		}
		return false;
	}
	return true;
}

void countingSortAlgo(int arr[], int size, int position) {
	const int limit = 10;
	int result[size];
	int count[limit] = {0};
	// Вычисление количества каждого целого числа
	for (int j = 0; j < size; j++) {
		count[(arr[j] / position) % 10]++;
	}
	// Расчет совокупного количества
	for (int j = 1; j < limit; j++) {
		count[j] += count[j - 1];
	}
	// Сортировка
	for (int j = size - 1; j >= 0; j--) {
		result[count[(arr[j] / position) % 10] - 1] = arr[j];
		count[(arr[j] / position) % 10]--;
	}
	for (int i = 0; i < size; i++) {
		arr[i] = result[i];
	}
}

void radixSortAlgo(int arr[], int size, int value_max) {
	for (int position = 1; value_max / position > 0; position *= 10) {
		countingSortAlgo(arr, size, position);
	}
}

int main(int argc, char *argv[])
{
	SetConsoleCP(1251); // Установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // Установка кодовой страницы win-cp 1251 в поток вывода

	int arraySize = argc - 1;
	float sum = 0;
	float op = 1;
	int evenNumberCount = 0;
	int oddNumberCount = 0;
	float Searh;
	bool found = false;
	int count = 0;
	int maxSize = 0;

	float *arrayMain = new float[arraySize]; // Создаем массив указателей
	for(int i = 1; i < argc; i++) {
		if (check_is_numeric(argv[i]) == false) {
			std::cout << "Error: некоректно задан аргумент <"<< argv[i] << ">: допустимы только числа (более 0)" << endl;
			return 0;
		} 
		else {
			arrayMain[i - 1] = stof(argv[i]);
			int position = string(argv[i]).find(".");
    		string afterDot = string(argv[i]).substr(position + 1);
			if (afterDot.size() > maxSize) {
				maxSize = afterDot.size();
			}
		}
	}

	std::cout << "Введите искомый элемент массива: ";
	std::cin >> Searh;

	float min = arrayMain[0];
	float max = arrayMain[0];
	std::vector<int> minIndex, maxIndex, searhIndex;

	for (int i = 0; i < arraySize; i++) {
		if (arrayMain[i] < min) {
			min = arrayMain[i];
			minIndex.clear(); 
            minIndex.push_back(i);
        } 
        else if (arrayMain[i] == min) { 
            	minIndex.push_back(i);
            }

		if (arrayMain[i] > max) {
			max = arrayMain[i];
			maxIndex.clear(); 
            maxIndex.push_back(i); 
        } 
        else if (arrayMain[i] == max) { 
                maxIndex.push_back(i); 
            } 
		if (arrayMain[i] == Searh) {
			searhIndex.push_back(i);
			count++;
   			found = true;
		}
		sum = sum + arrayMain[i];
		op = op * arrayMain[i];
		if (int(floor(arrayMain[i] + 0.5)) % 2 == 0) {
			evenNumberCount = evenNumberCount + 1;
		}
		else oddNumberCount = oddNumberCount + 1;
	}

	float averageArith = sum / arraySize;
	float averageGeo = pow(op, 1.0 / arraySize);

	// Вывод информации о результате поиска
	if (found) {
		std::cout << "Значение найдено в массиве " << count << " раз(а)." << endl;
		std::cout << "Индексы найденного значения: ";
		for (int index : searhIndex) { 
            std::cout << index << " "; 
        }
		std::cout << endl;
	}
	else {
		std::cout << "Значение не найдено в массиве." << endl;
	}
	
	int *arrSord = new int[arraySize];
	int ValueMax = max * int(pow(10, maxSize));

	for(int i = 0; i < arraySize; i++) {
		arrSord[i] = (arrayMain[i] * int(pow(10, maxSize)));
	}
    radixSortAlgo(arrSord, arraySize, ValueMax);

	// Вывод сортировки
	std::cout <<"\nСортировка по возрастанию: ";
	for (int i = 0; i < arraySize; i++) {
		std::cout << static_cast<float>((arrSord[i]) / pow(10, maxSize)) << " ";
	}
	std::cout <<"\nСортировка по убыванию: ";
	for (int i = arraySize - 1; i >= 0; i--) {
		std::cout << static_cast<float>((arrSord[i]) / pow(10, maxSize)) << " ";
	}
	// Вывод остальной информации по заданию
	std::cout << endl << "\nДанные по массиву: " << endl;
	std::cout << "min = " << min << ", Индексы: "; 
        for (int index : minIndex) { 
            std::cout << index << " "; 
        }  
    std::cout << "\nmax = " << max << ", Индексы: "; 
        for (int index : maxIndex) { 
            std::cout << index << " "; 
        }
    std::cout << endl;
	std::cout << "Сумма элементов массива: " << sum << endl;
	std::cout << "Произведение элементов массива: " << op << endl;
	std::cout << "Среднее арифметическое: " << averageArith << endl;
	std::cout << "Среднее геометрическое: " << averageGeo << endl;
	std::cout << "Количество четных элементов: " << evenNumberCount << endl;
	std::cout << "Количество нечетных элементов: " << oddNumberCount << endl;

	delete arrayMain;
	return 0;
}