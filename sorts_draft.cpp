#include <algorithm>

void Selection_Sort(int * arr, int n) {
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

void Insertion_Sort(int * arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j > 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void Merge_Sort(int * arr, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        Merge_Sort(arr, p, q);
        Merge_Sort(arr, q + 1, r);
        Merge(arr, p, q, r);
    }
}

void Merge(int * arr, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int * b = new int[n1 + 1];
    int * c = new int[n2 + 1];

    //copy arr[p..q] to b[0..(n1-1)]
    //copy arr[(q+1)..r] to c[0..(n1-1)]

    b[n1] = INT_MAX;
    c[n2] = INT_MAX;

    int i = 0;
    int j = 0;

    for(int k = p; k <=r; k++) {
        if (b[i] <= c[j]) {
            arr[k] = b[i];
            i++;
        } else {
            arr[k] = c[j];
            j++;
        }
    }
}
        

