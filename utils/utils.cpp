//
// Created by pierog on 3/21/26.
//

#include "utils.h"

#include <random>
using namespace std;

vector<int> utils::ArrayGenerator::generateIntArray(int size, int minValue, int maxValue) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minValue, maxValue);

    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = dist(gen);
    }

    return arr;
}

vector<int> utils::ArrayGenerator::generateCustomIntArray(int size, int minValue, int maxValue, order firstOrder,
                                                          float changeSorting) {
    vector<int> arr_raw = generateIntArray(size, minValue, maxValue);

    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size - 1; i++) {
            order currentOrder = firstOrder;

            if ((float) i / (float) (size - 1) > changeSorting) {
                currentOrder = (firstOrder == ASC) ? DESC : ASC;
            }

            if (arr_raw[i] > arr_raw[i + 1] && currentOrder == ASC) {
                swap(arr_raw[i], arr_raw[i + 1]);
            }

            if (arr_raw[i] < arr_raw[i + 1] && currentOrder == DESC) {
                swap(arr_raw[i], arr_raw[i + 1]);
            }
        }
    }
    return arr_raw;
}

vector<float> utils::ArrayGenerator::generateFloatArray(int size, float minValue, float maxValue) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(minValue, maxValue);

    vector<float> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = dist(gen);
    }

    return arr;
}


vector<float> utils::ArrayGenerator::generateCustomFloatArray(int size, float minValue, float maxValue,
                                                              order firstOrder,
                                                              float changeSorting) {
    vector<float> arr_raw = generateFloatArray(size, minValue, maxValue);

    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size - 1; i++) {
            order currentOrder = firstOrder;

            if ((float) i / (float) (size - 1) > changeSorting) {
                currentOrder = (firstOrder == ASC) ? DESC : ASC;
            }

            if (arr_raw[i] > arr_raw[i + 1] && currentOrder == ASC) {
                swap(arr_raw[i], arr_raw[i + 1]);
            }

            if (arr_raw[i] < arr_raw[i + 1] && currentOrder == DESC) {
                swap(arr_raw[i], arr_raw[i + 1]);
            }
        }
    }
    return arr_raw;
}

bool utils::SequenceChecker::checkSequence(vector<int> array, int size, order order) {
    for (int i = 0; i + 1 < size; i++) {
        if (array[i] > array[i + 1] && order == ASC) {
            return false;
        }

        if (array[i] < array[i + 1] && order == DESC) {
            return false;
        }
    }
    return true;
}

bool utils::SequenceChecker::checkSequence(vector<float> array, int size, order order) {
    for (int i = 0; i + 1 < size; i++) {
        if (array[i] > array[i + 1] && order == ASC) {
            return false;
        }

        if (array[i] < array[i + 1] && order == DESC) {
            return false;
        }
    }
    return true;
}
