//
// Created by pierog on 3/21/26.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H


class utils {
    enum order { ASC, DESC };

public:
    class ArrayGenerator {
    public:
        int *genretateIntArray(int size, int minValue, int maxValue);

        float *generateFloatArray(int size, float minValue, int maxValue);

        int *genrateSuctomIntArray(int size, int minValue, int maxValue, order firstOrder, float changeSorting);
    };

    class SequenceChecker {
    public:
        bool checkSequence(int *array, order order);
    };
};


#endif //UNTITLED_UTILS_H
