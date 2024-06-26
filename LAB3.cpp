﻿#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;

// Функция для ввода матрицы
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

//Функция для вывода матрицы
void outputMatrix(vector<vector<double>>& matrix, int size) {
    cout << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для ввода вектора правой части
void inputVector(vector<double>& b, int size) {
    for (int i = 0; i < size; i++) {
        double value;
        cout << "Введите элемент [" << i << "] вектора правой части: ";
        cin >> value;
        b.push_back(value);
    }
}

// Функция для вывода вектора
void outputVector(const vector<double>& vec) {
    for (double value : vec) {
        cout << value << " ";
    }
    cout << endl;
}

// Функция для решения СЛАУ методом Гаусса
void gaussianElimination(vector<vector<double>>& matrix, vector<double>& b, vector<double>& x, int size) {
    // Прямой ход метода Гаусса для получения верхней треугольной матрицы
    for (int k = 0; k < size - 1; k++) {
#pragma omp parallel for 
        for (int i = k + 1; i < size; i++) {
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k; j < size; j++) {
                matrix[i][j] -= factor * matrix[k][j];
                //outputMatrix(matrix, size);
                //cout << endl<<"Номер потока: "<< omp_get_thread_num();
            }
            b[i] -= factor * b[k];
        }
    }

    // Обратный ход метода Гаусса для нахождения неизвестных 
    for (int i = size - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < size; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
        x[i] /= matrix[i][i];
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int size;
    cout << "Введите размер матрицы: ";
    cin >> size;

    vector<vector<double>> matrix;
    vector<double> b;
    vector<double> x(size, 0);

    inputMatrix(matrix, size);
    inputVector(b, size);
    //auto start = chrono::high_resolution_clock::now();
    gaussianElimination(matrix, b, x, size);
    //auto end = chrono::high_resolution_clock::now();
    //chrono::duration<double> time_elapsed = end - start;
    

    outputMatrix(matrix,size);
    cout << "Решение СЛАУ: ";
    outputVector(x);
    //cout << "Время:" << time_elapsed.count();

    return 0;
}