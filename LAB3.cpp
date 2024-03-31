#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;


void inputMatrix(vector<vector<double>>& matrix, int size) {
    for (int i = 0; i < size; i++) {
        matrix.push_back(vector<double>());
        for (int j = 0; j < size; j++) {
            double value;
            cout << "Введите элемент [" << i << "][" << j << "] матрицы: ";
            cin >> value;
            matrix[i].push_back(value);
        }
    }
}

void inputVector(vector<double>& b, int size) {
    for (int i = 0; i < size; i++) {
        double value;
        cout << "Введите элемент [" << i << "] вектора правой части: ";
        cin >> value;
        b.push_back(value);
    }
}


void outputVector(const vector<double>& vec) {
    for (double value : vec) {
        cout << value << " ";
    }
    cout << endl;
}


void gaussianElimination(vector<vector<double>>& matrix, vector<double>& b, vector<double>& x, int size) {
    for (int k = 0; k < size - 1; k++) {
        for (int i = k + 1; i < size; i++) {
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k; j < size; j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    for (int i = size - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < size; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
        x[i] /= matrix[i][i];
    }
}

int main() {
    int size;
    cout << "Введите размер матрицы: ";
    cin >> size;

    vector<vector<double>> matrix;
    vector<double> b;
    vector<double> x(size, 0);

    inputMatrix(matrix, size);
    inputVector(b, size);
    gaussianElimination(matrix, b, x, size);
    outputVector(x);

    return 0;
}