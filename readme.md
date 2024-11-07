# SparseMatrix Project

This project implements sparse matrices using two storage formats:

- **COO (Coordinate Format)**: Stores non-zero elements along with their coordinates (row, column).
- **CSR (Compressed Sparse Row)**: Stores non-zero elements per row, allowing more efficient access during operations like matrix-vector multiplication.

## Main Features

- **Constructors and Conversions**: Ability to create sparse matrices in both formats and convert between them.
- **Mathematical Operations**: Implementation of operations such as matrix-vector multiplication.
- **Operators**: Overloading of operators to facilitate access and manipulation of elements.
- **Tests**: A suite of tests to verify the correct functioning of the implemented features.

## How to Compile and Run

To compile and run the project, you can use the following commands:

- **Build the project**:

  ```bash
  make build
  ```

  or simply:

  ```bash
  make
  ```

- **Clean the build files**:

  ```bash
  make clean
  ```

- **Build and run the project**:

  ```bash
  make run
  ```

  This command will compile the project and start executing the tests included in the project.

## Project Structure

- **include/**: Contains header (`.hpp`) files with class declarations and template implementations.
- **src/**: Contains the `main.cpp` file that runs the tests.
- **obj/**: Directory where object files are stored during compilation.
- **Makefile**: Script to automate the compilation and execution of the project.

## Requirements

- **C++ Compiler**: Ensure you have a compiler that supports C++17 or later.
- **GNU Make**: To use make commands.