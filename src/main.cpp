#include <iostream>
#include <vector>
#include "SparseMatrix.hpp"
#include "COO_SparseMatrix.hpp"
#include "CSR_SparseMatrix.hpp"
#include "tests.hpp"
#include <iostream>
#include <typeinfo>

template <typename T>
void perform_tests() {
    bool res;

    std::cout << "Running tests for type " << typeid(T).name() << std::endl << std::endl;

    res = test_equal<T>();
    std::cout << "Equality test " << (res ? "passed" : "failed") << std::endl << std::endl;

    res = test_matrix_vector_product<T>();
    std::cout << "Matrix-vector product test " << (res ? "passed" : "failed") << std::endl << std::endl;

    res = test_copy_conversion<T>();
    std::cout << "Copy and conversion test " << (res ? "passed" : "failed") << std::endl << std::endl;

    res = test_row_sum<T>();
    std::cout << "Row sum test " << (res ? "passed" : "failed") << std::endl << std::endl;

    res = test_canonical_basis<T>();
    std::cout << "Canonical basis test " << (res ? "passed" : "failed") << std::endl << std::endl;

    res = test_empty_matrix<T>();
    std::cout << "Edge cases test " << (res ? "passed" : "failed") << std::endl << std::endl;
}

int main() {
    perform_tests<int>();
    perform_tests<double>();
    return 0;
}