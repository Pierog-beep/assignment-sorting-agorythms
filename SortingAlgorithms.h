//
// Created by pierog on 3/23/26.
//

#ifndef UNTITLED_SORTING_ALGORITHMS_H
#define UNTITLED_SORTING_ALGORITHMS_H
#include <vector>

namespace SortingAlgorithms {
    class HeapSort {
        template<typename T>
        static void heapifyDown(std::vector<T> &arr, int size, int root) {
            int largest = root;
            int left = 2 * root + 1;
            int right = 2 * root + 2;

            if (left < size && arr[left] > arr[largest])
                largest = left;

            if (right < size && arr[right] > arr[largest])
                largest = right;

            if (largest != root) {
                std::swap(arr[root], arr[largest]);
                heapifyDown(arr, size, largest);
            }
        }

        template<typename T>
        static void buildMaxHeap(std::vector<T> &arr, int size) {
            for (int i = size / 2 - 1; i >= 0; i--) {
                heapifyDown(arr, size, i);
            }
        }

    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int size) {
            buildMaxHeap(arr, size);

            for (int i = size - 1; i > 0; i--) {
                std::swap(arr[0], arr[i]);
                heapifyDown(arr, i, 0);
            }
        }
    };

    class HybridSort {
        template<typename T>
        static void insertionSort(std::vector<T> &arr, int left_index, int right_index) {
            for (int i = left_index + 1; i <= right_index; i++) {
                int j = i;
                while (j > left_index && arr[j - 1] > arr[j]) {
                    std::swap(arr[j], arr[j - 1]);
                    j--;
                }
            }
        }

    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int threshold, int left, int right) {
            if (left >= right) return;

            if (right - left + 1 <= threshold) {
                insertionSort(arr, left, right);
                return;
            }

            int pivotIndex = left + (right - left) / 2;
            T pivotValue = arr[pivotIndex];

            std::swap(arr[pivotIndex], arr[right]);

            int i = left;

            for (int j = left; j < right; j++) {
                if (arr[j] < pivotValue) {
                    std::swap(arr[i], arr[j]);
                    i++;
                }
            }

            std::swap(arr[i], arr[right]);

            sort(arr, threshold, left, i - 1);
            sort(arr, threshold, i + 1, right);
        }
    };

    class QuickSort {
    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int left_index, int right_index) {
            if (left_index >= right_index) return;

            int pivot = (left_index + right_index) / 2;
            T pivotValue = arr[pivot];

            std::swap(arr[pivot], arr[right_index]);

            int i = left_index;

            for (int j = left_index; j < right_index; j++) {
                if (arr[j] <= pivotValue) {
                    std::swap(arr[i], arr[j]);
                    i++;
                }
            }

            std::swap(arr[i], arr[right_index]);

            sort(arr, left_index, i - 1);
            sort(arr, i + 1, right_index);
        }
    };

    class ShellSort {
    public:
        template<typename T>
        static void sortShell(std::vector<T> &arr, int size) {
            int gap = size / 2;

            for (; gap > 0; gap = gap / 2) {
                for (int j = gap; j < size; j++) {
                    for (int i = j - gap; i >= 0; i -= gap) if (arr[i] > arr[i + gap]) std::swap(arr[i], arr[i + gap]);
                }
            }
        }

        template<typename T>
        static void sortKnuth(std::vector<T> &arr, int size) {
            int gap = 1;
            while (gap < size / 3) gap = 3 * gap + 1;

            for (; gap > 0; gap = gap / 3) {
                for (int j = gap; j < size; j++) {
                    for (int i = j - gap; i >= 0; i -= gap) if (arr[i] > arr[i + gap]) std::swap(arr[i], arr[i + gap]);
                }
            }
        }
    };
};

#endif //UNTITLED_SORTING_ALGORITHMS_H
