#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <string>
#include <windows.h>
#include <fstream>

using namespace std;

float calculatePotentialEnergy(float A, float B, float C, float r) {
	return A * exp(-B * r) - C / pow(r, 6);
}

int main(int argc, char *argv[]) {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	// �������� ���������� ���������� ���������� ��������� ������
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " a b N" << std::endl;
        return 1;
    }

	float A, B, C;
	float a = std::stof(argv[1]);
	float b = std::stof(argv[2]);
	int n = std::stoi(argv[3]);
	float h = (b - a) / pow(10, 3);

	// ����� ������������ � ������������� �������� y � �������� ����������
    float min_y = (std::numeric_limits<float>::max)();
    float max_y = std::numeric_limits<float>::lowest();

	for (int i = 0; i < n; i++){
		std::cout <<"\n���� " << i + 1 << " ������ ���������� ��� z:";
		std::cout << "\n������� �������� �: ";
		std::cin >> A;
		std::cout << "������� �������� B: ";
		std::cin >> B;
		std::cout << "������� �������� C: ";
		std::cin >> C;
		
		std::vector<float> y_values;
        std::vector<float> x_values;

		for (float i = a; i <= b; i += h) {
			float potentialEnergy = calculatePotentialEnergy(A, B, C, i);
			y_values.push_back(potentialEnergy);
            x_values.push_back(i);
			// std::cout << "Potential Energy: " << potentialEnergy << std::endl;
			// std::cout << i << " " << "y(" << i << ";" << potentialEnergy << ")" << std::endl;
		}

		// ����� ��������� ������������ � ������������� �������� y
        float local_min_y = *std::min_element(y_values.begin(), y_values.end());
        float local_max_y = *std::max_element(y_values.begin(), y_values.end());

		min_y = (std::min)(min_y, local_min_y);
        max_y = (std::max)(max_y, local_max_y);
		std::cout << "\nmin y: " << std::fixed << std::setprecision(3) << local_min_y << std::endl;
    	std::cout << "max y: " << std::fixed << std::setprecision(3) << local_max_y << std::endl;

		// ������ ����������� ���������� � ����
        std::string filename = std::to_string(i + 1) + ".txt";
        std::ofstream file(filename);

        file << "#z = " << "�=" << A << "; B=" << B << "; C=" << C <<"\n";
        for (size_t j = 0; j < x_values.size(); ++j) {
            file << std::fixed << std::setprecision(3) << x_values[j] << " " << y_values[j] << "\n";
        }

	}

	// ����� ����� ������������ � ������������� �������� y
    std::cout << "\n����������� �������� y �� ���� �������: " << std::fixed << std::setprecision(3) << min_y << std::endl;
    std::cout << "������������ �������� y �� ���� �������: " << std::fixed << std::setprecision(3) << max_y << std::endl;

	return 0;
}