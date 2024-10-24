#include "SparseMatrix.hpp"

// contructor
SparseMatrix::SparseMatrix(unsigned int nrow, unsigned int ncol) : nrow(nrow), ncol(ncol) {
    values = std::vector<double>();
}

// destructor
SparseMatrix::~SparseMatrix() {}

unsigned int SparseMatrix::get_rows() const {
    return nrow;
}

unsigned int SparseMatrix::get_cols() const {
    return ncol;
}

unsigned int SparseMatrix::get_nnz() const {
    return nnz;
}