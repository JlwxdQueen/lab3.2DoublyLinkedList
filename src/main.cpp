#include <windows.h>
#include <iostream>
#include "../include/tests.h"

void displayMenu() {
    std::cout << "Выберите тест для выполнения:" << std::endl;
    std::cout << "1. Базовые тесты" << std::endl;
    std::cout << "2. Сложный тест" << std::endl;
    std::cout << "3. Выход" << std::endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int choice;

    do {
        displayMenu();
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                makeTests();
            break;
            case 2:
                makeHardTest();
            break;
            case 3:
                std::cout << "Выход из программы." << std::endl;
            break;
            default:
                std::cout << "Неверный выбор, попробуйте снова." << std::endl;
        }
    } while (choice != 3);

    return 0;
}
