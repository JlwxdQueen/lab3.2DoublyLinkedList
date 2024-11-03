#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <ostream>
#include <stdexcept>

template <typename T>
struct Element {
    T data;
    Element<T>* next;
    Element<T>* prev;
};

template <typename T>
class DoublyLinkedList {
    Element<T>* begin;      // Указатель на первый элемент
    Element<T>* end;        // Указатель на последний элемент
    int count;              // Количество элементов в списке

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    [[nodiscard]] bool isEmpty() const;                 // Метод для проверки списка на наличие элементов
    Element<T>* createElement(const T& data);           // Метод для создания элемента
    Element<T>* move(int index);                        // Метод для перемещения к элементу перед указанным индексом
    Element<T>* find(int index);                        // Метод для нахождения элемента по индексу
    Element<T>* getBegin() const;                       // Метод для получения ссылки на первый элемент
    Element<T>* getEnd() const;                         // Метод для получения ссылки на последний элемент
    void addEndElemToEmptyList(const T& data);          // Метод для добавления элемента в конец пустого списка
    void addEndElemToList(const T& data);               // Метод для добавления элемента в конец непустого списка
    void addBeginElemToList(const T& data);             // Метод для добавления элемента в начало списка
    void addCenterElemToList(const T& data, int index); // Метод для добавления элемента в центр списка
    void pop_front();                                   // Метод для удаления элемента из начала списка
    void pop_back();                                    // Метод для удаления элемента из конца списка
    void removeElemFromList(const T& data);             // Метод для удаления элемента через его содержимое
    void removeIndexFromList(int index);                // Метод для удаления элемента через его индекс
    bool contains(const T& data) const;                 // Метод для проверки на нахождения элемента в списке
    void unique();                                      // Метод для удаления повторяющихся элементов
    void sort();                                        // Метод для сортировки списка
    [[nodiscard]] int size() const;                     // Метод для получения размера списка
    void printList() const;                             // Метод для вывода списка в консоль

};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : begin(nullptr), end(nullptr), count(0) {}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (!isEmpty()) {
        pop_front();
    }
}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return count == 0;
}

template<typename T>
Element<T>* DoublyLinkedList<T>::createElement(const T& data) {
    auto* elem = new Element<T>;
    elem->data = data;
    elem->next = nullptr;
    elem->prev = nullptr;
    return elem;
}

template<typename T>
Element<T>* DoublyLinkedList<T>::move(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс за границами списка.");
    }

    Element<T>* current;

    if (index < count / 2) {
        current = begin;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
    } else {
        current = end;
        for (int i = count - 1; i > index; i--) {
            current = current->prev;
        }
    }
    return current;
}

template<typename T>
Element<T>* DoublyLinkedList<T>::find(const int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс за границами допустимого диапазона");
    }

    Element<T>* current;

    if (index < count / 2) {
        current = begin;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
    } else {
        current = end;
        for (int i = count - 1; i > index; i--) {
            current = current->prev;
        }
    }

    return current;
}

template<typename T>
void DoublyLinkedList<T>::addEndElemToEmptyList(const T& data) {
    Element<T>* elem = createElement(data);
    begin = end = elem;
    count++;
}

template<typename T>
void DoublyLinkedList<T>::addEndElemToList(const T& data) {
    Element<T>* elem = createElement(data);
    elem->prev = end;

    if (end != nullptr) {
        end->next = elem;
    }

    end = elem;
    count++;
}

template<typename T>
void DoublyLinkedList<T>::addBeginElemToList(const T& data) {
    Element<T>* elem = createElement(data);
    elem->next = begin;
    begin->prev = elem;
    begin = elem;
    count++;
}

template<typename T>
void DoublyLinkedList<T>::addCenterElemToList(const T& data, int index) {
    if (index <= 0 || index >= count) {
        throw std::out_of_range("Индекс за границами допустимого диапазона");
    }

    Element<T>* elemPrev = move(index - 1);
    Element<T>* elemCur = elemPrev->next;
    Element<T>* elemIns = createElement(data);

    elemIns->next = elemCur;
    elemIns->prev = elemPrev;

    elemPrev->next = elemIns;
    if (elemCur != nullptr) {
        elemCur->prev = elemIns;
    }

    count++;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (isEmpty()) {
        std::cerr << "Невозможно удалить элемент из пустого списка." << std::endl;
        return;
    }
    auto elem = begin;
    begin = begin->next;
    if (begin != nullptr) {
        begin->prev = nullptr;
    } else {
        end = nullptr;
    }
    delete elem;
    count--;
}

template<typename T>
void DoublyLinkedList<T>::removeIndexFromList(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Индекс за границами допустимого диапазона");
    }
    Element<T>* elem = move(index);
    Element<T>* elemPrev = elem->prev;
    Element<T>* elemNext = elem->next;
    elemPrev->next = elemNext;
    elemNext->prev = elemPrev;
    delete elem;
    count--;
}

template<typename T>
void DoublyLinkedList<T>::removeElemFromList(const T& data) {
    Element<T>* it = begin;

    while (it != nullptr) {
        if (it->data == data) {
            if (it->prev != nullptr) {
                it->prev->next = it->next;
            } else {
                begin = it->next;
            }

            if (it->next != nullptr) {
                it->next->prev = it->prev;
            } else {
                end = it->prev;
            }

            delete it;
            count--;
            return;
        }
        it = it->next;
    }

    std::cerr << "Элемент не найден" << std::endl;
}


template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (isEmpty()) {
        std::cerr << "Невозможно удалить элемент из пустого списка." << std::endl;
        return;
    }
    auto elem = end;
    end = end->prev;
    if (end != nullptr) {
        end->next = nullptr;
    } else {
        begin = nullptr;
    }
    delete elem;
    count--;
}

template<typename T>
Element<T>* DoublyLinkedList<T>::getBegin() const {
    return begin;
}

template<typename T>
Element<T>* DoublyLinkedList<T>::getEnd() const {
    return end;
}

template<typename T>
bool DoublyLinkedList<T>::contains(const T &data) const {
    Element<T>* current = begin;

    while (current != nullptr) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }

    return false;
}

template<typename T>
void DoublyLinkedList<T>::unique() {
    if (isEmpty()) {
        std::cerr << "Список пуст" << std::endl;
        return;
    }

    Element<T>* current = begin;
    while (current != nullptr) {
        Element<T>* runner = current->next;

        while (runner != nullptr) {
            if (runner->data == current->data) {
                const Element<T>* toDelete = runner;

                if (runner->prev != nullptr) {
                    runner->prev->next = runner->next;
                }
                if (runner->next != nullptr) {
                    runner->next->prev = runner->prev;
                }

                if (runner == end) {
                    end = runner->prev;
                }

                runner = runner->next;
                delete toDelete;
                count--;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

template<typename T>
void DoublyLinkedList<T>::sort() {
    if (isEmpty() || count == 1) {
        return;
    }

    Element<T>* sorted = nullptr;
    Element<T>* current = begin;

    while (current != nullptr) {
        Element<T>* next = current->next;
        current->next = nullptr;
        current->prev = nullptr;

        if (sorted == nullptr || sorted->data >= current->data) {
            current->next = sorted;
            if (sorted != nullptr) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
            Element<T>* temp = sorted;

            while (temp->next != nullptr && temp->next->data <= current->data) {
                temp = temp->next;
            }

            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            temp->next = current;
            current->prev = temp;
        }

        current = next;
    }

    begin = sorted;

    Element<T>* last = begin;
    while (last != nullptr && last->next != nullptr) {
        last = last->next;
    }
    end = last;
}

template<typename T>
int DoublyLinkedList<T>::size() const {
    return count;
}

template<typename T>
void DoublyLinkedList<T>::printList() const {
    Element<T>* current = begin;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
}


#endif
