#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

// ������� ������ �������
void printMatrix(const std::vector<std::vector<float>>& matrix) {
    for (const auto& row : matrix) {
        for (float value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}
 
// ������� ��� ����������� ����� �������
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

// ������� ��� ���������������� �������
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

// ������� ��� �������� �� ��������� ���� ������
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

// ������� �������� ���� ������
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

// ������� ��������� ���� ������
std::vector<std::vector<float>> multiplyMatrices(const std::vector<std::vector<float>>& matrix1, 
                                                 const std::vector<std::vector<float>>& matrix2) {
    // �������� ���������� ����� � �������� � ��������
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

// ������� ��� ���������� ����� ������� (����� ��������� �� ������� ��������� �������)
float trace(const std::vector<std::vector<float>>& matrix) {
    float sum = 0.0;
    for (size_t i = 0; i < matrix.size(); i++) {
        sum += matrix[i][i];
    }
    return sum;
}

// ������� ��� ���������� ������������ �������
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

// ������� ��� ���������� �������� �������
std::vector<std::vector<float>> inverseMatrix(const std::vector<std::vector<float>>& matrix) {
    int n = static_cast<int>(matrix.size());
    std::vector<std::vector<float>> inverse(n, std::vector<float>(n));
    float det = determinant(matrix);

    // �������� �� ������������� �������
    if (det == 0) {
        std::cout << "������� �����������, �������� ������� �� ����������." << std::endl;
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

                // ���������� ���������� � ����������� �����
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

    int N1, N2, M1, M2;
    
    std::cout << "\n������� ���������� ����� 1 �������: "; 
    std::cin >> M1;
    std::cout << "������� ���������� �������� 1 �������: "; 
    std::cin >> N1;
    
    std::vector<std::vector<float>> matrix_1(M1, std::vector<float>(N1));
    std::vector<std::vector<float>> matrix_1org(M1, std::vector<float>(N1)); // ��� ����������������
    std::vector<std::vector<float>> matrix_1_task4(M1, std::vector<float>(N1));
    std::vector<std::vector<float>> matrix_1_task3(M1, std::vector<float>(N1));

    std::cout << "\n���� ��������� �������_1 ����������� " << M1 << " x " << N1 << std::endl;
    for (int i = 0; i < M1; i++) {
        for (int j = 0; j < N1; j++) {
            std::cout << "�������_1, ���� ��������[" << i << "][" << j << "]: ";
            std::cin >> matrix_1[i][j];
            matrix_1org[i][j] = matrix_1[i][j];
            matrix_1_task4[i][j] = matrix_1[i][j];
            matrix_1_task3[i][j] = matrix_1[i][j];
        }
    }

    std::cout << "\n������� ���������� ����� 2 �������: "; 
    std::cin >> M2;
    std::cout << "������� ���������� �������� 2 �������: "; 
    std::cin >> N2;

    std::vector<std::vector<float>> matrix_2(M2, std::vector<float>(N2));
    std::vector<std::vector<float>> matrix_2org(M2, std::vector<float>(N2)); // ��� ����������������
    std::vector<std::vector<float>> matrix_2_task4(M2, std::vector<float>(N2));
    std::vector<std::vector<float>> matrix_2_task3(M2, std::vector<float>(N2));

    std::cout << "\n���� ��������� �������_2 ����������� " << M2 << " x " << N2 << std::endl;
    for (int i = 0; i < M2; i++) {
        for (int j = 0; j < N2; j++) {
            std::cout << "�������_1, ���� ��������[" << i << "][" << j << "]: ";
            std::cin >> matrix_2[i][j];
            matrix_2org[i][j] = matrix_2[i][j];
            matrix_2_task4[i][j] = matrix_2[i][j];
            matrix_2_task3[i][j] = matrix_2[i][j];
        }
    }

    std::cout << "\n����� �������_1:" << std::endl;
    printMatrix(matrix_1);
    // for (int i = 0; i < M1; i++) {
    //     for (int j = 0; j < N1; j++) {
    //         std::cout << " " << matrix_1[i][j];
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "\n����� �������_2:" << std::endl;
    printMatrix(matrix_2);
    
    // ���� ������
    int rank1 = findingRank(matrix_1, M1, N1);
    int rank2 = findingRank(matrix_2, M2, N2);

    std::cout << "\n���� ������ �������: " << rank1 << std::endl;
    std::cout << "���� ������ �������: " << rank2 << std::endl;

    // ����������������� ������
    std::vector<std::vector<float>> transposedMatrix1 = transposeMatrix(matrix_1org);
    std::vector<std::vector<float>> transposedMatrix2 = transposeMatrix(matrix_2org);
    
    std::cout << "\n����������������� ������ �������:" << std::endl;
    printMatrix(transposedMatrix1);
    std::cout << "\n����������������� ������ �������:" << std::endl;
    printMatrix(transposedMatrix2);

    // ����� ������� ���������� ��������� ������
    bool resultAreMatricesEqual = areMatricesEqual(matrix_1_task4, matrix_2_task4);
    if (resultAreMatricesEqual) {
        std::cout << "\n������� �����." << std::endl;
    }
    else {
        std::cout << "\n������� �� �����." << std::endl;
    }

    if (M1 == M2 && N1 == N2) {
        std::vector<std::vector<float>> result = addMatrices(matrix_1_task4, matrix_2_task4);
        std::cout << "\n��������� �������� ������:" << std::endl;
        printMatrix(result);
    }
    else {
        std::cout << "\n�������� �� �����������: ������� ������ ����� ���������� ������." << std::endl;
    }

    if (N1 == M2) {
        std::vector<std::vector<float>> result = multiplyMatrices(matrix_1_task4, matrix_2_task4);
        std::cout << "\n��������� ������������ ������:" << std::endl;
        printMatrix(result);
    }
    else {
        std::cout << "\n������������ ����������: ���������� �������� � ������ ������� ������ ��������� � ����������� ����� �� ������." << std::endl;
    }

    // ���� �� ���������� �������
    std::cout << "\n������ �� 1 �������: " << std::endl;
    if (M1 == N1) {
        float det = determinant(matrix_1_task3);
        float tr = trace(matrix_1_task3);
        std::vector<std::vector<float>> invMatrix = inverseMatrix(matrix_1_task3);

        std::cout << "������� ����������" << std::endl;
        std::cout << "������������ �������: " << det << std::endl;
        std::cout << "����� �������: " << tr << std::endl;

        if (det != 0) {
            std::cout << "�������� �������:\n";
            printMatrix(invMatrix);
        }
    }
    else {
        std::cout << "������� �� ����������. ���������� ����� ������������, ����� � �������� �������." << std::endl;
    }
    std::cout << "\n������ �� 2 �������: " << std::endl;
    if (M2 == N2) {
        float det = determinant(matrix_2_task3);
        float tr = trace(matrix_2_task3);
        std::vector<std::vector<float>> invMatrix = inverseMatrix(matrix_2_task3);

        std::cout << "������� ����������" << std::endl;
        std::cout << "������������ �������: " << det << std::endl;
        std::cout << "����� �������: " << tr << std::endl;

        if (det != 0) {
            std::cout << "�������� �������:\n";
            printMatrix(invMatrix);
        }
    }
    else {
        std::cout << "������� �� ����������. ���������� ����� ������������, ����� � �������� �������." << std::endl;
    }

    return 0;
}