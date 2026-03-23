//
// Created by pierog on 3/23/26.
//

#ifndef UNTITLED_SORTING_ALGORITHMS_H
#define UNTITLED_SORTING_ALGORITHMS_H
#include <vector>

namespace SortingAlgorithms {
    class HeapSort {
    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int size) {
        }
    };

    class HybridSort {
    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int size) {
        }
    };

    // Coś tu nie działa poprawnie (do naprawy później)
    class QuickSort {
    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int right_index, int left_index) {
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

    class InsertionSort {
    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int size) {
            for (int i = 1; i < size; i++) {
                int j = i;
                while (j > 0 && arr[j - 1] > arr[j]) {
                    std::swap(arr[j], arr[j - 1]);
                    j--;
                }
            }
        }
    };

    class ShellSort {
    public:
        template<typename T>
        static void sort(std::vector<T> &arr, int size) {
            int gap, i, j;
            for (gap = size / 2; gap > 0; gap = gap / 2) {
                for (j = gap; j < size; j++) {
                    for (i = j - gap; i >= 0; i -= gap) {
                        if (arr[i] > arr[i + gap]) {
                            std::swap(arr[i], arr[i + gap]);
                        }
                    }
                }
            }
        }
    };
};

#endif //UNTITLED_SORTING_ALGORITHMS_H
