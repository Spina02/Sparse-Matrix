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

    // base class destructor is called automatically here
}

//get and set values with override on () operator
double COO_SparseMatrix::operator()(unsigned int row, unsigned int col) const {
    
    if (row >= nrow || col >= ncol) {
        std::cerr << "Error: index out of range" << std::endl;
        return 0;
    }
    
    for (unsigned int i = 0; i < nnz; i++) {
        if (rows[i] == row && cols[i] == col) {
            return values[i];
        }
    }
    return 0;
}

double& COO_SparseMatrix::operator()(unsigned int row, unsigned int col) {
    
    if (row >= nrow || col >= ncol) {
        std::cerr << "Error: index out of range" << std::endl;
        return values[0];
    }
    
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
    
    if (vec.size() != ncol) {
        std::cerr << "Error: vector size does not match matrix size" << std::endl;
        return std::vector<double>();
    }

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
