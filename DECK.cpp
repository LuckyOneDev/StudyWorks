// Структуры ЛР-2
// 5 вариант
// Деки. вещественный элемент. Выборка эл из начала. Добавление эл. в конец
#include <iostream>

struct DeckEntry {
    float value;
    DeckEntry* prev;
    DeckEntry* next;
};

void generateRandomDeck(DeckEntry* begin, DeckEntry* end, int size) {
    begin->value = 10000.f * (float)rand() / RAND_MAX;
    begin->prev = NULL;
    end->next = NULL;

    DeckEntry* previous = begin;
    for (int i = 0; i < size - 2; i++)
    {
        DeckEntry* current = new DeckEntry;

        current->value = 10000.f * (float)rand() / RAND_MAX;

        current->prev = previous;
        previous->next = current;

        previous = current;
    }

    previous->next = end;

    end->value = 10000.f * (float)rand() / RAND_MAX;
    end->prev = previous;
}

void printDeck(DeckEntry* begin) {
    DeckEntry* current = begin;
    std::cout << "DECK:\n";
    int counter = 0;
    while (current != NULL) {
        std::cout << '[' << counter << "] " << current->value << std::endl;
        counter++;
        current = current->next;
    }
}

float PopFront(DeckEntry* begin) {
    DeckEntry* next = begin->next;
    float val = begin->value;

    begin->value = next->value;
    begin->next = next->next;
    begin->prev = NULL;

    return val;
}

void PushBack(DeckEntry* end, float value) {
    DeckEntry* newend = new DeckEntry;
    
    newend->value = value;
    newend->prev = end->prev;
    newend->next = NULL;

    end->next = newend;
}

void clearDeck(DeckEntry* &begin, DeckEntry* &end) {
    
    DeckEntry* current = begin;

    while (current != NULL) {
        DeckEntry* buf = current;
        current = current->next;
        delete buf;
    }
    
    begin = NULL;
    end = NULL;
}

int main()
{
    srand(1109);

    int input = 0;

    DeckEntry* begin = NULL;
    DeckEntry* end = NULL;

    while (true) {
        std::cout << "0) Exit" << std::endl;
        std::cout << "1) Create Deck" << std::endl;
        std::cout << "2) Print Deck" << std::endl;
        std::cout << "3) Clear Deck" << std::endl;
        std::cout << "4) Pop Front" << std::endl;
        std::cout << "5) Push Back" << std::endl;

        std::cin >> input;

        switch (input)
        {
        case 0:
            return 0;
            break;
        case 1:
            std::cout << "Size: ";
            std::cin >> input;
            begin = new DeckEntry;
            end = new DeckEntry;
            generateRandomDeck(begin, end, input);
            break;
        case 2:
            printDeck(begin);
            break;
        case 3:
            clearDeck(begin, end);
            break;
        case 4:
            std::cout << "Front value: " << PopFront(begin) << std::endl; 
            break;
        case 5:
            std::cout << "Value: ";
            std::cin >> input;
            PushBack(end, input);
            break;
        }
    }
    
}
