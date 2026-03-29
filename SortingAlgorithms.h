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
            int c, r;
            for (int i = 1; i < size; i++) {
                c = i;

                do {
                    r = (c - 1) / 2;
                    if (arr[r] < arr[c]) std::swap(arr[r], arr[c]);
                    c = r;
                } while (c != 0);
            }
        }

        template<typename T>
        static void heapify(std::vector<T> &arr, int size) {
            int c, r;
            for (int j = size - 1; j > 0; j--) {
                std::swap(arr[j], arr[0]);
                r = 0;

                do {
                    c = 2 * r + 1;
                    if (arr[c] < arr[c + 1] && c < j - 1) c++;
                    if (arr[r] < arr[c] && c < j) std::swap(arr[r], arr[c]);
                    r = c;
                } while (c < j);
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
        static int partition(std::vector<T> &arr, int left_index, int right_index) {
            T pivot = arr[right_index];
            int i = left_index, j = left_index;

            for (; i < right_index; i++) {
                if (arr[i] < pivot) std::swap(arr[i], arr[j++]);
            }

            std::swap(arr[j], arr[right_index]);
            return j;
        }

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
        static void sort(std::vector<T> &arr, int threshold, int left_index, int right_index) {
            while (left_index < right_index) {
                if (right_index - left_index < threshold) {
                    insertionSort(arr, left_index, right_index);
                    break;
                }

                int pivot = partition(arr, left_index, right_index);

                if (pivot - left_index < right_index - pivot) {
                    sort(arr, threshold, left_index, pivot - 1);
                    left_index = pivot + 1;
                } else {
                    sort(arr, threshold, pivot + 1, right_index);
                    right_index = pivot - 1;
                }
            }
        }
    };

    class QuickSort {
    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int left_index, int right_index) {
            if (left_index >= right_index) { return; }

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
