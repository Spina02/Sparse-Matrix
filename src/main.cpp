#include <iostream>
#include <vector>
#include "SparseMatrix.hpp"
#include "COO_SparseMatrix.hpp"
#include "CSR_SparseMatrix.hpp"
#include "tests.hpp"

void perform_tests() {
    bool res;

    std::cout << "Running tests" << std::endl << std::endl;

    res = test_equal();
    std::cout << "Equality test " << (res ? "passed" : "failed") << std::endl << std::endl;

    res = test_matrix_vector_product();
    std::cout << "Matrix-vector product test " << (res ? "passed" : "failed") << std::endl << std::endl;

    res = test_copy_convertion();
    std::cout << "Copy and convertion test " << (res ? "passed" : "failed") << std::endl << std::endl;
}

int main() {
    perform_tests();
}