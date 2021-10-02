#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>

//Выводит элементы массива seq размера size и добавляет перед ним строку title. 
//В скобках выводится размер массива.
//title+[sequence](size)
void printSequence(int* seq, int size, const char* title = "") {
    std::cout << title;
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
        std::cout << "INT_MAX" << "](" << size << ")\n";
    }
    else {
        std::cout << seq[size - 1] << "](" << size << ")\n";
    }
}

int* generateRandomSequence(int size) {
    int* arr = new int[size]; //Выделение памяти
    for (int i = 0; i < size; i++)
        arr[i] = rand();  //Заполнение массива
    return arr;
}

void Selection_Sort(int* arr, int n, bool fullPrint = false, std::ofstream str = std::ofstream() ) {
    if (fullPrint) {
        for (int i = 0; i < n - 1; i++) {
            int smallest = i;
            for (int j = 0; j < n; j++) {
                if (arr[j] < arr[smallest]) {
                    smallest = j;
                }
            }
            std::swap(arr[i], arr[smallest]);
            printSequence(arr, n);
        }
    }
    else {
        for (int i = 0; i < n - 1; i++) {
            int smallest = i;
            for (int j = 0; j < n; j++) {
                if (arr[j] < arr[smallest]) {
                    smallest = j;
                }
            }
            std::swap(arr[i], arr[smallest]);
        }
    }
    
}

void Insertion_Sort(int* arr, int n, bool fullPrint = false, std::ofstream str = std::ofstream()) {
    if (fullPrint) {
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j > 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
            printSequence(arr, n);
        }
    }
    else {
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j > 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
}

void Merge(int* arr, int left, int mid, int right) {
    int leftSubArraySize = mid - left + 2;
    int rightSubArraySize = right - mid + 1;

    int* leftSubArray = new int[leftSubArraySize];
    int* rightSubArray = new int[rightSubArraySize];

    for (int i = 0; i < leftSubArraySize - 1; i++) {
        leftSubArray[i] = arr[left + i];
    }

    leftSubArray[leftSubArraySize - 1] = INT_MAX;

    for (int i = 0; i < rightSubArraySize - 1; i++) {
        rightSubArray[i] = arr[mid + 1 + i];
    }
        
    rightSubArray[rightSubArraySize - 1] = INT_MAX;

    int lCounter = 0;
    int rCounter = 0;

    for (int i = left; i <= right; i++)
    {
        if (leftSubArray[lCounter] < rightSubArray[rCounter]) {
            arr[i] = leftSubArray[lCounter];
            lCounter++;
        }
        else {
            arr[i] = rightSubArray[rCounter];
            rCounter++;
        }
    }

    delete[] leftSubArray;
    delete[] rightSubArray;
}

void Merge_Sort(int* arr, int left, int right, bool fullPrint = false, std::ofstream str = std::ofstream() ) {
    if (fullPrint) {
        if (right != left) {
            int mid = (left + right) / 2;
            Merge_Sort(arr, left, mid, true);
            Merge_Sort(arr, mid + 1, right, true);
            Merge(arr, left, mid, right);
            printSequence(arr, right + 1);
        }
    }
    else {
        if (left < right) {
            int q = (left + right) / 2;
            Merge_Sort(arr, left, q);
            Merge_Sort(arr, q + 1, right);
            Merge(arr, left, q, right);
        }
    }
    
}

template <typename ... Types>
long long timeTest(void (*function)(Types ... args), int* arr, Types ... args) {
    auto beginTime = std::chrono::steady_clock::now();
    function(args);
    auto endTime = std::chrono::steady_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - beginTime).count();
    return elapsedMs;
}


int main()
{
    //Инициализация рандомизатора
    srand(time(NULL));

    const int smallSize = 6;
    int* sequence = generateRandomSequence(smallSize);

    Selection_Sort(sequence, smallSize, true);

}