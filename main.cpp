#include <iostream>
#include <chrono>
#include "Utils.h"
#include "SortingAlgorithms.h"

using namespace std;

void displayTime(auto start, auto end) {
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Sorting time: " << duration.count() << "us" << endl;
}

template<typename T>
void handleSort(const string &type, vector<T> &arr, int size) {
    int left = 0, right = size - 1;
    chrono::time_point<chrono::system_clock, chrono::system_clock::duration> start;

    if (type == "shell_s") {
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::ShellSort::sortShell(arr, arr.size());
        displayTime(start, chrono::high_resolution_clock::now());
    } else if (type == "shell_k") {
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::ShellSort::sortKnuth(arr, arr.size());
        displayTime(start, chrono::high_resolution_clock::now());
    } else if (type == "quick") {
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::QuickSort::sort(arr, left, right);
        displayTime(start, chrono::high_resolution_clock::now());
    } else if (type == "heap") {
        start = chrono::high_resolution_clock::now();
        SortingAlgorithms::HeapSort::sort(arr, arr.size());
        displayTime(start, chrono::high_resolution_clock::now());
    }
}

template<typename T>
void handleSort(const string &type, vector<T> &arr, int size, const string &thresholdString) {
    int left = 0, right = size - 1;

    if (type == "hybrid") {
        auto start = chrono::high_resolution_clock::now();
        SortingAlgorithms::HybridSort::sort(arr, stoi(thresholdString), left, right);
        displayTime(start, chrono::high_resolution_clock::now());
    }
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
                    handleSort(userResponse[1], intArr, intArrSize, userResponse[3]);
                    continue;
                }
                if (userResponse[2] == "float") {
                    handleSort(userResponse[1], floatArr, floatArrSize, userResponse[3]);
                    continue;
                }
            }
            if (userResponse[2] == "int") {
                handleSort(userResponse[1], intArr, intArrSize);
                continue;
            }
            if (userResponse[2] == "float") {
                handleSort(userResponse[1], floatArr, floatArrSize);
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
                    handleGeneration<int>(userResponse[3], userResponse[4], userResponse[5], intArr, userResponse[6],
                                          userResponse[7], intArrSize);
                    continue;
                }
                if (userResponse[2] == "float") {
                    handleGeneration<float>(userResponse[3], userResponse[4], userResponse[5], floatArr,
                                            userResponse[6],
                                            userResponse[7], floatArrSize);
                    continue;
                }
            }
            if (userResponse[1] == "int") {
                handleGeneration<int>(userResponse[2], userResponse[3], userResponse[4], intArr, intArrSize);
                continue;
            }
            if (userResponse[1] == "float") {
                handleGeneration<float>(userResponse[2], userResponse[3], userResponse[4], floatArr, floatArrSize);
                continue;
            }
        } else if (userResponse[0] == "quit") {
            // Quiting the program
            running = false;
            continue;
        }

        std::cout << "Wrong query syntax!" << std::endl;
    }
}
