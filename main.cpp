#include <iostream>
#include "Utils.h"
#include "SortingAlgorithms.h"

using namespace std;

int main() {
    int size = 10, min = 0, max = 20;
    vector<float> arr = utils::ArrayGenerator::generateCustomIntArray<float>(size, min, max, utils::DESC, 1.f);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;

    SortingAlgorithms::QuickSort::sort(arr, 9, 0);

    for (int i = 0; i < size; i++) {
        cout << arr[i] << ", ";
    }
    cout << endl;
}
