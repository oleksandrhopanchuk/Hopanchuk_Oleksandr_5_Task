#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <windows.h>

using namespace std;

// створення динамічної матриці n на n
int** createMatrix(int n) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    return matrix;
}

// заповнення матриці випадковими числами від -15 до 15
void fillMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 31 - 15;
        }
    }
}

// виведення матриці на екран
void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

// знаходження мінімального по модулю елемента всієї матриці
int findMinAbs(int** matrix, int n) {
    int minAbs = abs(matrix[0][0]);
    int minVal = matrix[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(matrix[i][j]) < minAbs) {
                minAbs = abs(matrix[i][j]);
                minVal = matrix[i][j];
            }
        }
    }
    return minVal;
}

// сектор 3 (правий трикутник без діагоналей): j > i і i + j > n-1
// знайти перший елемент який ділиться на k без остачі
void processSector3(int** matrix, int n, int k) {
    cout << "Sektor 3 (pravyi): j > i ta i + j > n-1" << endl;
    bool found = false;
    int count = 0;
    for (int i = 0; i < n && !found; i++) {
        for (int j = 0; j < n && !found; j++) {
            // сектор 3: правий трикутник між діагоналями
            if (j > i && (i + j) > (n - 1)) {
                count++;
                if (matrix[i][j] % k == 0) {
                    cout << "Pershyi element yakyi dilitsia na k=" << k
                         << ": matrix[" << i << "][" << j << "] = "
                         << matrix[i][j] << endl;
                    cout << "Nomer elementu v sektori: " << count << endl;
                    found = true;
                }
            }
        }
    }
    if (!found) {
        cout << "Elementiv yakyi dilitsia na k=" << k
             << " ne znaideno" << endl;
    }
}

// сектор 8 (права половина матриці): j >= n/2
// порахувати кількість елементів і замінити їх мінімальним по модулю
int processSector8(int** matrix, int n, int minVal) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = n / 2; j < n; j++) {
            count++;
            matrix[i][j] = minVal;
        }
    }
    return count;
}

// звільнення пам'яті
void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    srand(time(0));

    int n, k;
    cout << "Vvedit rozmir matrytsi n: ";
    cin >> n;
    if (n <= 0) {
        cout << "Rozmir maye buty bilshe 0!" << endl;
        return 1;
    }
    cout << "Vvedit chyslo k: ";
    cin >> k;

    int** matrix = createMatrix(n);
    fillMatrix(matrix, n);

    cout << "\nPochatkova matrytsia:" << endl;
    printMatrix(matrix, n);

    // знаходимо мінімальний по модулю до модифікації матриці
    int minVal = findMinAbs(matrix, n);
    cout << "\nMinimalnyi po modulyu element: " << minVal << endl;

    cout << "\n--- Rezultaty ---" << endl;
    processSector3(matrix, n, k);

    int count8 = processSector8(matrix, n, minVal);
    cout << "Kilkist elementiv u sektori 8: " << count8 << endl;
    cout << "Vsi zamyneni na: " << minVal << endl;

    cout << "\nMatrytsya pislia zamin u sektori 8:" << endl;
    printMatrix(matrix, n);

    deleteMatrix(matrix, n);
    return 0;
}
