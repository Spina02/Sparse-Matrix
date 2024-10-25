#include "SparseMatrix.hpp"
#include <iostream>

// contructor
SparseMatrix::SparseMatrix(unsigned int nrow, unsigned int ncol) : nrow(nrow), ncol(ncol) {
    values = std::vector<double>();
}

// copy constructor
SparseMatrix::SparseMatrix(const SparseMatrix& other) 
    : nrow(other.nrow), ncol(other.ncol), nnz(other.nnz), values(other.values) {
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

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& other) {
    nrow = other.nrow;
    ncol = other.ncol;
    nnz = other.nnz;
    values = other.values;
    return *this;
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