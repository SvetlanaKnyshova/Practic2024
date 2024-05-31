#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <iomanip>
#include <cctype>   // для функции isdigit
#include <cstdlib>  // для функции atoi
#include <stdlib.h>


using namespace std;

bool check_is_numeric(char value[])
{
	for (int i = 0; i < strlen(value); i++) {
		if (isdigit(value[i])) {
			continue;
		}
		return false;
	}
	return true;
}

// Функция вывода матрицы
void printMatrix(const std::vector<std::vector<float>>& matrix) {
    for (const auto& row : matrix) {
        for (float value : row) {
            std::cout << std::setprecision(2) << value << " ";
        }
        std::cout << std::endl;
    }
}
 
// Функция для определения ранга матрицы
int findingRank(std::vector<std::vector<float>>& matrix, int rows, int cols) {
    int rank = 0;
    for (int col = 0; col < cols; col++) {
        for (int row = rank; row < rows; row++) {
            if (matrix[row][col] != 0) {
                std::swap(matrix[row], matrix[rank]);
                for (int i = rank + 1; i < rows; i++) {
                    float factor = matrix[i][col] / matrix[rank][col];
                    for (int j = col; j < cols; j++) {
                        matrix[i][j] -= factor * matrix[rank][j];
                    }
                }
                rank++;
                break;
            }
        }
    }
    return rank;
}

// Функция для транспонирования матрицы
std::vector<std::vector<float>> transposeMatrix(const std::vector<std::vector<float>>& matrix) {
    int rows = static_cast<int>(matrix.size());
    int cols = static_cast<int>(matrix[0].size());
    std::vector<std::vector<float>> transposed(cols, std::vector<float>(rows, 0.0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

// Функция для проверки на равенство двух матриц
bool areMatricesEqual(const std::vector<std::vector<float>>& matrix1, const std::vector<std::vector<float>>& matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        return false;
    }

    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix1[0].size(); j++) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Функция сложения двух матриц
std::vector<std::vector<float>> addMatrices(const std::vector<std::vector<float>>& matrix1, 
                                            const std::vector<std::vector<float>>& matrix2) {
    int rows = static_cast<int>(matrix1.size());
    int cols = static_cast<int>(matrix1[0].size());
    std::vector<std::vector<float>> result(rows, std::vector<float>(cols, 0.0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

// Функция умножения двух матриц
std::vector<std::vector<float>> multiplyMatrices(const std::vector<std::vector<float>>& matrix1, 
                                                 const std::vector<std::vector<float>>& matrix2) {
    // Получаем количество строк и столбцов в матрицах
    int rows1 = static_cast<int>(matrix1.size());
    int cols1 = static_cast<int>(matrix1[0].size());
    int cols2 = static_cast<int>(matrix2[0].size());
    std::vector<std::vector<float>> result(rows1, std::vector<float>(cols2, 0.0));

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// Функция для вычисления следа матрицы (суммы элементов на главной диагонали матрицы)
float trace(const std::vector<std::vector<float>>& matrix) {
    float sum = 0.0;
    for (size_t i = 0; i < matrix.size(); i++) {
        sum += matrix[i][i];
    }
    return sum;
}

// Функция для нахождения определителя матрицы
float determinant(const std::vector<std::vector<float>>& matrix) {
    int n = static_cast<int>(matrix.size());

    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else {
        float det = 0;
        int sign = 1;

        for (int i = 0; i < n; ++i) {
            std::vector<std::vector<float>> submatrix;
            for (int j = 1; j < n; ++j) {
                std::vector<float> row;
                for (int k = 0; k < n; ++k) {
                    if (k != i) {
                        row.push_back(matrix[j][k]);
                    }
                }
                submatrix.push_back(row);
            }
            det += sign * matrix[0][i] * determinant(submatrix);
            sign = -sign;
        }
        return det;
    }
}

// Функция для вычисления обратной матрицы
std::vector<std::vector<float>> inverseMatrix(const std::vector<std::vector<float>>& matrix) {
    int n = static_cast<int>(matrix.size());
    std::vector<std::vector<float>> inverse(n, std::vector<float>(n));
    float det = determinant(matrix);

    // Проверка на вырожденность матрицы
    if (det == 0) {
        std::cout << "Матрица вырожденная, обратной матрицы не существует." << std::endl;
        return inverse;
    }

    if (n == 2) {
        float invDet = 1.0 / det;
        inverse[0][0] = matrix[1][1] * invDet;
        inverse[0][1] = -matrix[0][1] * invDet;
        inverse[1][0] = -matrix[1][0] * invDet;
        inverse[1][1] = matrix[0][0] * invDet;
    }
    else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::vector<std::vector<float>> minorMatrix;
                for (int k = 0; k < n; ++k) {
                    if (k == i) continue;
                    std::vector<float> row;
                    for (int l = 0; l < n; ++l) {
                        if (l == j) continue;
                        row.push_back(matrix[k][l]);
                    }
                    minorMatrix.push_back(row);
                }

                // Вычисление подматрицы и определения знака
                float minorDet = determinant(minorMatrix);

                float sign = ((i + j) % 2 == 0) ? 1 : -1;
                inverse[j][i] = sign * minorDet / det;
                std::cout << inverse[i][j];
            }
        }
    }
    return inverse;
}

int main() { 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N1, N2, M1, M2, num;
    
    std::cout << "\nВведите количество строк 1 матрицы: "; 
    std::cin >> M1;
    std::cout << "Введите количество столбцов 1 матрицы: "; 
    std::cin >> N1;
    
    std::vector<std::vector<float>> matrix_1(M1, std::vector<float>(N1));
    std::vector<std::vector<float>> matrix_1org(M1, std::vector<float>(N1)); // для транспонирования
    std::vector<std::vector<float>> matrix_1_task4(M1, std::vector<float>(N1));
    std::vector<std::vector<float>> matrix_1_task3(M1, std::vector<float>(N1));
    char *line;

    std::cout << "\nВвод элементов Матрица_1 размерности " << M1 << " x " << N1 << std::endl;
    for (int i = 0; i < M1; i++) {
        for (int j = 0; j < N1; j++) {
            std::cout << "Матрица_1, ввод элемента[" << i << "][" << j << "]: ";
            std::cin >> line;
            while (check_is_numeric(line) == false or atoi(line) == 0) {
                std::cout << "Error: введенный элемент [" << i << "][" << j << "] - не является целочисленным, либо не больше нуля!" << std::endl;
                std::cout << "Матрица_1, ввод элемента[" << i << "][" << j << "]: ";
                std::cin >> line;
		    }
                matrix_1[i][j] = stof(line);
                matrix_1org[i][j] = matrix_1[i][j];
                matrix_1_task4[i][j] = matrix_1[i][j];
                matrix_1_task3[i][j] = matrix_1[i][j];
        }
    }
    
    std::cout << "\nВведите количество строк 2 матрицы: "; 
    std::cin >> M2;
    std::cout << "Введите количество столбцов 2 матрицы: "; 
    std::cin >> N2;

    std::vector<std::vector<float>> matrix_2(M2, std::vector<float>(N2));
    std::vector<std::vector<float>> matrix_2org(M2, std::vector<float>(N2)); // для транспонирования
    std::vector<std::vector<float>> matrix_2_task4(M2, std::vector<float>(N2));
    std::vector<std::vector<float>> matrix_2_task3(M2, std::vector<float>(N2));


    std::cout << "\nВвод элементов Матрица_2 размерности " << M2 << " x " << N2 << std::endl;
    for (int i = 0; i < M2; i++) {
        for (int j = 0; j < N2; j++) {
            std::cout << "Матрица_2, ввод элемента[" << i << "][" << j << "]: ";
            std::cin >> line;
            while (check_is_numeric(line) == false or atoi(line) == 0) {
                std::cout << "Error: введенный элемент [" << i << "][" << j << "] - не является целочисленным, либо не больше нуля!" << std::endl;
                std::cout << "Матрица_2, ввод элемента[" << i << "][" << j << "]: ";
                std::cin >> line;
		    }
            matrix_2[i][j] = stof(line);
            matrix_2org[i][j] = matrix_2[i][j];
            matrix_2_task4[i][j] = matrix_2[i][j];
            matrix_2_task3[i][j] = matrix_2[i][j];
        }
    }

    std::cout << "\nВывод Матрица_1:" << std::endl;
    printMatrix(matrix_1);
    // for (int i = 0; i < M1; i++) {
    //     for (int j = 0; j < N1; j++) {
    //         std::cout << " " << matrix_1[i][j];
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "\nВывод Матрица_2:" << std::endl;
    printMatrix(matrix_2);
    
    // Ранг матриц
    int rank1 = findingRank(matrix_1, M1, N1);
    int rank2 = findingRank(matrix_2, M2, N2);

    std::cout << "\nРанг первой матрицы: " << rank1 << std::endl;
    std::cout << "Ранг второй матрицы: " << rank2 << std::endl;

    // Транспонтирование матриц
    std::vector<std::vector<float>> transposedMatrix1 = transposeMatrix(matrix_1org);
    std::vector<std::vector<float>> transposedMatrix2 = transposeMatrix(matrix_2org);
    
    std::cout << "\nТранспонированная первая матрица:" << std::endl;
    printMatrix(transposedMatrix1);
    std::cout << "\nТранспонированная вторая матрица:" << std::endl;
    printMatrix(transposedMatrix2);

    // Вызов функции нахождения равенства матриц
    bool resultAreMatricesEqual = areMatricesEqual(matrix_1_task4, matrix_2_task4);
    if (resultAreMatricesEqual) {
        std::cout << "\nМатрицы равны." << std::endl;
    }
    else {
        std::cout << "\nМатрицы не равны." << std::endl;
    }

    if (M1 == M2 && N1 == N2) {
        std::vector<std::vector<float>> result = addMatrices(matrix_1_task4, matrix_2_task4);
        std::cout << "\nРезультат сложения матриц:" << std::endl;
        printMatrix(result);
    }
    else {
        std::cout << "\nСложение не произведено: матрицы должны иметь одинаковый размер." << std::endl;
    }

    if (N1 == M2) {
        std::vector<std::vector<float>> result = multiplyMatrices(matrix_1_task4, matrix_2_task4);
        std::cout << "\nРезультат перемножения матриц:" << std::endl;
        printMatrix(result);
    }
    else {
        std::cout << "\nПеремножение невозможно: количество столбцов в первой матрице должно совпадать с количеством строк во второй." << std::endl;
    }

    // Блок на квадратные матрицы
    std::cout << "\nДанные по 1 матрице: " << std::endl;
    if (M1 == N1) {
        float det = determinant(matrix_1_task3);
        float tr = trace(matrix_1_task3);
        std::vector<std::vector<float>> invMatrix = inverseMatrix(matrix_1_task3);

        std::cout << "Матрица квадратная" << std::endl;
        std::cout << "Определитель матрицы: " << det << std::endl;
        std::cout << "Следы матрицы: " << tr << std::endl;

        if (det != 0) {
            std::cout << "Обратная матрица:\n";
            printMatrix(invMatrix);
        }
    }
    else {
        std::cout << "Матрица не квадратная. Невозможно найти определитель, следы и обратную матрицу." << std::endl;
    }
    std::cout << "\nДанные по 2 матрице: " << std::endl;
    if (M2 == N2) {
        float det = determinant(matrix_2_task3);
        float tr = trace(matrix_2_task3);
        std::vector<std::vector<float>> invMatrix = inverseMatrix(matrix_2_task3);

        std::cout << "Матрица квадратная" << std::endl;
        std::cout << "Определитель матрицы: " << det << std::endl;
        std::cout << "Следы матрицы: " << tr << std::endl;

        if (det != 0) {
            std::cout << "Обратная матрица:\n";
            printMatrix(invMatrix);
        }
    }
    else {
        std::cout << "Матрица не квадратная. Невозможно найти определитель, следы и обратную матрицу." << std::endl;
    }

    return 0;
}