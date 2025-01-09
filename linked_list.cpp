#include <iostream>
#include <stdexcept>

class Node { //создание узла
public:
    double data;
    Node* next;

public:
    Node(double data) {
        this->data = data;
        this->next = nullptr;
    }
};

class OneLinkedList {
public:
    Node* head, * tail;

public:
    OneLinkedList() { //обнуляем значения для нового узла
        this->head = this->tail = nullptr;
    }

    ~OneLinkedList() { //деструктор, очищаем память
        while (head != nullptr) pop_front();
    }

    void pop_front() {   //удаление первого элемента
        if (head == nullptr) return;
        Node* node = head;
        head = head->next;
        delete node;
        if (head == nullptr) tail = nullptr; // Обновляем tail, если список пуст
    }

    void push_back(double data) { //добавление новых элементов конец
        Node* node = new Node(data);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    size_t size() const { // размер списка
        size_t count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    OneLinkedList(const OneLinkedList& other) { //конструктор копирования
    head = nullptr;
    tail = nullptr;
    Node* current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
        }
    }

    OneLinkedList operator+(const OneLinkedList& other) const { //сложение
        if (this->size() != other.size()) {
            throw std::invalid_argument("Lists must be of the same size for addition.");
        }

        OneLinkedList result;
        Node* current1 = this->head;
        Node* current2 = other.head;

        while (current1 != nullptr && current2 != nullptr) {
            result.push_back(current1->data + current2->data);
            current1 = current1->next;
            current2 = current2->next;
        }

        return result;
    }

    OneLinkedList operator-(const OneLinkedList& other) const { //вычитание
        if (this->size() != other.size()) {
            throw std::invalid_argument("Lists must be of the same size for subtraction.");
        }

        OneLinkedList result;
        Node* current1 = this->head;
        Node* current2 = other.head;

        while (current1 != nullptr && current2 != nullptr) {
            result.push_back(current1->data - current2->data);
            current1 = current1->next;
            current2 = current2->next;
        }

        return result;
    }

    OneLinkedList operator*(const OneLinkedList& other) const { // умножение
        if (this->size() != other.size()) {
            throw std::invalid_argument("Lists must be of the same size for multiplication.");
        }

        OneLinkedList result;
        Node* current1 = this->head;
        Node* current2 = other.head;

        while (current1 != nullptr && current2 != nullptr) {
            result.push_back(current1->data * current2->data);
            current1 = current1->next;
            current2 = current2->next;
        }

        return result;
    }

    OneLinkedList operator/(const OneLinkedList& other) const { // деление
        if (this->size() != other.size()) {
            throw std::invalid_argument("Lists must be of the same size for division.");
        }

        OneLinkedList result;
        Node* current1 = this->head;
        Node* current2 = other.head;

        while (current1 != nullptr && current2 != nullptr) {
            if (current2->data == 0) {
                throw std::invalid_argument("Division by zero is not allowed.");
            }
            result.push_back(current1->data / current2->data);
            current1 = current1->next;
            current2 = current2->next;
        }

        return result;
    }
};

int main() {    
        OneLinkedList lst1, lst2;
        lst1.push_back(1);
        lst1.push_back(12);
        lst2.push_back(2);
        lst2.push_back(24);

        OneLinkedList sum = lst1 + lst2;
        OneLinkedList diff = lst1 - lst2;
        OneLinkedList prod = lst1 * lst2;
        OneLinkedList quot = lst1 / lst2;

        std::cout << "Sum: ";
        for (Node* node = sum.head; node != nullptr; node = node->next)
            std::cout << node->data << " ";
        std::cout << std::endl;

        std::cout << "Difference: ";
        for (Node* node = diff.head; node != nullptr; node = node->next)
            std::cout << node->data << " ";
        std::cout << std::endl;

        std::cout << "Product: ";
        for (Node* node = prod.head; node != nullptr; node = node->next)
            std::cout << node->data << " ";
        std::cout << std::endl;

        std::cout << "Quotient: ";
        for (Node* node = quot.head; node != nullptr; node = node->next)
            std::cout << node->data << " ";
        std::cout << std::endl;

    return 0;
}