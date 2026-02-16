*This project has been created as part of the 42 curriculum by **mabou-ha**.*

# CPP Module 09

## Description

CPP Module 09 is the final module of the C++ Piscine at 42.
It focuses on advanced use of the C++ Standard Library, algorithmic thinking, and basic performance analysis.

The module contains three exercises:

* **ex00 – Bitcoin Exchange**
  Parse historical Bitcoin data from a CSV file and compute exchange values for given dates.

* **ex01 – Reverse Polish Notation (RPN)**
  Implement a calculator that evaluates expressions written in Reverse Polish Notation using a stack.

* **ex02 – PmergeMe**
  Implement the Ford–Johnson (merge-insert) sorting algorithm and compare its performance using
  `std::vector` and `std::deque`.

The goal of this module is to learn how to:

* Use STL containers efficiently.
* Apply classic algorithms.
* Handle parsing and error cases robustly.
* Measure and compare execution time between containers.

---

## Project Structure

```text
cpp09/
├── ex00/
│   ├── BitcoinExchange.cpp
│   ├── BitcoinExchange.hpp
│   ├── main.cpp
│   ├── Makefile
├── ex01/
│   ├── RPN.cpp
│   ├── RPN.hpp
│   ├── main.cpp
│   ├── Makefile
└── ex02/
    ├── PmergeMe.cpp
    ├── PmergeMe.hpp
    ├── main.cpp
    └── Makefile
```

---

## Instructions

### Compilation

Each exercise has its own Makefile.

Example (from inside an exercise folder):

```bash
make
```

This will generate the executable for that exercise.

### Execution

#### ex00 – Bitcoin Exchange

```bash
./btc input.txt
```

#### ex01 – RPN

```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

#### ex02 – PmergeMe

```bash
./PmergeMe 3 5 9 7 4 2 8
```

---

## Exercises Overview

### ex00 – Bitcoin Exchange

* Reads a CSV file containing Bitcoin prices (`data.csv`).
* Parses an input file containing `date | value`.
* Outputs the converted value using the closest available date (previous valid date).
* Handles invalid formats, invalid dates, negative values, and out-of-range numbers.

### ex01 – Reverse Polish Notation

* Evaluates mathematical expressions written in RPN.
* Uses a stack to process operands and operators.
* Supports operators: `+ - * /`.
* Handles invalid expressions (missing operands, invalid tokens, division by zero).

### ex02 – PmergeMe

* Implements the Ford–Johnson sorting algorithm (merge-insertion sort).
* Sorts the same input using:

  * `std::vector`
  * `std::deque`
* Measures and prints execution time for both containers.
* Validates input (positive integers, duplicates depending on your implementation rules).

---

## Resources

### C++ and STL

* [https://cplusplus.com/reference/](https://cplusplus.com/reference/)

### Algorithms (Ford–Johnson / Merge-Insertion Sort)

* [https://en.wikipedia.org/wiki/Merge-insertion_sort](https://en.wikipedia.org/wiki/Merge-insertion_sort)
* [https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91](https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91)

### Reverse Polish Notation

* [https://en.wikipedia.org/wiki/Reverse_Polish_notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)

---

## AI Usage

AI (ChatGPT) was used in this project for:

* Understanding some of the concepts required for this module, especially when an idea needed a clearer explanation.
* Implementing details and to double-check typical edge cases during parsing and error handling.

