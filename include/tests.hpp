#ifndef TESTS_HPP
#define TESTS_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "CSR_SparseMatrix.hpp"
#include "COO_SparseMatrix.hpp"

// Function to print a vector
template <typename T>
void print_vec(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << std::endl;
    }
    std::cout << std::endl;
}

// Test for equality operator
template <typename T>
bool test_equal() {
    std::cout << "Testing equality operator" << std::endl;

    std::vector<bool> res(6, false);

    CSR_SparseMatrix<T> csr1(3, 3);
    csr1(0, 1) = static_cast<T>(2);
    csr1(1, 0) = static_cast<T>(2);
    csr1(2, 2) = static_cast<T>(2);

    CSR_SparseMatrix<T> csr2(3, 3);
    csr2(0, 1) = static_cast<T>(2);
    csr2(1, 0) = static_cast<T>(2);
    csr2(2, 2) = static_cast<T>(2);

    CSR_SparseMatrix<T> csr3 = CSR_SparseMatrix<T>::random(3, 3);

    COO_SparseMatrix<T> coo1(3, 3);
    coo1(0, 1) = static_cast<T>(2);
    coo1(1, 0) = static_cast<T>(2);
    coo1(2, 2) = static_cast<T>(2);

    COO_SparseMatrix<T> coo2(3, 3);
    coo2(0, 1) = static_cast<T>(2);
    coo2(1, 0) = static_cast<T>(2);
    coo2(2, 2) = static_cast<T>(2);

    COO_SparseMatrix<T> coo3 = COO_SparseMatrix<T>::random(3, 3);

    res[0] = (csr1 == csr2) == true;
    res[1] = (csr1 == csr3) == false;
    res[2] = (coo1 == coo2) == true;
    res[3] = (coo1 == coo3) == false;
    res[4] = (csr1 == coo1) == true;
    res[5] = (csr1 == coo3) == false;

    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

// Test for matrix-vector product
template <typename T>
bool test_matrix_vector_product() {
    std::cout << "Testing matrix-vector product" << std::endl;

    std::vector<bool> res(4, false);

    CSR_SparseMatrix<T> csr(3, 3);
    csr(0, 1) = static_cast<T>(2);
    csr(1, 0) = static_cast<T>(2);
    csr(2, 2) = static_cast<T>(2);

    COO_SparseMatrix<T> coo(3, 3);
    coo(0, 1) = static_cast<T>(2);
    coo(1, 0) = static_cast<T>(2);
    coo(2, 2) = static_cast<T>(2);

    std::vector<T> vec1 = {static_cast<T>(1), static_cast<T>(2), static_cast<T>(3)};
    std::vector<T> vec2 = {static_cast<T>(-1), static_cast<T>(0), static_cast<T>(1)};

    std::vector<T> res_csr1 = csr * vec1;
    std::vector<T> res_coo1 = coo * vec1;
    std::vector<T> res_csr2 = csr * vec2;
    std::vector<T> res_coo2 = coo * vec2;

    res[0] = (res_coo1 == std::vector<T>({static_cast<T>(4), static_cast<T>(2), static_cast<T>(6)}));
    res[1] = (res_csr1 == std::vector<T>({static_cast<T>(4), static_cast<T>(2), static_cast<T>(6)}));
    res[2] = (res_coo2 == std::vector<T>({static_cast<T>(0), static_cast<T>(-2), static_cast<T>(2)}));
    res[3] = (res_csr2 == std::vector<T>({static_cast<T>(0), static_cast<T>(-2), static_cast<T>(2)}));

    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Test " << i << (res[i] ? " passed" : " failed") << std::endl;
    }

    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

// Test for copy and conversion
template <typename T>
bool test_copy_conversion() {
    std::cout << "Testing copy and conversion" << std::endl;

    std::vector<bool> res(8, false);

    CSR_SparseMatrix<T> csr = CSR_SparseMatrix<T>::random(3, 3);

    CSR_SparseMatrix<T> csr_eq = csr;
    COO_SparseMatrix<T> coo_cp(csr);
    COO_SparseMatrix<T> coo_eq = csr;

    res[0] = (csr == csr_eq);
    res[1] = (csr == coo_cp);
    res[2] = (csr == coo_eq);
    res[3] = (coo_cp == coo_eq);

    COO_SparseMatrix<T> coo = COO_SparseMatrix<T>::random(3, 3);

    COO_SparseMatrix<T> coo_eq2 = coo;
    CSR_SparseMatrix<T> csr_cp(coo);
    CSR_SparseMatrix<T> csr_eq2 = coo;

    res[4] = (coo == coo_eq2);
    res[5] = (coo == csr_cp);
    res[6] = (coo == csr_eq2);
    res[7] = (csr_cp == csr_eq2);

    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Test " << i << (res[i] ? " passed" : " failed") << std::endl;
    }

    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

// Test for row sum using matrix-vector product with vector of ones
template <typename T>
bool test_row_sum() {
    std::cout << "Testing matrix-vector product with vector of ones" << std::endl;
    
    std::vector<bool> res(3, false);
    
    CSR_SparseMatrix<T> csr(3, 3);
    csr(0, 0) = static_cast<T>(1); csr(0, 1) = static_cast<T>(2); csr(0, 2) = static_cast<T>(3);
    csr(1, 0) = static_cast<T>(4); csr(1, 2) = static_cast<T>(5);
    csr(2, 1) = static_cast<T>(6); csr(2, 2) = static_cast<T>(7);
    
    COO_SparseMatrix<T> coo(3, 3);
    coo(0, 0) = static_cast<T>(1); coo(0, 1) = static_cast<T>(2); coo(0, 2) = static_cast<T>(3);
    coo(1, 0) = static_cast<T>(4); coo(1, 2) = static_cast<T>(5);
    coo(2, 1) = static_cast<T>(6); coo(2, 2) = static_cast<T>(7);
    
    std::vector<T> ones(3, static_cast<T>(1.0));
    
    std::vector<T> expected_sums = {static_cast<T>(6), static_cast<T>(9), static_cast<T>(13)};
    
    auto csr_result = csr * ones;
    auto coo_result = coo * ones;
    
    res[0] = (csr_result == expected_sums);
    res[1] = (coo_result == expected_sums);
    res[2] = (csr_result == coo_result);
    
    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Test " << i << (res[i] ? " passed" : " failed") << std::endl;
    }
    
    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

// Test for matrix-vector product with canonical basis vectors
template <typename T>
bool test_canonical_basis() {
    std::cout << "Testing matrix-vector product with canonical basis vectors" << std::endl;
    
    std::vector<bool> res;
    
    CSR_SparseMatrix<T> csr(3, 3);
    csr(0, 0) = static_cast<T>(1); csr(0, 1) = static_cast<T>(2); csr(0, 2) = static_cast<T>(3);
    csr(1, 0) = static_cast<T>(4); csr(1, 2) = static_cast<T>(5);
    csr(2, 1) = static_cast<T>(6); csr(2, 2) = static_cast<T>(7);
    
    for (size_t i = 0; i < 3; ++i) {
        std::vector<T> e_i(3, static_cast<T>(0.0));
        e_i[i] = static_cast<T>(1.0);
        
        auto result = csr * e_i;
        
        for (size_t j = 0; j < 3; ++j) {
            res.push_back(std::abs(result[j] - csr(j, i)) < 1e-10);
        }
    }
    
    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Test " << i << (res[i] ? " passed" : " failed") << std::endl;
    }
    
    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

// Test for edge cases
template <typename T>
bool test_empty_matrix() {
    std::cout << "Testing edge cases (ignore errors)" << std::endl;
    
    std::vector<bool> res;
    
    CSR_SparseMatrix<T> empty_csr(0, 0);
    std::vector<T> empty_vec;
    auto result = empty_csr * empty_vec;
    res.push_back(result.empty());
    
    CSR_SparseMatrix<T> csr(3, 3);
    std::vector<T> wrong_size_vec(4, static_cast<T>(1.0));
    result = csr * wrong_size_vec;
    res.push_back(result.empty());
    
    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Test " << i << (res[i] ? " passed" : " failed") << std::endl;
    }
    
    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

#endif // TESTS_HPP
