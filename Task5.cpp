#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

// 1. Структура для опису учня
struct Student {
    string surname;
    string name;
    string grade;        // Клас (наприклад, 10-А)
    double avgScore;     // Середній бал
    string parentPhone;  // Телефон одного з батьків
};

// Функція для безпечного введення дробового числа (захист від вводу літер)
double getSafeDouble(string message) {
    double value;
    cout << message;
    while (!(cin >> value)) {
        cout << "[Помилка] Будь ласка, введіть число: ";
        cin.clear();          // Скидаємо прапорець помилки
        string dummy;
        cin >> dummy;         // Очищаємо неправильний текст
    }
    return value;
}

// 2. Функція збереження об'єкта у файл (додавання в кінець)
void saveToFile(const Student& s) {
    ofstream outFile("students.txt", ios::app);

    if (outFile.is_open()) {
        // Записуємо дані через пробіл
        outFile << s.surname << " "
            << s.name << " "
            << s.grade << " "
            << s.avgScore << " "
            << s.parentPhone << endl;
        outFile.close();
    }
    else {
        cout << "[Помилка] Не вдалося відкрити файл для запису!" << endl;
    }
}

// 3. Зчитування всіх записів з файлу у динамічний масив (vector)
vector<Student> loadFromFile() {
    vector<Student> students;
    ifstream inFile("students.txt");

    if (inFile.is_open()) {
        Student s;
        // Зчитуємо дані, поки вдається прочитати всі 5 полів
        while (inFile >> s.surname >> s.name >> s.grade >> s.avgScore >> s.parentPhone) {
            students.push_back(s);
        }
        inFile.close();
    }
    return students;
}

// 4. Виведення всіх учнів на екран
void showAllStudents(const vector<Student>& students) {
    cout << "\n>>> СПИСОК УСІХ УЧНІВ <<<" << endl;

    if (students.empty()) {
        cout << "База даних порожня. Додайте учнів." << endl;
        return;
    }

    for (int i = 0; i < students.size(); i++) {
        cout << "Прізвище: " << setw(10) << left << students[i].surname
            << " | Ім'я: " << setw(10) << students[i].name
            << " | Клас: " << setw(5) << students[i].grade
            << " | Бал: " << setw(5) << students[i].avgScore
            << " | Телефон: " << students[i].parentPhone << endl;
    }
}

// 5. Індивідуальна функція: Порахувати загальний середній бал
void calculateSchoolAverage(const vector<Student>& students) {
    cout << "\n>>> АНАЛІТИКА УСПІШНОСТІ <<<" << endl;

    if (students.empty()) {
        cout << "Немає даних для розрахунку." << endl;
        return;
    }

    double sum = 0;
    for (int i = 0; i < students.size(); i++) {
        sum += students[i].avgScore;
    }

    double average = sum / students.size();

    cout << "Всього учнів у базі: " << students.size() << endl;
    cout << "Загальний середній бал по школі: " << fixed << setprecision(2) << average << endl;
}

// Головна функція з терміналом
int main() {
    // Встановлюємо правильне кодування для кирилиці
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    while (true) {
        cout << "\n=== МЕНЮ БАЗИ УЧНІВ ===" << endl;
        cout << "1. Додати нового учня" << endl;
        cout << "2. Переглянути всіх учнів" << endl;
        cout << "3. Розрахувати середній бал по школі" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";

        // Захист від введення букв замість цифр у меню
        if (!(cin >> choice)) {
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "[Помилка] Введіть цифру пункту меню!" << endl;
            continue;
        }

        if (choice == 0) break;

        if (choice == 1) {
            Student s;
            cout << "Прізвище (без пробілів): "; cin >> s.surname;
            cout << "Ім'я: "; cin >> s.name;
            cout << "Клас (напр. 10-А): "; cin >> s.grade;
            s.avgScore = getSafeDouble("Середній бал: ");
            cout << "Телефон батьків: "; cin >> s.parentPhone;

            saveToFile(s);
            cout << "[Успіх] Дані учня збережено!" << endl;
        }
        else if (choice == 2) {
            vector<Student> students = loadFromFile();
            showAllStudents(students);
        }
        else if (choice == 3) {
            vector<Student> students = loadFromFile();
            calculateSchoolAverage(students);
        }
        else {
            cout << "[Помилка] Такого пункту не існує." << endl;
        }
    }

    return 0;
}
