#include "SparseMatrix.hpp"
#include <iostream>

// contructor
SparseMatrix::SparseMatrix(unsigned int nrow, unsigned int ncol) : nrow(nrow), ncol(ncol) {
    values = std::vector<double>();
}

// destructor
SparseMatrix::~SparseMatrix() {
    values.clear();
}

unsigned int SparseMatrix::get_rows() const {
    return nrow;
}

unsigned int SparseMatrix::get_cols() const {
    return ncol;
}

unsigned int SparseMatrix::get_nnz() const {
    return nnz;
}

void SparseMatrix::print() const {
    unsigned int i = 0, j = 0;
    for (i = 0; i < nrow; ++i) {
        for (j = 0; j < ncol; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}