#include <iostream>

const int LIST_SIZE = 30;

struct listEntry {
	int value = 0;
	listEntry* next = NULL;
};

// Создаёт односвязный список, заполненный числами от 0 до size
listEntry* createList(int size) {
	listEntry* first = new listEntry;

	listEntry* current = first;
	for (int i = 0; i < size; i++) {
		listEntry* next = new listEntry;
		next->value = i + 1;
		current->next = next;
		current = next;
	}

	return first;
}

int findInList(listEntry* list, int value) {
	int index = -1;
	int i = 0;
	listEntry* current = list;
	while (current != NULL) {
		if (current->value == value) {
			index = i;
			break;
		}
		current = current->next;
		i++;
	}

	return index;
}

listEntry* pushFront(listEntry* list, int value) {
	listEntry* begin = new listEntry;
	begin->value = value;
	begin->next = list;
	return begin;
}

void deleteEnd(listEntry* list) {
	listEntry* current = list;
	listEntry* preNext = NULL;
	while (current->next != NULL) {
		preNext = current;
		current = current->next;
	}
	delete current;
	preNext->next = NULL;
}

void deleteList(listEntry* list) {
	listEntry* current = list;
	while (current != NULL) {
		listEntry* prev = current;
		current = current->next;
		delete prev;
	}
}

void printList(listEntry* list) {
	int i = 0;
	listEntry* current = list;
	while (current != NULL) {
		std::cout << i << ": " << current->value << std::endl;
		current = current->next;
		i++;
	}
}

int main() {
	listEntry* list = createList(LIST_SIZE);

	printList(list);

	int operation = -1;
	while (true) {
		std::cout << "Choose operation:\n 1)create\n 2)print\n 3)pushFront\n 4)deleteEnd\n 5)findValue\n 6)delete\n 7)exit\n";
		std::cin >> operation;
		switch (operation) {
		case 1:
			deleteList(list);
			std::cout << "Value: ";
			std::cin >> operation;
			list = createList(operation);
		case 2:
			printList(list);
			break;
		case 3:
			std::cout << "Value: ";
			std::cin >> operation;
			list = pushFront(list, operation);
			break;
		case 4:
			deleteEnd(list);
			break;
		case 5:
			std::cout << "Value: ";
			std::cin >> operation;
			std::cout << findInList(list, operation) << std::endl;
			break;
		case 6:
			deleteList(list);
			list = NULL;
			break;
		case 7:
			deleteList(list);
			list = NULL;
			return 0;
			break;
		default:
			break;
		}
	}
}
