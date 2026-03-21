//
// Created by pierog on 3/21/26.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H
#include <vector>

using namespace std;

class utils {
public:
    enum order { ASC, DESC };

    class ArrayGenerator {
    public:
        static vector<int> generateIntArray(int size, int minValue, int maxValue);

        static vector<int> generateCustomIntArray(int size, int minValue, int maxValue, order firstOrder,
                                                  float changeSorting);

        static vector<float> generateFloatArray(int size, float minValue, float maxValue);

        static vector<float> generateCustomFloatArray(int size, float minValue, float maxValue, order firstOrder,
                                                      float changeSorting);
    };

    class SequenceChecker {
    public:
        static bool checkSequence(vector<int> array, int size, order order);

        static bool checkSequence(vector<float> array, int size, order order);
    };
};


#endif //UNTITLED_UTILS_H
