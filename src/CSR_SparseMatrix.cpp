#include "CSR_SparseMatrix.hpp"
#include <iostream>

// contructor
CSR_SparseMatrix::CSR_SparseMatrix(unsigned int nrow, unsigned int ncol) : SparseMatrix(nrow, ncol) {
    // initialize empty vectors
    cols = std::vector<unsigned int>();
    // initialize row_idx with nrow+1 elements
    row_idx = std::vector<unsigned int>(nrow + 1, 0);
}

// destructor
CSR_SparseMatrix::~CSR_SparseMatrix() {
    // destroy vectors
    cols.clear();
    row_idx.clear();

    // base class destructor is called automatically here
}

//get and set values with override on () operator
double CSR_SparseMatrix::operator()(unsigned int row, unsigned int col) const {

    if (row >= nrow || col >= ncol) {
        std::cerr << "Error: index out of range" << std::endl;
        return 0;
    }

    for (unsigned int i = row_idx[row]; i < row_idx[row + 1]; i++) {
        if (cols[i] == col) {
            return values[i];
        }
    }
    return 0;
}

double& CSR_SparseMatrix::operator()(unsigned int row, unsigned int col) {

    if (row >= nrow || col >= ncol) {
        std::cerr << "Error: index out of range" << std::endl;
        return values[0];
    }

    for (unsigned int i = row_idx[row]; i < row_idx[row + 1]; i++) {
        if (cols[i] == col) {
            return values[i];
        }
    }
    cols.push_back(col);
    values.push_back(0);

    // increment all row indices after row
    for (unsigned int i = row + 1; i < nrow + 1; i++) {
        row_idx[i]++;
    }

    return values[nnz++];
}

// matrix-vector product with override on * operator
std::vector<double> CSR_SparseMatrix::operator*(std::vector<double> vec) const {

    if (vec.size() != ncol) {
        std::cerr << "Error: vector size does not match matrix size" << std::endl;
        return std::vector<double>();
    }

    std::vector<double> res(nrow, 0);
    for (unsigned int i = 0; i < nrow; i++) {
        for (unsigned int j = row_idx[i]; j < row_idx[i + 1]; j++) {
            res[i] += values[j] * vec[cols[j]];
        }
    }
    return res;
}