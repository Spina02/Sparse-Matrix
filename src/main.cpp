#include <iostream>
#include <vector>
#include "SparseMatrix.hpp"
#include "COO_SparseMatrix.hpp"
#include "CSR_SparseMatrix.hpp"
#include "tests.hpp"

void test() {

    std::cout << "Running tests" << std::endl << std::endl;

    if (test_equal()) 
        std::cout << "Equality test passed" << std::endl << std::endl;
    else
        std::cout << "Equality test failed" << std::endl << std::endl;

    if (test_matrix_vector_product())
        std::cout << "Matrix-vector product test passed" << std::endl << std::endl;
    else
        std::cout << "Matrix-vector product test failed" << std::endl << std::endl;


    if (test_conversion())
        std::cout << "Conversion test passed" << std::endl << std::endl;
    else
        std::cout << "Conversion test failed" << std::endl << std::endl;

    if (test_copy())
        std::cout << "Copy test passed" << std::endl << std::endl;
    else
        std::cout << "Copy test failed" << std::endl << std::endl;
}

int main() {
    test();
}