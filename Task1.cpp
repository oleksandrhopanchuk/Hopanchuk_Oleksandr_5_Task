#include <iostream>
#include <ctime>
#include <chrono>
#include <future>
#include <windows.h>

using namespace std;
using namespace std::chrono;

// вивід масиву (якщо більше 20 елементів - скорочено)
void printArray(int arr[], int n) {
    if (n <= 20) {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
    }
    else {
        for (int i = 0; i < 5; i++)
            cout << arr[i] << " ";
        cout << "... ";
        for (int i = n - 5; i < n; i++)
            cout << arr[i] << " ";
    }
    cout << endl;
}

// заповнення масиву випадковими числами від 0 до 100000
void fillArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100001;
}

// копіювання масиву
void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}

// сортування вставкою
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// сортування підрахунком
void countingSort(int arr[], int n) {
    int mn = arr[0], mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < mn) mn = arr[i];
        if (arr[i] > mx) mx = arr[i];
    }

    int range = mx - mn + 1;
    int* cnt = new int[range];
    for (int i = 0; i < range; i++) cnt[i] = 0;

    for (int i = 0; i < n; i++)
        cnt[arr[i] - mn]++;

    int k = 0;
    for (int i = 0; i < range; i++) {
        while (cnt[i] > 0) {
            arr[k] = i + mn;
            k++;
            cnt[i]--;
        }
    }

    delete[] cnt;
}

// сортування Шелла
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int tmp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > tmp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = tmp;
        }
    }
}

// бінарний пошук
int binarySearch(int arr[], int n, int val) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == val) return mid;
        if (arr[mid] < val) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// порівняння синхронного та асинхронного сортування
void compareSyncAsync(void (*sortFunc)(int[], int), string name, int n) {
    int* arr1 = new int[n];
    int* arr2 = new int[n];
    fillArray(arr1, n);
    copyArray(arr1, arr2, n);

    // синхронно
    auto s1 = high_resolution_clock::now();
    sortFunc(arr1, n);
    double tSync = duration<double, milli>(high_resolution_clock::now() - s1).count();

    // асинхронно
    auto s2 = high_resolution_clock::now();
    auto f = async(launch::async, sortFunc, arr2, n);
    f.get();
    double tAsync = duration<double, milli>(high_resolution_clock::now() - s2).count();

    cout << name << "\t\t" << tSync << " ms\t\t" << tAsync << " ms" << endl;

    delete[] arr1;
    delete[] arr2;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    srand(time(0));

    int sizes[] = { 15, 150, 2000, 9000, 40000, 140000 };

    cout << "=== Task 1. Sorting arrays. Variant 5 ===" << endl;
    cout << endl;

    // демонстрація на малому масиві
    cout << "--- Demo (n=15) ---" << endl;
    int demo[15];
    fillArray(demo, 15);
    cout << "Initial array: ";
    printArray(demo, 15);

    int tmp[15];

    copyArray(demo, tmp, 15);
    insertionSort(tmp, 15);
    cout << "Insertion sort: ";
    printArray(tmp, 15);

    copyArray(demo, tmp, 15);
    countingSort(tmp, 15);
    cout << "Counting sort:  ";
    printArray(tmp, 15);

    copyArray(demo, tmp, 15);
    shellSort(tmp, 15);
    cout << "Shell sort:     ";
    printArray(tmp, 15);

    // таблиця часу виконання
    cout << endl;
    cout << "--- Execution time table ---" << endl;
    cout << "n\t\tInsertion\tCounting\tShell" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (int s = 0; s < 6; s++) {
        int n = sizes[s];

        int* a1 = new int[n];
        int* a2 = new int[n];
        int* a3 = new int[n];
        fillArray(a1, n);
        copyArray(a1, a2, n);
        copyArray(a1, a3, n);

        auto t1s = high_resolution_clock::now();
        insertionSort(a1, n);
        double t1 = duration<double, milli>(high_resolution_clock::now() - t1s).count();

        auto t2s = high_resolution_clock::now();
        countingSort(a2, n);
        double t2 = duration<double, milli>(high_resolution_clock::now() - t2s).count();

        auto t3s = high_resolution_clock::now();
        shellSort(a3, n);
        double t3 = duration<double, milli>(high_resolution_clock::now() - t3s).count();

        cout << n << "\t\t" << t1 << "\t\t" << t2 << "\t\t" << t3 << endl;

        delete[] a1;
        delete[] a2;
        delete[] a3;
    }

    // асинхронне сортування
    cout << endl;
    cout << "--- Sync vs Async (n=140000) ---" << endl;
    cout << "Method\t\tSync\t\t\tAsync" << endl;
    cout << "------------------------------------------------------------" << endl;
    compareSyncAsync(insertionSort, "Insertion", 140000);
    compareSyncAsync(countingSort, "Counting", 140000);
    compareSyncAsync(shellSort, "Shell", 140000);

    // бінарний пошук
    cout << endl;
    cout << "--- Binary search ---" << endl;
    int sarr[15];
    fillArray(sarr, 15);
    shellSort(sarr, 15);
    cout << "Sorted array: ";
    printArray(sarr, 15);

    int val;
    cout << "Enter number to search: ";
    cin >> val;

    int pos = binarySearch(sarr, 15, val);
    if (pos != -1)
        cout << "Found at index: " << pos << endl;
    else
        cout << "Not found." << endl;

    return 0;
}
