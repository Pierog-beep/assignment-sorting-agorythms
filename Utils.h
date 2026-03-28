//
// Created by pierog on 3/21/26.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H
#include <fstream>
#include <sstream>
#include <random>
#include <vector>


namespace utils {
    enum order { ASC, DESC };

    class ArrayGenerator {
    public:
        template<typename T>
        static std::vector<T> generateIntArray(int size, int minValue, int maxValue) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::vector<T> arr(size);

            if constexpr (std::is_integral_v<T>) {
                std::uniform_int_distribution<T> dist(minValue, maxValue);

                for (int i = 0; i < size; i++) {
                    arr[i] = dist(gen);
                }

            } else if constexpr (std::is_floating_point_v<T>) {
                std::uniform_real_distribution<T> dist(minValue, maxValue);

                for (int i = 0; i < size; i++) {
                    arr[i] = dist(gen);
                }
            }

            return arr;
        }

        template<typename T>
        static std::vector<T> generateCustomIntArray(int size, int minValue, int maxValue, order firstOrder,
                                                     float changeSorting) {
            std::vector<T> arr = generateIntArray<T>(size, minValue, maxValue);

            for (int j = 0; j < size; j++) {
                for (int i = 0; i < size - 1; i++) {
                    order currentOrder = firstOrder;

                    if ((float) i / (float) (size - 1) > changeSorting) {
                        currentOrder = (firstOrder == ASC) ? DESC : ASC;
                    }

                    if (arr[i] > arr[i + 1] && currentOrder == ASC) {
                        std::swap(arr[i], arr[i + 1]);
                    }

                    if (arr[i] < arr[i + 1] && currentOrder == DESC) {
                        std::swap(arr[i], arr[i + 1]);
                    }
                }
            }
            return arr;
        }
    };

    class SequenceChecker {
    public:
        template<typename T>
        static bool checkSequence(std::vector<T> array, int size, order order) {
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
    };

    class FileReader {
    public:
        template<typename T>
        static std::vector<T> arrayFromFile(std::string filePath) {
            std::ifstream file(filePath);
            std::vector<T> result;
            std::string line;
            T value;

            if (!file.is_open()) {
                std::cout << "Error opening file " << filePath << std::endl;
                return result;
            }

            if (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string token;

                while (std::getline(ss, token, ',')) {
                    std::stringstream convert(token);
                    convert >> value;
                    result.push_back(value);
                }
            }

            file.close();
            return result;
        }
    };
};


#endif //UNTITLED_UTILS_H
