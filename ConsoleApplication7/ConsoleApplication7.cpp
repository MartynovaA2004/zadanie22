// ConsoleApplication7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono> 

using namespace std;

// 1. Сортировка выбором
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

// 2. Сортировка вставками
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


// 3. Сортировка пузырьком
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


// 4. Сортировка слиянием

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Рекурсивная сортировка слиянием
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Находим середину массива

        // Рекурсивно сортируем две половины
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Объединяем отсортированные части
        merge(arr, left, mid, right);
    }
}


// 5. Быстрая сортировка
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


//  6. Сортировка Шелла 
void shellSort(vector<int>& arr, vector<int>& intervals) {
    int n = arr.size();
    for (int interval : intervals) {
        for (int i = interval; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
                arr[j] = arr[j - interval];
            }
            arr[j] = temp;
        }
    }
}

vector<int> intervals1 = { 5, 3, 1 };
vector<int> intervals2 = { 13, 4, 1 };
vector<int> intervals3 = { 10, 5, 2, 1 };



// 7. Пирамидальная сортировка

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Функция сортировки пирамидой
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Построение кучи (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Извлекаем элементы из кучи по одному
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Перемещаем текущий корень в конец
        heapify(arr, i, 0); // Вызываем heapify на уменьшенной куче
    }
}

// 8. Timsort
void timSort(vector<int>& arr) {
    int n = arr.size();
    const int minRun = 32;

    for (int i = 0; i < n; i += minRun) {
        insertionSort(arr, i, min(i + minRun - 1, n - 1));
    }

    for (int size = minRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = min(n - 1, left + size - 1);
            int right = min((left + 2 * size - 1), (n - 1));

            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

// 9. IntroSort
void introSort(vector<int>& arr, int low, int high, int depthLimit) {
    if (low < high) {
        if (depthLimit == 0) {
            heapSort(arr);
        }
        else {
            int pi = partition(arr, low, high);
            introSort(arr, low, pi - 1, depthLimit - 1);
            introSort(arr, pi + 1, high, depthLimit - 1);
        }
    }
}

void introSortHelper(vector<int>& arr) {
    int depthLimit = 2 * log2(arr.size());
    introSort(arr, 0, arr.size() - 1, depthLimit);
}




int main() {
    
    setlocale(LC_ALL, "Russian");

                  // ВВОД
    // Создаем вектор для тестирования
    vector<int> arr = { 64, 25, 12, 22, 11 };

    // Выводим неотсортированный массив
    cout << "Неотсортированный массив: ";
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;


                // ОБРАБОТКА
     
    
    //selectionSort(arr);                            // 1. Сортировка выбором    
    //insertionSort(arr);                            // 2. Сортировка вставками
    //bubbleSort(arr);                               // 3. Сортировка пузырьком
    //mergeSort(arr, 0, arr.size() - 1);             // 4. Сортировка слиянием   
    //quickSort(arr, 0, arr.size() - 1);             // 5. Быстрая сортировка
    //shellSort(arr, intervals1);                    // 6. Сортировка Шелла
    //heapSort(arr);                                 // 7. Пирамидальная сортировка
    //timSort(arr);                                  // 8. Timsort
    //introSortHelper(arr);                          // 9. IntroSort


                // ВЫВОД
    // Выводим отсортированный массив
    cout << "Отсортированный массив: ";
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;



    return 0;
}

