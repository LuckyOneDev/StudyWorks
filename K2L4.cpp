#include <iostream>
#include <fstream>

const int LIST_SIZE = 30;

struct listEntry {
	int value = 0;
	listEntry* next = NULL;
};

// Создаёт односвязный список, заполненный числами от 0 до size
listEntry* createList(int size) {
	listEntry* first = new listEntry;

	listEntry* current = first;
	for (int i = 1; i < size; i++) {
		listEntry* next = new listEntry;
		next->value = i;
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

void printList(listEntry* list, std::string fname = "0") {
	listEntry* current = list;
	std::ofstream file;
	bool empty = ((fname.compare("0")) == 0);
	if (!empty)
		file.open(fname);

	std::ostream& output = !empty ? file : std::cout;
	int i = 0;
	while (current != NULL) {
		output << i << ": " << current->value << std::endl;
		current = current->next;
		i++;
	}

	if (!empty) {
		file.close();
	}
}

void removeByKey(listEntry* list, int key) {
	listEntry* current = list;
	listEntry* prev = NULL;
	while (current != NULL) {
		if (current->value == key) {
			if (prev != NULL) {
				prev->next = current->next;
				delete current;
				current = prev->next;
			} else {
				listEntry* next = current->next;
				delete current;
				current = next;
			}
			continue;
		}
		prev = current;
		current = current->next;
	}
}


int main() {
	listEntry* list = createList(LIST_SIZE);

	printList(list);
	std::string fname;
	int operation = -1;
	while (true) {
		std::cout << "Choose operation:\n 1)create\n 2)print\n 3)pushFront\n 4)deleteEnd\n 5)findValue\n 6)delete\n 7)remByK\n 8)exit\n";
		std::cin >> operation;
		switch (operation) {
		case 1:
			deleteList(list);
			std::cout << "New size: ";
			std::cin >> operation;
			list = createList(operation);
			break;
		case 2:
			std::cout << "Filename (0 for console): ";
			std::cin >> fname;
			printList(list, fname);
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
			std::cout << "Value: ";
			std::cin >> operation;
			removeByKey(list, operation);
			break;
		case 8:
			deleteList(list);
			list = NULL;
			return 0;
			break;
		default:
			break;
		}
	}
}
