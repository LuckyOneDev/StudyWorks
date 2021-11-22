// Структуры ЛР-2
// 2 вариант
// Циклический список. Символьный. выборка из очереди элемента с заданным значением приоритета.
#include <iostream>

struct QItem {
	char value;
	int priority;
};

struct Queue {
	QItem** values;					// queue container
	int rear;                  // index of first element
	int front;                   // index of last element
	int count;          // number of elements currently in queue
	int size; 
};

void initQueue(Queue* queue, int size) {
	queue->rear = 0;
	queue->front = size;
	queue->count = 0;
	queue->size = size;
	queue->values = new QItem*[size];

	for (size_t i = 0; i < size; i++)
		queue->values[i] = NULL;
}

void printQueue(Queue* queue) {
	if (queue->size == 0) {
		std::cout << "Queue is not created" << std::endl;
		return;
	}

	std::cout << "\nQueue:\n";
	for (size_t i = 0; i < queue->size; i++)
	{
		if (queue->values[i] != NULL) {
				std::cout << "[" << i << "] " << queue->values[i]->value << " : " << queue->values[i]->priority << std::endl;
		}
		else {
				std::cout << "[" << i << "] NULL" << std::endl;
		}
	}
	
}

void insertQueue(Queue* queue, char val, int priority ) {
	if (queue->size == 0) {
		std::cout << "Queue is not created" << std::endl;
		return;
	}
	if (queue->count == queue->size) {
		std::cout << "Queue overflow!" << std::endl;
	}
	QItem* item = new QItem;
	item->value = val;
	item->priority = priority;
	queue->values[queue->rear] = item;
	queue->rear = (queue->rear + 1) % queue->size;
	queue->count++;
}

void clearQueue(Queue* queue) {
	if (queue->size != 0) {
		queue->rear = 0;
		queue->front = 0;
		queue->count = 0;
		queue->size = 0;
		delete[] *(queue->values);
		delete queue->values;
	}
}

QItem* getElementByPriority(Queue* queue, int priority) 
{
	if (queue->count == 0) {
		std::cout << "Empty queue!" << std::endl;
		return NULL;
	}

	for (size_t i = 0; i < queue->size; i++)
	{
		if (queue->values[i]->priority == priority) {
			QItem* val = queue->values[i];
			queue->values[i] = queue->values[queue->rear];
			queue->values[queue->rear] = NULL;
			queue->count--;
			return val;
		}
	}
	
	return NULL;

}


int main()
{
	srand(124);
	Queue* queue = new Queue;
	queue->size = 0;

	while (true) {
		int input;
		std::cout << "0) Exit" << std::endl;
		std::cout << "1) Create Queue" << std::endl;
		std::cout << "2) Print Queue" << std::endl;
		std::cout << "3) Add element" << std::endl;
		std::cout << "4) Clear Queue" << std::endl;
		std::cout << "5) Get by priority" << std::endl;

		std::cin >> input;

		switch (input)
		{
		case 0:
			return 0;
			break;
		case 1:
			std::cout << "Size: ";
			std::cin >> input;
			initQueue(queue, input);
			break;
		case 2:
			printQueue(queue);
			break;
		case 3:
			std::cout << "Value: ";
			char character;
			std::cin >> character;
			std::cout << std::endl;
			std::cout << "Priority: ";
			int priority;
			std::cin >> priority;
			insertQueue(queue, character, priority);
			break;
		case 4:
			clearQueue(queue);
			break;
		case 5:
			std::cout << "Priority: ";
			std::cin >> input;
			auto result = getElementByPriority(queue, input);
			if (result != NULL) {
				std::cout << "Value: " << result->value << std::endl;
			}
			else {
				std::cout << "Value not found"  << std::endl;
			}
			
			break;
		}
	}
}
