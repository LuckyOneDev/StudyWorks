// Структуры ЛР-2
// 2 вариант
// Циклический список. Символьный. выборка из очереди элемента с минимальным значением приоритета. Совпадение приоритетов разрешено.
#include <iostream>

struct ListEntry {
    char val;
    ListEntry* next;
    int priority;
};

ListEntry* generateRandomQueue(int size) {
    
    ListEntry* previous = new ListEntry;
    ListEntry* first = previous;
    for (size_t i = 0; i < size; i++)
    {
        ListEntry* current = new ListEntry;
        current->val = (char)(97 + rand() % 25);
        current->priority = rand();
        previous->next = current;
        previous = current;
    }

    previous->next = first;
    first->val = (char)(97 + rand() % 25);
    first->priority = rand();

    return first;
}

void printQueue(ListEntry* begin, int size) {
    for (size_t i = 0; i < size; i++)
    {
        std::cout << '[' << i << "] " << begin->val << " : " << begin->priority << std::endl;
        begin = begin->next;
    }
}

char getMin(ListEntry*& begin, int size) {
    // Finding min
    int minPriority = begin->priority;
    ListEntry* min = begin;
    ListEntry* preMin = NULL;

    ListEntry* pre;
    ListEntry* cur = begin;
    for (size_t i = 0; i < size; i++)
    {
        if (cur->priority < minPriority)
        {
            minPriority = cur->priority;
            min = cur;
        }
        cur = cur->next;
        preMin = begin;
    }// Min found

    char v = min->val;

    if (begin == min) {
        begin = begin->next;
    }
    else {
        preMin->next = min->next;
    }

    return v;
}

void addElement(ListEntry*& begin, char elem, int priority) {
    ListEntry* newElem = new ListEntry;
    newElem->next = begin;
    newElem->priority = priority;
    newElem->val = elem;

    begin = newElem;
}

void clearQueue(ListEntry*& begin, int size) {
    for (size_t i = 0; i < size; i++)
    {
        ListEntry* buf = begin;
        begin = begin->next;
        delete buf;
    }

    begin = NULL;
}

int main()
{
    srand(124);
    
    int listSize = 0;
    ListEntry* list = generateRandomQueue(15);
    
    while (true) {
        int input;
        std::cout << "0) Exit" << std::endl;
        std::cout << "1) Create Queue" << std::endl;
        std::cout << "2) Print Queue" << std::endl;
        std::cout << "3) Add element" << std::endl;
        std::cout << "4) Clear Queue" << std::endl;
        std::cout << "5) Get min" << std::endl;

        std::cin >> input;

        switch (input)
        {
        case 0:
            return 0;
            break;
        case 1:
            std::cout << "Size: ";
            std::cin >> listSize;
            list = generateRandomQueue(listSize);
            break;
        case 2:
            printQueue(list, listSize);
            break;
        case 3:
            std::cout << "Value: ";
            char character;
            std::cin >> character;
            std::cout << std::endl;
            std::cout << "Priority: ";
            int priority;
            std::cin >> priority;
            addElement(list, character, priority);
            listSize++;
            break;
        case 4:
            clearQueue(list, listSize);
            listSize = 0;
            break;
        case 5:
            std::cout << "Min: " << getMin(list, listSize) << std::endl;
            listSize--;
            break;
        }
    }
}
