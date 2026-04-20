#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

// Допоміжна функція для підрахунку слів у реченні
int countWords(string sentence) {
    stringstream ss(sentence);
    string word;
    int count = 0;
    while (ss >> word) {
        count++;
    }
    return count;
}

// Функція для автоматичного створення текстового файлу
void createInputFileIfNotExists() {
    ifstream checkFile("input.txt");
    if (!checkFile.is_open()) {
        cout << "[Інфо] Файл input.txt не знайдено. Створюю автоматично..." << endl;
        ofstream newFile("input.txt");
        if (newFile.is_open()) {
            newFile << "Весна цього року видалася напрочуд теплою та сонячною." << endl;
            newFile << "Дерева вкрилися дрібними зеленими листочками, а в повітрі пахне свіжістю." << endl;
            newFile << "Птахи дзвінко співають з самого ранку." << endl;
            newFile << "Природа оживає." << endl;
            newFile << "Люди із задоволенням гуляють у парках, насолоджуючись лагідними променями сонця." << endl;
            newFile.close();
            cout << "[Інфо] Файл input.txt успішно створено та заповнено текстом." << endl << endl;
        }
    }
    else {
        checkFile.close();
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Тема 4. Робота з файлами та рядками ===" << endl;
    cout << "Завдання: Знайти речення з найменшою кількістю слів." << endl << endl;

    // Автоматичне створення файлу 
    createInputFileIfNotExists();

    // Відкриваємо файл для читання
    ifstream inFile("input.txt");
    // Відкриваємо файл для запису результату
    ofstream outFile("output.txt");

    if (!inFile.is_open()) {
        cout << "Помилка: Не вдалося відкрити або створити файл input.txt!" << endl;
        return 1;
    }

    string currentSentence;
    string minSentence = "";
    int minWords = -1;

    cout << "Зчитуємо дані з файлу input.txt..." << endl;
    cout << "------------------------------------------------" << endl;

    // Читаємо файл порядоково
    while (getline(inFile, currentSentence)) {
        if (currentSentence.empty()) {
            continue;
        }

        int currentWordsCount = countWords(currentSentence);
        cout << "Слів: " << currentWordsCount << " | Речення: " << currentSentence << endl;

        // Шукаємо мінімум
        if (minWords == -1 || (currentWordsCount > 0 && currentWordsCount < minWords)) {
            minWords = currentWordsCount;
            minSentence = currentSentence;
        }
    }

    cout << "------------------------------------------------" << endl;
    inFile.close();

    // Записуємо результат
    if (minWords != -1) {
        cout << "\nРЕЗУЛЬТАТ:" << endl;
        cout << "Речення з найменшою кількістю слів (" << minWords << "):" << endl;
        cout << minSentence << endl;

        outFile << minSentence << endl;
        cout << "\nДане речення успішно записано у файл output.txt!" << endl;
    }
    else {
        cout << "Файл порожній або не містить слів." << endl;
    }

    outFile.close();
    return 0;
}
