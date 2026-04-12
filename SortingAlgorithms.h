//
// Created by pierog on 3/23/26.
//

#ifndef UNTITLED_SORTING_ALGORITHMS_H
#define UNTITLED_SORTING_ALGORITHMS_H
#include <vector>

namespace SortingAlgorithms {
    class HeapSort {
        template<typename T>
        static void buildMaxHeap(std::vector<T> &arr, int size) {
            int child, parent;
            for (int i = 1; i < size; i++) {
                child = i;

                do {
                    parent = (child - 1) / 2;
                    if (arr[parent] < arr[child]) std::swap(arr[parent], arr[child]);
                    child = parent;
                } while (child != 0);
            }
        }

        template<typename T>
        static void heapify(std::vector<T> &heap, int size) {
            int child, root;
            for (int j = size - 1; j > 0; j--) {
                std::swap(heap[j], heap[0]);
                root = 0;

                while (true) {
                    child = 2 * root + 1;
                    if (child >= j) break;
                    if (child + 1 < j && heap[child] < heap[child + 1]) child++;
                    if (heap[root] < heap[child]) {
                        std::swap(heap[root], heap[child]);
                        root = child;
                    } else break;
                }
            }
        }

    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int size) {
            buildMaxHeap(arr, size);
            heapify(arr, size);
        }
    };

    class HybridSort {
        template<typename T>
        static void insertionSort(std::vector<T> &arr, int left_index, int right_index) {
            for (int i = left_index; i <= right_index; i++) {
                int j = i;
                while (j > left_index && arr[j - 1] > arr[j]) {
                    std::swap(arr[j], arr[j - 1]);
                    j--;
                }
            }
        }

    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int threshold, int left_index, int right_index) {
            if (right_index - left_index + 1 <= threshold) {
                insertionSort(arr, left_index, right_index);
                return;
            }

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

            sort(arr, threshold, left_index, i - 1);
            sort(arr, threshold, i + 1, right_index);
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
