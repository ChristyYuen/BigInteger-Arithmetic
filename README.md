# BigInteger ADT: Arbitrary-Precision Arithmetic in C

## Project Overview

This project implements a **BigInteger Abstract Data Type (ADT)** in C, capable of performing arithmetic operations on arbitrarily large signed integers. The ADT supports addition, subtraction, and multiplication using a list of base-b digits where `b` is a power of 10 (`1 ≤ p ≤ 9`).

The underlying data structure for BigInteger is a **List of longs**, and this List ADT has been extended from a prior implementation to support large integers. This project demonstrates how fundamental arithmetic can be performed on large numbers in a manner similar to how it's done with smaller integers in C, using **long integers** and **efficient base-b arithmetic**.

## Features

### BigInteger ADT Operations

- **Addition:** Compute the sum of two BigIntegers.
- **Subtraction:** Compute the difference between two BigIntegers.
- **Multiplication:** Compute the product of two BigIntegers.
- **Sign Management:** Handle positive, negative, and zero states.
- **Base-b Representation:** Uses base-10 digits with configurable base sizes, up to `BASE = 1,000,000,000`.
- **Normalization:** Ensures all base-b digits are normalized in the range `0 ≤ x < b`.

### List ADT Enhancements

- **Long Integer Support:** The List ADT now supports `long` elements instead of `int`, enabling it to store and operate on large digits.
- **Efficient Copying:** The `copyList()` function has been optimized to provide a shallow copy of lists, as deep copying is unnecessary for this use case.
- **Element Overwrite:** A new `set()` function allows in-place modification of elements at the current cursor, streamlining the arithmetic operations.

### Client Program: `Arithmetic.c`

The client program **`Arithmetic.c`** performs the following operations using BigInteger:

1. Read two large integers from an input file.
2. Compute the following:
   - \( A + B \)
   - \( A - B \)
   - \( A - A \)
   - \( 3A - 2B \)
   - \( AB \)
   - \( A^2 \)
   - \( B^2 \)
   - \( 9A^4 + 16B^5 \)
3. Write the results to an output file.

## Project Files

- **`Arithmetic.c`**: Top-level client for performing arithmetic on large integers.
- **`BigInteger.c`**: Implementation of the BigInteger ADT.
- **`BigInteger.h`**: Header file for the BigInteger ADT.
- **`BigIntegerTest.c`**: Test suite for the BigInteger ADT.
- **`List.c`**: Implementation of the List ADT, supporting long integers.
- **`List.h`**: Header file for the List ADT.
- **`ListTest.c`**: Test suite for the List ADT.
- **`Makefile`**: Build configuration for compiling the project.


### Base Arithmetic

All arithmetic operations are performed using base-b digits, with efficient carry/borrow management for addition and subtraction, and proper handling of overflow during multiplication. Normalization ensures that all digits are within the base range.

## Build and Run Instructions

1. **Compile the project**:
   ```bash
   make

2. **Run the arithmetic client**:
   ````
   bash
   ./Arithmetic input.txt output.txt

- input.txt: Contains two large integers as described in the input format section.
- output.txt: Will contain the results of the arithmetic operations.

3. **Test the List and BigInteger ADTs**:
   ```
   bash
   ./ListTest
   ./BigIntegerTest


## Design Considerations
- **Efficiency**: Operations like normalization, carry management, and base conversions are implemented to ensure the code runs efficiently even for very large numbers.
- **Modularity**: The project is divided into clear modules (List, BigInteger, Arithmetic) to maintain separation of concerns and ensure easy testing.
- **Robustness**: The BigInteger ADT is designed to handle edge cases, such as zero, negative numbers, and large carry/borrow values during arithmetic.

## Project Goals
This project demonstrates the ability to:
- Work with large numbers using low-level data structures.
- Implement basic arithmetic operations using efficient algorithms.
- Develop a modular solution by separating concerns into ADTs.
- Test and debug complex software components with thorough unit testing.

## Conclusion
- This project demonstrates the power of modular design and efficient algorithms for handling arbitrarily large numbers in C. It showcases how low-level data structures like lists can be adapted to handle large-scale arithmetic, making it a robust solution for use cases involving large integers.

## License
- This project is released under the MIT License.
