#include "ContainerFunctions.h"

// Функция для вывода всех объектов в стеке
void print(const MyStack<PrintedEdition*>& stack) {
    if (stack.any()) {
        std::cout << "Container is empty" << std::endl;
        return;
    }

    std::cout << "\n--- Container Content ---\n";

    // Создаем копию стека для перебора
    MyStack<PrintedEdition*> tempStack = stack;
    MyStack<PrintedEdition*> reverseStack;

    // Сначала извлекаем все элементы и помещаем их в обратном порядке
    while (!tempStack.any()) {
        reverseStack.append(tempStack.get());
        tempStack.pop();
    }

    // Теперь выводим элементы и восстанавливаем их в исходный стек
    int index = 0;
    while (!reverseStack.any()) {
        PrintedEdition* item = reverseStack.get();
        std::cout << "[" << index << "] ";
        item->show();
        reverseStack.pop();
        index++;
    }

    std::cout << "------------------------\n";
}

// Функция для удаления объекта по индексу
void remove(MyStack<PrintedEdition*>& stack, int index) {
    if (stack.any()) {
        std::cout << "Container is empty" << std::endl;
        return;
    }

    // Копируем стек для операции
    MyStack<PrintedEdition*> tempStack;
    MyStack<PrintedEdition*> resultStack;

    // Перекладываем все элементы во временный стек
    while (!stack.any()) {
        tempStack.append(stack.get());
        stack.pop();
    }

    // Перекладываем обратно, пропуская элемент с нужным индексом
    int currentIndex = 0;
    PrintedEdition* itemToRemove = nullptr;

    while (!tempStack.any()) {
        PrintedEdition* current = tempStack.get();
        tempStack.pop();

        if (currentIndex != index) {
            resultStack.append(current);
        } else {
            itemToRemove = current;
        }
        currentIndex++;
    }

    // Перекладываем обратно в исходный стек
    while (!resultStack.any()) {
        stack.append(resultStack.get());
        resultStack.pop();
    }

    // Удаляем объект, если нашли его
    if (itemToRemove) {
        delete itemToRemove;
        std::cout << "Item at index " << index << " removed successfully" << std::endl;
    } else {
        std::cout << "Index " << index << " is out of range" << std::endl;
    }
}

// Функция для очистки стека и удаления всех объектов
void clear(MyStack<PrintedEdition*>& stack) {
    if (stack.any()) {
        std::cout << "Container is already empty" << std::endl;
        return;
    }

    while (!stack.any()) {
        PrintedEdition* item = stack.get();
        delete item;  // Удаляем объект
        stack.pop();  // Удаляем указатель из стека
    }

    std::cout << "Container cleared successfully" << std::endl;
}
