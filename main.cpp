#include <iostream>
#include "Utils.h"
#include "SortingAlgorithms.h"

using namespace std;

int main() {
    vector<int> int_arr;
    vector<float> float_arr;
    vector<string> user_respose;

    bool running = true;
    while (running) {
        string token, line;
        user_respose.clear();

        if (getline(cin, line)) {
            stringstream ss(line);
            while (getline(ss, token, ' ')) user_respose.push_back(token);
        }

        if (user_respose[0] == "load") {
            if (user_respose[1] == "int") {
                int_arr = utils::FileReader::arrayFromFile<int>(user_respose[2]);
            }
            if (user_respose[1] == "string") {
                float_arr = utils::FileReader::arrayFromFile<float>(user_respose[2]);
            }
        } else if (user_respose[0] == "sort") {
            // Hybrid sort
            if (user_respose[1] == "hybrid") {
                if (user_respose[2] == "int") {
                    SortingAlgorithms::HybridSort (int_arr);
                }
                if (user_respose[2] == "string") {
                    SortingAlgorithms::HybridSort (float_arr);
                }
            }

            // Shell sort
            if (user_respose[1] == "shell") {
                if (user_respose[2] == "int") {
                    SortingAlgorithms::ShellSort (int_arr);
                }
                if (user_respose[2] == "string") {
                    SortingAlgorithms::ShellSort (float_arr);
                }
            }

            // Quick sort
            if (user_respose[1] == "quick") {
                if (user_respose[2] == "int") {
                    SortingAlgorithms::QuickSort (int_arr);
                }
                if (user_respose[2] == "string") {
                    SortingAlgorithms::QuickSort (float_arr);
                }
            }

            // Heap sort
            if (user_respose[1] == "heap") {
                if (user_respose[2] == "int") {
                    SortingAlgorithms::HeapSort (int_arr);
                }
                if (user_respose[2] == "string") {
                    SortingAlgorithms::HeapSort (int_arr);
                }
            }
        } else if (user_respose[0] == "q") {
            running = false;
        } else if (user_respose[0] == "show") {
            if (user_respose[1] == "int") {
                // To do
            }
            if (user_respose[1] == "string") {
                // To do
            }
        }
    }
}
