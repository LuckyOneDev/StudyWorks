// Структуры ЛР-2
// 2 вариант
// Циклический список. Символьный. выборка из очереди элемента с заданным значением приоритета.
#include <iostream>

// Структура представляет собой элемент очереди с приоритетом
struct PQItem {
	char value; // Значение очереди
	int priority; // Приоритет в очереди
};

// Структура представляет собой очередь с приоритеотм
struct PQueue {
	PQItem** values; // Значения очереди
	int rear; // Индекс свободного места для вставки
	int front; // Индекс старейшего (по порядку вставок) элемента
	int count; // Количество элементов
	int size;  // Размер очереди
};

// Инициализирует созданную очередь
// queue - указазатель на очередь
// size = максимальный размер очереди
void initPQueue(PQueue* queue, int size) {
	queue->rear = 0;
	queue->front = 0;
	queue->count = 0;
	queue->size = size;
	queue->values = new PQItem*[size]; //Создаём массив указателей

	// Инициализируем массив нулями
	for (size_t i = 0; i < size; i++)
		queue->values[i] = NULL;
}

// Выводит элементы очереди на печать поочерёдно
// queue - указазатель на очередь
void printPQueue(PQueue* queue) {

	// Если очередь не создана, то выводим ошибку
	if (queue->size == 0) {
		std::cout << "Queue is not created" << std::endl;
		return;
	}

	// Выводим заголовок
	std::cout << "\nQueue:\n";
	// Проходимся по каждому элементу очереди
	for (size_t i = 0; i < queue->size; i++)
	{
		// Проверяем на NULL, чтобы корректно отработать все возможные значения
		if (queue->values[i] != NULL) {
				std::cout << "[" << i << "] " << queue->values[i]->value << " : " << queue->values[i]->priority << std::endl;
		}
		else {
				std::cout << "[" << i << "] NULL" << std::endl;
		}
	}
	
}
// Вставляет в очередь новый элемент
// queue - указазатель на очередь
// val - значение
// priority - приоритет значения
void insertIntoPQueue(PQueue* queue, char val, int priority ) {
	// Если очередь не создана, то выводим ошибку
	if (queue->size == 0) {
		std::cout << "Queue is not created" << std::endl;
		return;
	}
	// Если очередь уже заполнена, то выводим ошибку
	if (queue->count == queue->size) {
		std::cout << "Queue overflow!" << std::endl;
	}
	// Создаём новый элемент из данных
	PQItem* item = new PQItem;
	item->value = val;
	item->priority = priority;

	// Вставляем элемент в свободное место
	queue->values[queue->rear] = item;
	// Циклически сдвигаем индекс свободного места
	queue->rear = (queue->rear + 1) % queue->size;
	// Число элементов увеличивается на 1
	queue->count++;
}

// Удаляет очередь и освобождает занятые ей ресурсы
// queue - указазатель на очередь
void deletePQueue(PQueue* queue) {
	// Проверяем, создана ли очередь. Иначе нет смысла её удалять
	if (queue->size != 0) {
		queue->rear = 0;
		queue->front = 0;
		queue->count = 0;
		queue->size = 0;
		delete[] *(queue->values);
		delete queue->values;
	}
}
// Выбирает из очереди элемент с заданным значением
// queue - указазатель на очередь
// priority - нужный приоритет
// Возвращает указатель на элемент
PQItem* getElementByPriority(PQueue* queue, int priority) 
{
	// Если в очереди нет элементов, то выводим ошибку
	if (queue->count == 0) {
		std::cout << "Empty queue!" << std::endl;
		return NULL;
	}
	
	// Проходим по каждому элементу очереди
	for (size_t i = 0; i < queue->size; i++)
	{
		// Если у элемента нужный приоритет
		if (queue->values[i]->priority == priority) {
			// Запоминаем значения нужного элемента
			PQItem* val = new PQItem;
			val->value = queue->values[i]->value;
			val->priority = queue->values[i]->priority;

			// Меняем местами с front элементом
			queue->values[i] = queue->values[queue->front];
			// Устанавливаем front в NULL
			queue->values[queue->front] = NULL;
			// Число элементов уменьшается на 1
			queue->count--;
			
			// Циклически сдвигаем front
			queue->front = (queue->front + 1) % queue->size;

			return val;
		}
	}
	
	// Элемент не найден. Возвращаем NULL
	return NULL;

}


int main()
{
	// Инциализируем генератор случайных чисел
	srand(124);

	// Создаём очередь
	PQueue* queue = new PQueue;
	// Устанавливаем размер в 0, чтобы пометить, что очередь не инициализирована
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
			initPQueue(queue, input);
			break;
		case 2:
			printPQueue(queue);
			break;
		case 3:
			std::cout << "Value: ";
			char character;
			std::cin >> character;
			std::cout << std::endl;
			std::cout << "Priority: ";
			int priority;
			std::cin >> priority;
			insertIntoPQueue(queue, character, priority);
			break;
		case 4:
			deletePQueue(queue);
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
