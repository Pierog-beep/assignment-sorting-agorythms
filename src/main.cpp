
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
#include "Utils.h"
#include "SortingAlgorithms.h"

using namespace std;

void displayWelcome() {
    cout << "========================================\n";
    cout << "       SORTING ALGORITHMS TOOL\n";
    cout << "========================================\n";
    cout << "Available commands:\n";

    cout << "  generate <type> <min> <max> <size>\n";
    cout << "  generate custom <type> <min> <max> <size> <threshold> <order>\n";
    cout << "  load <type> <filename>\n";
    cout << "  show <type>\n";
    cout << "  sort <algorithm> <type>\n";
    cout << "  test <algorithm> <size> <repetitions>\n";
    cout << "  quit\n";

    cout << "Available types: int, float\n";
    cout << "Available algorithms: shell_s, shell_k, quick, heap\n";
    cout << "========================================\n";
}

void displayTime(long long duration) {
    cout << "========================================\n";
    cout << "          SORTING COMPLETED\n";
    cout << "========================================\n";
    cout << "Execution time: " << duration << " ns\n";
    cout << fixed << setprecision(4);
    cout << "Execution time: " << duration / 1000000.0 << " ms\n";
    cout << "========================================\n";
}

template<typename T>
long long handleSort(const string &type, vector<T> &arr, int size) {
    int left = 0, right = size - 1;

    if (type == "shell_s") {
        auto start = chrono::high_resolution_clock::now();
        SortingAlgorithms::ShellSort::sortShell(arr, size);
        return chrono::duration_cast<chrono::nanoseconds>(
            chrono::high_resolution_clock::now() - start
        ).count();
    }

    if (type == "shell_k") {
        auto start = chrono::high_resolution_clock::now();
        SortingAlgorithms::ShellSort::sortKnuth(arr, size);
        return chrono::duration_cast<chrono::nanoseconds>(
            chrono::high_resolution_clock::now() - start
        ).count();
    }

    if (type == "quick") {
        auto start = chrono::high_resolution_clock::now();
        SortingAlgorithms::QuickSort::sort(arr, left, right);
        return chrono::duration_cast<chrono::nanoseconds>(
            chrono::high_resolution_clock::now() - start
        ).count();
    }

    if (type == "heap") {
        auto start = chrono::high_resolution_clock::now();
        SortingAlgorithms::HeapSort::sort(arr, size);
        return chrono::duration_cast<chrono::nanoseconds>(
            chrono::high_resolution_clock::now() - start
        ).count();
    }

    return -1;
}

void fullTest(const string &type, const int size, const int repetitions) {
    int minIV = 0, maxIV = 100;
    float minFV = 0, maxFV = 100;

    vector<int> randomIArr, ascIArr, descIArr, mixedIArr;
    vector<float> randomFArr, ascFArr, descFArr, mixedFArr;

    long long randomITime = 0, ascITime = 0, descITime = 0, mixedITime = 0;
    long long randomFTime = 0, ascFTime = 0, descFTime = 0, mixedFTime = 0;

    if (repetitions <= 0 || size < 0) {
        cout << "Invalid benchmark parameters.\n";
        return;
    }

    for (int i = 0; i < repetitions; i++) {
        mixedIArr = utils::ArrayGenerator::generateCustomArray<int>(
            size, minIV, maxIV, utils::ASC, 0.66f
        );
        descIArr = utils::ArrayGenerator::generateCustomArray<int>(
            size, minIV, maxIV, utils::DESC, 1.f
        );
        ascIArr = utils::ArrayGenerator::generateCustomArray<int>(
            size, minIV, maxIV, utils::ASC, 1.f
        );
        randomIArr = utils::ArrayGenerator::generateArray<int>(
            size, minIV, maxIV
        );

        mixedFArr = utils::ArrayGenerator::generateCustomArray<float>(
            size, minFV, maxFV, utils::ASC, 0.66f
        );
        descFArr = utils::ArrayGenerator::generateCustomArray<float>(
            size, minFV, maxFV, utils::DESC, 1.f
        );
        ascFArr = utils::ArrayGenerator::generateCustomArray<float>(
            size, minFV, maxFV, utils::ASC, 1.f
        );
        randomFArr = utils::ArrayGenerator::generateArray<float>(
            size, minFV, maxFV
        );

        randomITime += handleSort<int>(type, randomIArr, size);
        mixedITime += handleSort<int>(type, mixedIArr, size);
        descITime += handleSort<int>(type, descIArr, size);
        ascITime += handleSort<int>(type, ascIArr, size);

        if (!utils::SequenceChecker::checkSequence(randomIArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(mixedIArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(descIArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(ascIArr, size, utils::ASC)) {
            cout << "The sorting algorithm produced an\n";
            cout << "incorrectly sorted array.\n";
            cout << "Benchmark terminated.\n";
            return;
        }

        randomFTime += handleSort<float>(type, randomFArr, size);
        mixedFTime += handleSort<float>(type, mixedFArr, size);
        descFTime += handleSort<float>(type, descFArr, size);
        ascFTime += handleSort<float>(type, ascFArr, size);

        if (!utils::SequenceChecker::checkSequence(randomFArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(mixedFArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(descFArr, size, utils::ASC) ||
            !utils::SequenceChecker::checkSequence(ascFArr, size, utils::ASC)) {
            cout << "Error in sorting!\nArray not sorted!\n";
            return;
        }
    }

    double transform = repetitions * 1000000.0;

    double randomI = randomITime / transform;
    double mixedI = mixedITime / transform;
    double descI = descITime / transform;
    double ascI = ascITime / transform;

    double randomF = randomFTime / transform;
    double mixedF = mixedFTime / transform;
    double descF = descFTime / transform;
    double ascF = ascFTime / transform;

    // Displaying benchmark results
    cout << "===============================================================\n";
    cout << "                    BENCHMARK RESULTS\n";
    cout << "===============================================================\n";

    cout << "Algorithm: " << type << "\n";
    cout << "Array size: " << size << "\n";
    cout << "Repetitions: " << repetitions << "\n";

    cout << "---------------------------------------------------------------\n";

    cout << left
         << setw(12) << "Data type"
         << right
         << setw(12) << "Random"
         << setw(12) << "Mixed"
         << setw(12) << "Descending"
         << setw(12) << "Ascending"
         << "\n";

    cout << "---------------------------------------------------------------\n";

    cout << fixed << setprecision(4);

    cout << left << setw(12) << "Integer"
         << right << setw(12) << randomI
         << setw(12) << mixedI
         << setw(12) << descI
         << setw(12) << ascI << "\n";

    cout << left << setw(12) << "Float"
         << right << setw(12) << randomF
         << setw(12) << mixedF
         << setw(12) << descF
         << setw(12) << ascF << "\n";

    cout << "---------------------------------------------------------------\n";
    cout << "All execution times are expressed in milliseconds (ms).\n";
    cout << "===============================================================\n";

    // Additional results
    printf("Int;%.4f;%.4f;%.4f;%.4f;\n",
           randomI, mixedI, descI, ascI);

    printf("Float;%.4f;%.4f;%.4f;%.4f;\n",
           randomF, mixedF, descF, ascF);
}

template<typename T>
void handleGeneration(
    const string &minValueString,
    const string &maxValueString,
    const string &sizeString,
    vector<T> &arr,
    int &size
) {
    T min, max;

    stringstream min_stream(minValueString);
    min_stream >> min;

    stringstream max_stream(maxValueString);
    max_stream >> max;

    arr = utils::ArrayGenerator::generateArray<T>(
        stoi(sizeString), min, max
    );

    size = stoi(sizeString);
}

template<typename T>
void handleGeneration(
    const string &minValueString,
    const string &maxValueString,
    const string &sizeString,
    vector<T> &arr,
    string &thresholdString,
    string &firstOrder,
    int &size
) {
    T min, max;

    stringstream min_stream(minValueString);
    min_stream >> min;

    stringstream max_stream(maxValueString);
    max_stream >> max;

    if (firstOrder == "ASC") {
        arr = utils::ArrayGenerator::generateCustomArray<T>(
            stoi(sizeString), min, max, utils::ASC,
            stof(thresholdString)
        );
        size = stoi(sizeString);
    }

    if (firstOrder == "DESC") {
        arr = utils::ArrayGenerator::generateCustomArray<T>(
            stoi(sizeString), min, max, utils::DESC,
            stof(thresholdString)
        );
        size = stoi(sizeString);
    }
}

int main() {
    int intArrSize = 0, floatArrSize = 0;

    vector<int> intArr;
    vector<float> floatArr;
    vector<string> userResponse;

    displayWelcome();

    bool running = true;

    while (running) {
        string token, line;
        userResponse.clear();

        if (!getline(cin, line)) {
            break;
        }

        stringstream ss(line);

        while (ss >> token) {
            userResponse.push_back(token);
        }

        if (userResponse.empty()) {
            continue;
        }

        if (userResponse[0] == "load") {
            // Loading arrays from a file
            if (userResponse.size() < 3) {
                cout << "Wrong query syntax!\n";
                continue;
            }

            if (userResponse[1] == "int") {
                utils::ArrayGenerator::readArrayFromFile<int>(
                    userResponse[2], intArr, intArrSize
                );
                cout << "[INFO] Array loaded successfully!\n";
                cout << "Number of elements: " << intArrSize << "\n";
                continue;
            }

            if (userResponse[1] == "float") {
                utils::ArrayGenerator::readArrayFromFile<float>(
                    userResponse[2], floatArr, floatArrSize
                );
                cout << "[INFO] Array loaded successfully!\n";
                cout << "Number of elements: " << floatArrSize << "\n";
                continue;
            }
        }
        else if (userResponse[0] == "sort") {
            // Sorting arrays
            if (userResponse.size() < 3) {
                cout << "Wrong query syntax!\n";
                continue;
            }

            if (userResponse[2] == "int") {
                displayTime(handleSort(userResponse[1], intArr, intArrSize));
                continue;
            }

            if (userResponse[2] == "float") {
                displayTime(handleSort(userResponse[1], floatArr, floatArrSize));
                continue;
            }
        }
        else if (userResponse[0] == "show") {
            // Showing the loaded arrays
            if (userResponse.size() < 2) {
                cout << "Wrong query syntax!\n";
                continue;
            }

            if (userResponse[1] == "int") {
                cout << "========== INTEGER ARRAY ==========\n";
                cout << "Number of elements: " << intArrSize << "\n";
                cout << "-----------------------------------\n";

                utils::ArrayPrint::printArray(intArr, intArrSize);

                cout << "\n===================================\n";
                continue;
            }

            if (userResponse[1] == "float") {
                cout << "========== FLOAT ARRAY ==========\n";
                cout << "Number of elements: " << floatArrSize << "\n";
                cout << "\n-----------------------------------\n";

                utils::ArrayPrint::printArray(floatArr, floatArrSize);

                cout << "\n===================================\n";
                continue;
            }
        }
        else if (userResponse[0] == "generate") {
            // Generating the arrays
            if (userResponse.size() < 2) {
                cout << "Wrong query syntax!\n";
                continue;
            }

            if (userResponse[1] == "custom") {
                if (userResponse.size() < 8) {
                    cout << "Wrong query syntax!\n";
                    continue;
                }

                if (userResponse[2] == "int") {
                    handleGeneration<int>(
                        userResponse[3], userResponse[4], userResponse[5],
                        intArr, userResponse[6], userResponse[7], intArrSize
                    );

                    cout << "[INFO] Array generated successfully!\n";
                    cout << "Number of elements: " << intArrSize << "\n";
                    continue;
                }

                if (userResponse[2] == "float") {
                    handleGeneration<float>(
                        userResponse[3], userResponse[4], userResponse[5],
                        floatArr, userResponse[6], userResponse[7], floatArrSize
                    );

                    cout << "[INFO] Array generated successfully!\n";
                    cout << "Number of elements: " << floatArrSize << "\n";
                    continue;
                }
            }

            if (userResponse.size() < 5) {
                cout << "Wrong query syntax!\n";
                continue;
            }

            if (userResponse[1] == "int") {
                handleGeneration<int>(
                    userResponse[2], userResponse[3], userResponse[4],
                    intArr, intArrSize
                );

                cout << "[INFO] Array generated successfully!\n";
                cout << "Number of elements: " << intArrSize << "\n";
                continue;
            }

            if (userResponse[1] == "float") {
                handleGeneration<float>(
                    userResponse[2], userResponse[3], userResponse[4],
                    floatArr, floatArrSize
                );

                cout << "[INFO] Array generated successfully!\n";
                cout << "Number of elements: " << floatArrSize << "\n";
                continue;
            }
        }
        else if (userResponse[0] == "test") {
            if (userResponse.size() < 4) {
                cout << "Wrong query syntax!\n";
                continue;
            }

            fullTest(
                userResponse[1],
                stoi(userResponse[2]),
                stoi(userResponse[3])
            );
            continue;
        }
        else if (userResponse[0] == "quit") {
            // Quitting the program
            running = false;
            continue;
        }

        cout << "Wrong query syntax!\n";
    }

    return 0;
}
