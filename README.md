
# CPP09

C++ Module 09 focuses on STL containers and algorithms (C++98).  
This repository contains:

- `ex00/` — **Bitcoin Exchange** (`btc`)
- `ex01/` — **Reverse Polish Notation** (`RPN`)
- `ex02/` — **PmergeMe** (`PmergeMe`)

All projects are compiled with:
- `-Wall -Wextra -Werror`
- must also compile with `-std=c++98` 

---

## Project Structure

```text
cpp09/
├── ex00/                          # Bitcoin Exchange
│   ├── BitcoinExchange.cpp
│   ├── BitcoinExchange.hpp
│   ├── main.cpp
│   ├── Makefile
│   ├── data.csv                   # exchange rate database
│   └── test.txt                   # sample input (optional)
│
├── ex01/                          # Reverse Polish Notation (RPN)
│   ├── RPN.cpp
│   ├── RPN.hpp
│   ├── main.cpp
│   ├── Makefile
│   └── tests.sh                   # helper script for running test cases
│
└── ex02/                          # PmergeMe (Ford–Johnson / merge-insert sort)
    ├── PmergeMe.cpp
    ├── PmergeMe.hpp
    ├── PmergeMe.tpp               # template implementation (if applicable)
    ├── main.cpp
    └── Makefile

```
---

# ex00 — Bitcoin Exchange

## Goal
Compute: `value * bitcoin_rate(date)` using a CSV database (`data.csv`) and an input file containing lines in the format:

```

date | value

````

Rules (from the subject): :contentReference[oaicite:2]{index=2}
- Program name: `btc`
- Takes **a file** as argument.
- Valid date format: `YYYY-MM-DD`
- Valid value: float or positive integer in `[0, 1000]`
- If the date does not exist in the DB, use the **closest lower date** in the DB.

## Build
```bash
cd ex00
make
````

## Run

```bash
./btc input.txt
```

## Expected behavior

* If no file / cannot open file:

  * `Error: could not open file.` 
* For invalid input lines:

  * `Error: bad input => <line>`
* For negative values:

  * `Error: not a positive number.`
* For values > 1000:

  * `Error: too large a number.` 

---

# ex01 — RPN

## Goal

Evaluate a **Reverse Polish Notation** expression passed as a single argument.

Rules (from the subject): 

* Program name: `RPN`
* Takes an RPN expression as argument (no brackets, no decimals required).
* Allowed operators: `+ - * /`
* Numbers used in input are always `< 10` (single-digit), though intermediate/result may exceed.
* On error, print `Error` to standard error.

## Build

```bash
cd ex01
make
```

## Run

```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

## Example (subject)

Outputs `42` for valid expressions; prints `Error` for invalid ones. 

---

# ex02 — PmergeMe

## Goal

Sort a positive integer sequence using **merge-insert sort** (Ford–Johnson algorithm) and compare timing using **two containers**.

Rules (from the subject): 

* Program name: `PmergeMe`
* Input: sequence of **positive integers** as arguments
* Must use **Ford–Johnson** (merge-insertion) algorithm
* Use **at least two different containers**
* Must handle **at least 3000 integers**
* On error: print `Error` to standard error
* Output must include:

  1. unsorted sequence (“Before:”)
  2. sorted sequence (“After:”)
  3. time for container #1
  4. time for container #2
     (format is free, but must show precision clearly) 

## Build

```bash
cd ex02
make
```

## Run (small)

```bash
./PmergeMe 3 5 9 7 4
```

## Run (3000 numbers, Linux)

```bash
./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ")
```

## Run (3000 numbers, macOS)

```bash
./PmergeMe $(jot -r 3000 1 100000 | tr '\n' ' ')
```

## Example output style (subject)

```
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::[...] : ...
Time to process a range of 5 elements with std::[...] : ...
```

---

## AI usage
AI tools were used in a limited way to:
- help **review edge cases** and **validate input/error handling** requirements,
- suggest **test cases** and **output formatting** consistent with the subject,
- support **debugging/clarification** of STL and iterator-related pitfalls.

---