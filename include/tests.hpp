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

#endif