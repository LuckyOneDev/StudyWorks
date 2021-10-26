#include <iostream>

const int LIST_SIZE = 30;

struct listEntry {
	int value;
	listEntry* next;
};

int listGet(listEntry* list, int index) {
	listEntry* next = list;

	for (int i = 0; i < index; i++)
	{
		next = next->next;
	}

	return next->value;
}

// Устанавливает значение списка
listEntry* listSet(listEntry* list, int index, int value) {
	listEntry* next = list;

	for (int i = 0; i < index; i++)
	{
		next = next->next;
	}

	next->value = value;
	return next;
}

void deleteList(listEntry* list) {
	listEntry* current = list;
	while (current != NULL) {
		current = current->next;
		delete list;
		list = current;
	}
}

// Создаёт односвязный список, заполненный числами от 0 до size
listEntry* createList(int size) {
	listEntry* first = new listEntry;
	first->value = 0;
	first->next = NULL;

	listEntry* current = first;
	for (int i = 0; i < size; i++)
	{
		listEntry* next = new listEntry;
		next->value = i + 1;
		current->next = next;
		current = next;
	}

	current->next = NULL;

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
	while (current != NULL) {
		current = current->next;
		preNext = list;
		list = current;
	}
	delete preNext->next;
	preNext->next = NULL;
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

int main()
{
	listEntry* list = createList(LIST_SIZE);

	
	
	printList(list);

	int operation = -1;
	std::cout << "Choose operation:\n 1)pushFront\n 2)deleteEnd\n 3)findValue\n 4)exit\n";
	std::cin >> operation;
	switch (operation)
	{
	case 1:
		std::cout << "Value: ";
		std::cin >> operation;
		list = pushFront(list, operation);
		printList(list);
		break;
	case 2:
		deleteEnd(list);
		printList(list);
		break;
	case 3:
		std::cout << "Value: ";
		std::cin >> operation;
		std::cout << findInList(list, operation) << std::endl;
		break;
	case 4:
		deleteList(list);
		return 0;
		break;
	default:
		deleteList(list);
		return 0;
		break;
	}

}
