#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>

//Выводит элементы массива seq размера size в квадратных скобках
void printSequence(int* seq, int size) {
    std::cout << "[";
    for (int i = 0; i < size - 1; i++)
    {
        if (seq[i] == INT_MAX) {
            std::cout << "INT_MAX" << ", ";
        }
        else {
            std::cout << seq[i] << ", ";
        }

    }

    if (seq[size - 1] == INT_MAX) {
        std::cout << "INT_MAX" << "]\n";
    }
    else {
        std::cout << seq[size - 1] << "]\n";
    }
}

int* generateRandomSequence(int size) {
    int* arr = new int[size]; //Выделение памяти
    for (int i = 0; i < size; i++)
        arr[i] = rand();  //Заполнение массива
    return arr;
}

int* generateIncreaseSequence(int size) {
  int* arr = new int[size]; //Выделение памяти
  int step = INT_MAX / size; // Вычисление шага
  for (int i = 0; i < size; i++)
    arr[i] = i * step + rand() % step;  //Заполнение массива
  return arr;
}

int* generateDecreaseSequence(int size) {
  int* arr = new int[size]; //Выделение памяти
  int step = INT_MAX / size; // Вычисление шага
  for (int i = size - 1; i >= 0; i--)
    arr[i] = (size - i - 1) * step + rand() % step;  //Заполнение массива
  return arr;
}


void Selection_Sort(int* arr, int arrSize, bool fullPrint = false, int* compareCount = NULL, int* transposeCount = NULL) {
    (*compareCount) = 0;
    if (fullPrint) {
        (*compareCount)++;
        for (int i = 0; i < arrSize - 1; i++) {
            (*compareCount)++;
            int min = i;
            (*compareCount)++;
            for (int j = i + 1; j < arrSize; j++) {
                (*compareCount)++;
                (*compareCount)++;
                if (arr[j] < arr[min]) {
                    min = j;
                }
            }
            (*transposeCount) +=2;
            std::swap(arr[i], arr[min]);
            printSequence(arr, arrSize);
        }
    }
    else {
        (*compareCount)++;
        for (int i = 0; i < arrSize - 1; i++) {
            (*compareCount)++;
            int min = i;
            (*compareCount)++;
            for (int j = i + 1; j < arrSize; j++) {
                (*compareCount)++;
                (*compareCount)++;
                if (arr[j] < arr[min]) {
                    min = j;
                }
            }
            (*transposeCount) += 2;
            std::swap(arr[i], arr[min]);
        }
    }

}

int Partition(int* arr, int left, int right, int* compareCount = NULL, int* transposeCount = NULL) {
    int pivot = arr[right];    // pivot
    int i = (left - 1);  // Index of smaller element

    (*compareCount)++;
    for (int j = left; j <= right - 1; j++)
    {
        (*compareCount)++;
        // If current element is smaller than or
        // equal to pivot

        (*compareCount)++;
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            (*transposeCount) += 2;
            std::swap(arr[i], arr[j]);
        }
    }
    (*transposeCount) += 2;
    std::swap(arr[i + 1], arr[right]);
    return (i + 1);
}

// another draft
void Quick_Sort(int* arr, int left, int right, bool fullPrint = false, int maxSize = -1, int* compareCount = NULL, int* transposeCount = NULL) {
    if (fullPrint) {
        (*compareCount)++;
        if (left < right) {
            printSequence(arr, maxSize);

            int middle = Partition(arr, left, right, compareCount, transposeCount);

            Quick_Sort(arr, left, middle - 1, fullPrint, maxSize, compareCount, transposeCount);
            Quick_Sort(arr, middle + 1, right, fullPrint, maxSize, compareCount, transposeCount);

        }
    }
    else {
        (*compareCount)++;
        if (left < right) {

            int middle = Partition(arr, left, right, compareCount, transposeCount);

            Quick_Sort(arr, left, middle - 1, fullPrint, maxSize, compareCount, transposeCount);
            Quick_Sort(arr, middle + 1, right, fullPrint, maxSize, compareCount, transposeCount);

        }
    }
    

}

template <typename ... Types>
long long timeTest(void (*function)(Types ... args), Types ... args) {
    auto beginTime = std::chrono::steady_clock::now();
    function(args...);
    auto endTime = std::chrono::steady_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - beginTime).count();
    return elapsedMs;
}


int main()
{
    //Инициализация рандомизатора
    srand(time(NULL));

    const int smallSize = 7;
   
    std::cout << "TEST FOR SIZE: " << smallSize << std::endl;

    int* firstSequence = generateRandomSequence(smallSize);
    int* secondSequence = new int[smallSize];
    std::copy(firstSequence, firstSequence + smallSize, secondSequence);

    int compareCount = 0;
    int transposeCount = 0;
    Selection_Sort(firstSequence, smallSize, true, &compareCount, &transposeCount);
    std::cout << "Selection_Sort. compareCount: " << compareCount << " transposeCount: " << transposeCount << std::endl;
    std::cout << std::endl;
   

    compareCount = 0;
    transposeCount = 0;
    Quick_Sort(secondSequence, 0, smallSize - 1, true, smallSize, &compareCount, &transposeCount);
    std::cout << "Quick_Sort. compareCount: " << compareCount << " transposeCount: " << transposeCount << std::endl;

    delete [] firstSequence;
    delete [] secondSequence;

    std::ofstream file("Sorts.csv");
    file << "count" << ';' 
        << "Selection_sort_compareCount" << ';' 
        << "Selection_sort_transposeCount" << ';' 
        << "Selection_sort_time" << ';'
        << "Quick_sort_compareCount" << ';' 
        << "Quick_sort_transposeCount" << ';' 
        << "Quick_sort_time" << '\n';

    for (int i = 0; i < 7; i++)
    {
        int count = pow(10, i);
        //creating two same sequences
        firstSequence = generateRandomSequence(count);
        secondSequence = new int[count];
        std::copy(firstSequence, firstSequence + count, secondSequence);

        compareCount = 0;
        transposeCount = 0;
        auto time = timeTest(Selection_Sort, firstSequence, count, false, &compareCount, &transposeCount);
        
        file << count << ';' << compareCount << ';' << transposeCount << ';' << time << ';';

        compareCount = 0;
        transposeCount = 0;
        auto time = timeTest(Quick_Sort, secondSequence, 0, count - 1, false, count, &compareCount, &transposeCount);

        file << count << ';' << compareCount << ';' << transposeCount << ';' << time << '\n';


        delete[] firstSequence;
        delete [] secondSequence;

        std::cout << "Loop " << i << " complete" << std::endl;
    }

    file.close();
}
