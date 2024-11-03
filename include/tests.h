#ifndef TESTS_H
#define TESTS_H

#include <random>
#include <iostream>
#include "DoublyLinkedList.h"

inline void makeTests() {
    DoublyLinkedList<int> list;

    // Тест 1: Проверка на пустой список
    std::cout << "Тест 1: Проверка на пустой список" << std::endl;
    std::cout << "Список пуст: " << (list.isEmpty() ? "PASS" : "FAIL") << std::endl;

    // Тест 2: Добавление элементов
    std::cout << "Тест 2: Добавление элементов" << std::endl;
    list.addEndElemToEmptyList(30);
    list.addEndElemToList(10);
    list.addEndElemToList(40);
    list.addEndElemToList(20);
    list.addEndElemToList(120);
    std::cout << "Список после добавления: ";
    list.printList();
    std::cout << std::endl;

    // Тест 3: Проверка размера
    std::cout << "Тест 3: Проверка размера" << std::endl;
    std::cout << "Размер списка: " << list.size() << " (Ожидалось 5): " << (list.size() == 5 ? "PASS" : "FAIL") << std::endl;

    // Тест 4: Проверка наличия элемента
    std::cout << "Тест 4: Проверка наличия элемента" << std::endl;
    std::cout << "Содержит 20: " << (list.contains(20) ? "PASS" : "FAIL") << std::endl;
    std::cout << "Содержит 100: " << (list.contains(100) ? "PASS" : "FAIL") << std::endl;

    // Тест 5: Удаление элемента
    std::cout << "Тест 5: Удаление элемента" << std::endl;
    list.removeElemFromList(20);
    std::cout << "Список после удаления 20: ";
    list.printList();
    std::cout << std::endl;

    // Тест 6: Удаление элемента по индексу
    std::cout << "Тест 6: Удаление элемента по индексу" << std::endl;
    list.removeIndexFromList(1); // Удаляем элемент с индексом 1 (10)
    std::cout << "Список после удаления по индексу 1: ";
    list.printList();
    std::cout << std::endl;

    // Тест 7: Удаление повторяющихся элементов
    std::cout << "Тест 7: Удаление повторяющихся элементов" << std::endl;
    list.addEndElemToList(40); // Добавляем повторяющийся элемент
    list.unique();
    std::cout << "Список после удаления повторяющихся элементов: ";
    list.printList();
    std::cout << std::endl;

    // Тест 8: Сортировка
    std::cout << "Тест 8: Сортировка" << std::endl;
    list.addEndElemToList(15);
    list.addEndElemToList(5);
    list.sort();
    std::cout << "Список после сортировки: ";
    list.printList();
    std::cout << std::endl;

    // Тест 9: Удаление всех элементов
    std::cout << "Тест 9: Удаление всех элементов" << std::endl;
    while (!list.isEmpty()) {
        list.pop_back();
    }
    std::cout << "Список после удаления всех элементов: ";
    list.printList();
    std::cout << "Список пуст: " << (list.isEmpty() ? "PASS" : "FAIL") << std::endl;
}

inline void makeHardTest() {
    DoublyLinkedList<int> list;

    list.addEndElemToEmptyList(1);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-999, 999);

    for (int i = 0; i < 1000; ++i) {
        int randomValue = dis(gen);
        list.addEndElemToList(randomValue);
    }

    list.sort();

    std::cout << "Список после сортировки:" << std::endl;
    list.printList();
    std::cout << std::endl;
}

#endif
