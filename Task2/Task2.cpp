#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

// функція для послідовного з'єднання
// при послідовному з'єднанні опори просто додаються
double serialResistance(double r[], int n) {
    double total = 0;
    for (int i = 0; i < n; i++) {
        total += r[i];
    }
    return total;
}

// функція для паралельного з'єднання
// при паралельному: 1/R = 1/R1 + 1/R2 + ... + 1/Rn
double parallelResistance(double r[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += 1.0 / r[i];
    }
    return 1.0 / sum;
}

// функція для виведення всіх опорів
void printResistors(double r[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "R" << i + 1 << " = " << r[i] << " Om" << endl;
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // задані опори з умови варіанту 5
    double r[] = { 5, 6, 7, 8, 4, 3, 2, 5, 9, 12 };
    int n = 10;

    cout << "=== Tema 2. Funktsiyi v C++. Variant 5 ===" << endl;
    cout << endl;

    cout << "Zadani rezystory:" << endl;
    printResistors(r, n);
    cout << endl;

    // послідовне з'єднання
    cout << "--- Poslidovne zyednannya ---" << endl;
    cout << "Formula: R = R1 + R2 + ... + R10" << endl;
    cout << "R = ";
    for (int i = 0; i < n; i++) {
        cout << r[i];
        if (i < n - 1) cout << " + ";
    }
    cout << endl;
    double rSerial = serialResistance(r, n);
    cout << fixed << setprecision(4);
    cout << "Rezultat: R = " << rSerial << " Om" << endl;
    cout << endl;

    // паралельне з'єднання
    cout << "--- Paralelne zyednannya ---" << endl;
    cout << "Formula: 1/R = 1/R1 + 1/R2 + ... + 1/R10" << endl;
    cout << "Vnesok kozhnogo rezystora (1/Ri):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  1/R" << i + 1 << " = 1/" << r[i]
            << " = " << 1.0 / r[i] << endl;
    }
    double rParallel = parallelResistance(r, n);
    cout << "Rezultat: R = " << rParallel << " Om" << endl;

    return 0;
}
