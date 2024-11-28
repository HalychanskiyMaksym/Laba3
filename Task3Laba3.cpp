#include <iostream>
#include <stdexcept>
using namespace std;

class Matrix {
private:
    int* data;
    int rows, cols;
    mutable int errorState;  // Код помилки
    static int objectCount;  // Лічильник об'єктів

public:
    // Конструктор за замовчуванням (3x3 матриця)
    Matrix() : rows(3), cols(3), errorState(0) {
        data = new int[rows * cols]();
        objectCount++;
    }

    // Конструктор з одним параметром (n x n матриця)
    Matrix(int n) : rows(n), cols(n), errorState(0) {
        data = new int[rows * cols]();
        objectCount++;
    }

    // Конструктор з двома параметрами (n x m матриця)
    Matrix(int n, int m, int value = 0) : rows(n), cols(m), errorState(0) {
        data = new int[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = value;
        }
        objectCount++;
    }

    // Конструктор копій
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), errorState(0) {
        data = new int[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = other.data[i];
        }
        objectCount++;
    }

    // Оператор присвоєння
    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;  // Перевірка на самоприсвоєння

        delete[] data;  // Видаляємо старі дані

        rows = other.rows;
        cols = other.cols;
        data = new int[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    // Деструктор
    ~Matrix() {
        delete[] data;
        objectCount--;
    }

    // Функція для присвоєння значення елементу
    void setElement(int i, int j, int value = 0) {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            errorState = 1;  // Код помилки: індекс за межами
            return;
        }
        data[i * cols + j] = value;
    }

    // Функція для отримання елементу
    int getElement(int i, int j) const {
        if (i < 0 || i >= rows || j < 0 || j >= cols) {
            errorState = 2;  // Код помилки: індекс за межами
            return -1;  // Повертаємо помилкове значення
        }
        return data[i * cols + j];
    }

    // Функція для друку матриці
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << getElement(i, j) << " ";
            }
            cout << endl;
        }
    }

    // Оператор додавання
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must be the same for addition.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Оператор віднімання
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must be the same for subtraction.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Оператор множення
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions must be compatible for multiplication.");
        }

        Matrix result(rows, other.cols, 0);  // Результат буде матрицею розміру rows x other.cols
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.data[i * other.cols + j] += data[i * cols + k] * other.data[k * other.cols + j];
                }
            }
        }
        return result;
    }

    // Оператор порівняння (рівність)
    bool operator==(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }

        for (int i = 0; i < rows * cols; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    // Оператор порівняння (менше)
    bool operator<(const Matrix& other) const {
        return rows * cols < other.rows * other.cols;
    }

    // Оператор порівняння (більше)
    bool operator>(const Matrix& other) const {
        return rows * cols > other.rows * other.cols;
    }

    // Статична функція для отримання лічильника об'єктів
    static int getObjectCount() {
        return objectCount;
    }
};

// Ініціалізація статичної змінної
int Matrix::objectCount = 0;

int main() {
    // Створення матриць
    Matrix m1;  // 3x3 матриця
    Matrix m2(2);  // 2x2 матриця
    Matrix m3(3, 2, 5);  // 3x2 матриця, ініціалізована значенням 5
    Matrix m4(2, 3, 3);  // 2x3 матриця, ініціалізована значенням 3

    // Встановлення елементів
    m1.setElement(0, 0, 1);
    m1.setElement(1, 1, 2);
    m1.setElement(2, 2, 3);

    // Друк матриць
    cout << "m1:" << endl;
    m1.print();
    cout << endl;

    cout << "m2:" << endl;
    m2.print();
    cout << endl;

    cout << "m3:" << endl;
    m3.print();
    cout << endl;

    cout << "m4:" << endl;
    m4.print();
    cout << endl;

    // Додавання матриць
    Matrix m5 = m1 + m1;
    cout << "m5 (m1 + m1):" << endl;
    m5.print();
    cout << endl;

    // Множення матриць
    Matrix m6 = m3 * m4;
    cout << "m6 (m3 * m4):" << endl;
    m6.print();
    cout << endl;

    // Порівняння матриць
    if (m1 == m5) {
        cout << "m1 is equal to m5" << endl;
    } else {
        cout << "m1 is not equal to m5" << endl;
    }

    cout << "Total objects: " << Matrix::getObjectCount() << endl;

    return 0;
}
