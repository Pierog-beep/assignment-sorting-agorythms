#include <iostream>
#include <chrono>
#include "Utils.h"
#include "SortingAlgorithms.h"

using namespace std;

void displayTime(long long duration) {
    cout << duration << " ms" << endl;
}

template<typename T>
long long handleSort(const string &type, vector<T> &arr, int size) {
    int left = 0, right = size - 1;
    chrono::time_point<chrono::system_clock, chrono::system_clock::duration> start;

    if (type == "shell_s") {
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::ShellSort::sortShell(arr, size);
        return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start).count();
    }
    if (type == "shell_k") {
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::ShellSort::sortKnuth(arr, size);
        return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start).count();
    }
    if (type == "quick") {
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::QuickSort::sort(arr, left, right);
        return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start).count();
    }
    if (type == "heap") {
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::HeapSort::sort(arr, size);
        return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start).count();
    }
    return -1;
}

template<typename T>
long long handleSort(vector<T> &arr, int size, int threshold) {
    int left = 0, right = size - 1;
    auto start = chrono::high_resolution_clock::now();
    SortingAlgorithms::HybridSort::sort(arr, threshold, left, right);
    return chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start).count();
}

void fullTest(const string &type, const int size, const int repetitions, const int threshold) {
    int minIV = 0, maxIV = 100;
    float minFV = 0, maxFV = 100;

    vector<int> randomIArr, ascIArr, descIArr, mixedIArr;
    vector<float> randomFArr, ascFArr, descFArr, mixedFArr;

    long long randomITime = 0, ascITime = 0, descITime = 0, mixedITime = 0, randomFTime = 0, ascFTime = 0, descFTime = 0
            , mixedFTime = 0;

    printf("Results [ms] (Random, Mixed, Descending, Ascending):\n");

    for (int i = 0; i < repetitions; i++) {
        // Int arr generation
        mixedIArr = utils::ArrayGenerator::generateCustomArray<int>(size, minIV, maxIV, utils::ASC, 0.66f);
        descIArr = utils::ArrayGenerator::generateCustomArray<int>(size, minIV, maxIV, utils::DESC, 1.f);
        ascIArr = utils::ArrayGenerator::generateCustomArray<int>(size, minIV, maxIV, utils::ASC, 1.f);
        randomIArr = utils::ArrayGenerator::generateArray<int>(size, minIV, maxIV);

        // Float arr generation
        mixedFArr = utils::ArrayGenerator::generateCustomArray<float>(size, minFV, maxFV, utils::ASC, 0.66f);
        descFArr = utils::ArrayGenerator::generateCustomArray<float>(size, minFV, maxFV, utils::DESC, 1.f);
        ascFArr = utils::ArrayGenerator::generateCustomArray<float>(size, minFV, maxFV, utils::ASC, 1.f);
        randomFArr = utils::ArrayGenerator::generateArray<float>(size, minFV, maxFV);

        // Gathering int arr data
        if (type == "hybrid") {
            randomITime += handleSort<int>(randomIArr, size, threshold);
            mixedITime += handleSort<int>(mixedIArr, size, threshold);
            descITime += handleSort<int>(descIArr, size, threshold);
            ascITime += handleSort<int>(ascIArr, size, threshold);
        } else {
            randomITime += handleSort<int>(type, randomIArr, size);
            mixedITime += handleSort<int>(type, mixedIArr, size);
            descITime += handleSort<int>(type, descIArr, size);
            ascITime += handleSort<int>(type, ascIArr, size);
        }

        if (!utils::SequenceChecker::checkSequence(randomIArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(mixedIArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(descIArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(ascIArr, size, utils::ASC)) {
            printf("Error in sorting!\nArray not sorted!");
            return;
        }

        // Gathering float arr data
        if (type == "hybrid") {
            randomFTime += handleSort<float>(randomFArr, size, threshold);
            mixedFTime += handleSort<float>(mixedFArr, size, threshold);
            descFTime += handleSort<float>(descFArr, size, threshold);
            ascFTime += handleSort<float>(ascFArr, size, threshold);
        } else {
            randomFTime += handleSort<float>(type, randomFArr, size);
            mixedFTime += handleSort<float>(type, mixedFArr, size);
            descFTime += handleSort<float>(type, descFArr, size);
            ascFTime += handleSort<float>(type, ascFArr, size);
        }

        if (!utils::SequenceChecker::checkSequence(randomFArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(mixedFArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(descFArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(ascFArr, size, utils::ASC)) {
            printf("Error in sorting!\nArray not sorted!");
            return;
        }
    }

    // Calculating and showing the results
    double transform = repetitions * 1000000;

    printf("Int;%.4f;%.4f;%.4f;%.4f;\n",
           (double) randomITime / transform, (double) mixedITime / transform, (double) descITime / transform,
           (double) ascITime / transform);

    printf("Float;%.4f;%.4f;%.4f;%.4f;\n",
           (double) randomFTime / transform, (double) mixedFTime / transform, (double) descFTime / transform,
           (double) ascFTime / transform);
}

template<typename T>
void handleGeneration(const std::string &minValueString, const std::string &maxValueString,
                      const std::string &sizeString, std::vector<T> &arr, int &size) {
    T min, max;

    stringstream min_stream(minValueString);
    min_stream >> min;

    stringstream max_stream(maxValueString);
    max_stream >> max;

    arr = utils::ArrayGenerator::generateArray<T>(stoi(sizeString), min, max);
    size = stoi(sizeString);
}

template<typename T>
void handleGeneration(const string &minValueString, const string &maxValueString,
                      const string &sizeString, vector<T> &arr, string &thresholdString, string &firstOrder,
                      int &size) {
    T min, max;

    stringstream min_stream(minValueString);
    min_stream >> min;

    stringstream max_stream(maxValueString);
    max_stream >> max;

    if (firstOrder == "ASC") {
        arr = utils::ArrayGenerator::generateCustomArray<T>(stoi(sizeString), min, max, utils::ASC,
                                                            stof(thresholdString));
        size = stoi(sizeString);
    }

    if (firstOrder == "DESC") {
        arr = utils::ArrayGenerator::generateCustomArray<T>(stoi(sizeString), min, max, utils::DESC,
                                                            stof(thresholdString));
        size = stoi(sizeString);
    }
}

int main() {
    int intArrSize = 0, floatArrSize = 0;
    vector<int> intArr;
    vector<float> floatArr;
    vector<string> userResponse;

    bool running = true;
    while (running) {
        string token, line;
        userResponse.clear();

        if (getline(cin, line)) {
            stringstream ss(line);
            while (getline(ss, token, ' ')) userResponse.push_back(token);
        }

        if (userResponse[0] == "load") {
            // Loading arrays from a file
            if (userResponse[1] == "int") {
                utils::ArrayGenerator::readArrayFromFile<int>(userResponse[2], intArr, intArrSize);
                continue;
            }

            if (userResponse[1] == "float") {
                utils::ArrayGenerator::readArrayFromFile<float>(userResponse[2], floatArr, floatArrSize);
                continue;
            }
        } else if (userResponse[0] == "sort") {
            // Sorting arrays
            if (userResponse[1] == "hybrid") {
                if (userResponse[2] == "int") {
                    displayTime(handleSort(intArr, intArrSize, stoi(userResponse[3])));
                    continue;
                }
                if (userResponse[2] == "float") {
                    displayTime(handleSort(floatArr, floatArrSize, stoi(userResponse[3])));
                    continue;
                }
            }
            if (userResponse[2] == "int") {
                displayTime(handleSort(userResponse[1], intArr, intArrSize));
                continue;
            }
            if (userResponse[2] == "float") {
                displayTime(handleSort(userResponse[1], floatArr, floatArrSize));
                continue;
            }
        } else if (userResponse[0] == "show") {
            // Showing the loaded arrays
            if (userResponse[1] == "int") {
                utils::ArrayPrint::printArray(intArr, intArrSize);
                cout << endl;
                continue;
            }
            if (userResponse[1] == "float") {
                utils::ArrayPrint::printArray(floatArr, floatArrSize);
                cout << endl;
                continue;
            }
        } else if (userResponse[0] == "generate") {
            // Generating the arrays
            if (userResponse[1] == "custom") {
                if (userResponse[2] == "int") {
                    handleGeneration<int>(userResponse[3], userResponse[4], userResponse[5],
                                          intArr, userResponse[6], userResponse[7], intArrSize);
                    continue;
                }
                if (userResponse[2] == "float") {
                    handleGeneration<float>(userResponse[3], userResponse[4], userResponse[5],
                                            floatArr, userResponse[6], userResponse[7], floatArrSize);
                    continue;
                }
            }
            if (userResponse[1] == "int") {
                handleGeneration<int>(userResponse[2], userResponse[3], userResponse[4],
                                      intArr, intArrSize);
                continue;
            }
            if (userResponse[1] == "float") {
                handleGeneration<float>(userResponse[2], userResponse[3], userResponse[4],
                                        floatArr, floatArrSize);
                continue;
            }
        } else if (userResponse[0] == "test") {
            fullTest(userResponse[1], stoi(userResponse[2]), stoi(userResponse[3]), stoi(userResponse[4]));
            continue;
        } else if (userResponse[0] == "quit") {
            // Quiting the program
            running = false;
            continue;
        }

        std::cout << "Wrong query syntax!" << std::endl;
    }
}
