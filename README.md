# Sorting Algorithms Benchmark

## Overview

This project is a C++ application designed to implement and test various sorting algorithms.

The program allows users to generate or load arrays of integers and floating-point numbers, sort them using different algorithms, and measure execution time. It also provides a benchmarking mode that compares sorting performance across different input distributions.

## Features

- Sorting integer (`int`) and floating-point (`float`) arrays.
- Generating random arrays within a specified value range.
- Generating custom arrays with ascending or descending initial order.
- Loading arrays from external files.
- Displaying generated or loaded arrays.
- Measuring sorting execution time in nanoseconds.
- Benchmarking sorting algorithms using multiple input distributions.
- Verifying sorting correctness after each operation.

## Implemented Algorithms

The application provides the following sorting algorithms:

| Algorithm | Command | Description |
|---|---|---|
| Shell Sort | `shell_s` | Shell Sort using a standard gap sequence. |
| Shell Sort (Knuth) | `shell_k` | Shell Sort using the Knuth gap sequence. |
| Quick Sort | `quick` | Recursive sorting algorithm based on partitioning the array around a pivot. |
| Heap Sort | `heap` | Comparison-based sorting algorithm using a binary heap. |

## Input Data Generation

The application supports two types of array generation:

### Standard Generation

Generates an array containing random values within the specified minimum and maximum range.

Syntax:

```bash
generate <type> <min> <max> <size>
```

Examples:

```bash
generate int 0 100 1000
generate float 0 100 1000
```

### Custom Generation

Generates arrays with a specified initial ordering.

Syntax:

```bash
generate custom <type> <min> <max> <size> <threshold> <order>
```

Parameters:

- `type` – Data type (`int` or `float`).
- `min` – Minimum generated value.
- `max` – Maximum generated value.
- `size` – Number of elements.
- `threshold` – Fraction of the array that should follow the specified ordering.
- `order` – Initial ordering (`ASC` or `DESC`).

Examples:

```bash
generate custom int 0 100 1000 0.66 ASC
generate custom float 0 100 1000 0.5 DESC
```

## Loading Arrays from Files

Arrays can also be loaded from external files.

Syntax:

```bash
load <type> <filename>
```

Examples:

```bash
load int input.txt
load float input.txt
```

The file format must be compatible with the implementation of `readArrayFromFile()` in `Utils.h`.

## Displaying Arrays

To display the currently loaded or generated array, use:

```bash
show <type>
```

Examples:

```bash
show int
show float
```

## Sorting

To sort an array using one of the implemented algorithms, use:

```bash
sort <algorithm> <type>
```

Examples:

```bash
sort quick int
sort heap float
sort shell_s int
sort shell_k float
```

After sorting, the program displays the execution time in nanoseconds.

## Benchmarking

The application includes a benchmarking mode that allows users to compare algorithm performance across different input distributions and data types.

Syntax:

```bash
test <algorithm> <size> <repetitions> 
```

Parameters:

- `algorithm` – Sorting algorithm to test (`shell_s`, `shell_k`, `quick`, `heap`, or `hybrid`).
- `size` – Number of elements in each test array.
- `repetitions` – Number of benchmark repetitions.


Example:

```bash
test quick 10000 10 
test hybrid 10000 10 
```

### Benchmark Scenarios

Each benchmark iteration generates eight arrays:

| Distribution | Description |
|---|---|
| Random | Randomly distributed values. |
| Mixed | Approximately 66% of the array follows ascending order. |
| Descending | Entire array is sorted in descending order. |
| Ascending | Entire array is already sorted in ascending order. |

Each distribution is tested with both integer and floating-point values.

The program measures the execution time of each sorting operation and calculates the average execution time over all repetitions.
Results are displayed in milliseconds and nanoseconds.
The program also verifies that every resulting array is sorted in ascending order. If an algorithm produces an incorrectly sorted array, the benchmark stops and reports an error.

## Command Reference

| Command | Description |
|---|---|
| `generate` | Generates a new array. |
| `generate custom` | Generates an array with a specified initial ordering. |
| `load` | Loads an array from a file. |
| `show` | Displays the current array. |
| `sort` | Sorts an array using a selected algorithm. |
| `test` | Runs a performance benchmark. |
| `quit` | Terminates the application. |

## Project Structure

The application uses three main components:

- **Main application** – Handles user commands, manages arrays, coordinates sorting operations, and measures execution time.
- **SortingAlgorithms.h** – Contains the implementations of the sorting algorithms.
- **Utils.h** – Provides utility functionality, including array generation, file loading, printing, and sequence validation.

## Notes

- Only one integer array and one floating-point array are maintained at a time.
- Generating or loading a new array replaces the previous array of the same type.
- Sorting operations modify the arrays directly.
- Benchmark results depend on hardware, compiler optimizations, and input size.
