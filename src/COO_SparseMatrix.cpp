#include <iostream>
#include "COO_SparseMatrix.hpp"

//constructor
COO_SparseMatrix::COO_SparseMatrix(unsigned int nrow, unsigned int ncol) : SparseMatrix(nrow, ncol) {
    // initialize empty vectors
    rows = std::vector<unsigned int>();
    cols = std::vector<unsigned int>();
    values = std::vector<double>();
}

// destructor
COO_SparseMatrix::~COO_SparseMatrix() {
    // destroy vectors
    rows.clear();
    cols.clear();
    values.clear();

    // base class destructor is called automatically here
}

//get and set values with override on () operator
double COO_SparseMatrix::operator()(unsigned int row, unsigned int col) const {
    for (unsigned int i = 0; i < nnz; i++) {
        if (rows[i] == row && cols[i] == col) {
            return values[i];
        }
    }
    return 0;
}

double& COO_SparseMatrix::operator()(unsigned int row, unsigned int col) {
    for (unsigned int i = 0; i < nnz; i++) {
        if (rows[i] == row && cols[i] == col) {
            return values[i];
        }
    }
    rows.push_back(row);
    cols.push_back(col);
    values.push_back(0);
    return values[nnz++];
}

// matrix-vector product with override on * operator
std::vector<double> COO_SparseMatrix::operator*(std::vector<double> vec) const {
    std::vector<double> res(ncol, 0);
    for (unsigned int i = 0; i < nnz; i++) {
        for (unsigned int j = 0; j < ncol; j++) {
            if (cols[i] == j) {
                res[rows[i]] += values[i] * vec[j];
            }
        }
    }
    return res;
}

void COO_SparseMatrix::print() const {
    unsigned int i = 0, j = 0;
    for (i = 0; i < nrow; ++i) {
        for (j = 0; j < ncol; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
