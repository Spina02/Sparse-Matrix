#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <vector>
#include "SparseMatrix.hpp"
#include "COO_SparseMatrix.hpp"
#include "CSR_SparseMatrix.hpp"

// utils
void print_vec(std::vector<double> vec);

// test functions
bool test_equal();
bool test_matrix_vector_product();
bool test_copy_convertion();

// Additional test functions
bool test_row_sum();  // Test with vector of ones
bool test_canonical_basis();  // Test with canonical basis vectors
bool test_empty_matrix();  // Test edge cases

#endif