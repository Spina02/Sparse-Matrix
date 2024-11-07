#ifndef COOSPARSEMATRIX_H
#define COOSPARSEMATRIX_H

#include <vector>
#include <iostream>
#include "SparseMatrix.hpp"

template<typename T>
class COO_SparseMatrix : public SparseMatrix<T> {
public:
    // Constructor
    COO_SparseMatrix(unsigned int nrow, unsigned int ncol);

    // Copy constructor
    COO_SparseMatrix(const SparseMatrix<T>& other);

    // Destructor
    ~COO_SparseMatrix();

    // Utility functions
    static COO_SparseMatrix<T>& random(unsigned int nrow, unsigned int ncol, double density = 0.3);
    CSR_SparseMatrix<T> coo2csr() const;

    // Operator overloading
    T operator()(unsigned int row, unsigned int col) const override;
    T& operator()(unsigned int row, unsigned int col) override;
    std::vector<T> operator*(const std::vector<T>& vec) const override;
    bool operator==(const SparseMatrix<T>& other) const override;

private:
    std::vector<unsigned int> rows, cols;
};

//? ------------------- Implementation -------------------

// Constructor
template<typename T>
COO_SparseMatrix<T>::COO_SparseMatrix(unsigned int nrow, unsigned int ncol) : SparseMatrix<T>(nrow, ncol) {
    rows = std::vector<unsigned int>();
    cols = std::vector<unsigned int>();
    this->values = std::vector<T>();
}

// Copy constructor
template<typename T>
COO_SparseMatrix<T>::COO_SparseMatrix(const SparseMatrix<T>& other) : SparseMatrix<T>(other) {
    if (const CSR_SparseMatrix<T>* csr = dynamic_cast<const CSR_SparseMatrix<T>*>(&other)) {
        *this = csr->csr2coo();
    } else if (const COO_SparseMatrix<T>* coo = dynamic_cast<const COO_SparseMatrix<T>*>(&other)) {
        rows = coo->rows;
        cols = coo->cols;
        this->values = coo->values;
        this->nnz = coo->nnz;
    } else {
        std::cerr << "Error: Unsupported SparseMatrix type" << std::endl;
    }
}

// Destructor
template<typename T>
COO_SparseMatrix<T>::~COO_SparseMatrix() {
    rows.clear();
    cols.clear();
}

//? ------------------- Utility functions -------------------

// Generate random COO matrix
template<typename T>
COO_SparseMatrix<T>& COO_SparseMatrix<T>::random(unsigned int nrow, unsigned int ncol, double density) {
    srand(static_cast<unsigned int>(time(0)));
    COO_SparseMatrix<T>* res = new COO_SparseMatrix<T>(nrow, ncol);
    for (unsigned int i = 0; i < nrow; i++) {
        for (unsigned int j = 0; j < ncol; j++) {
            if ((double)rand() / RAND_MAX < density) {
                double mantissa = (double)rand() / RAND_MAX;
                double intpart = (double)(rand() % 100);
                (*res)(i, j) = mantissa + intpart;
            }
        }
    }
    return *res;
}

// Convert COO to CSR
template<typename T>
CSR_SparseMatrix<T> COO_SparseMatrix<T>::coo2csr() const {
    CSR_SparseMatrix<T> res(this->nrow, this->ncol);
    for (unsigned int i = 0; i < this->nnz; i++) {
        res(rows[i], cols[i]) = this->values[i];
    }
    return res;
}

//? ------------------- Operator overloading -------------------

// Get value at (row, col)
template<typename T>
T COO_SparseMatrix<T>::operator()(unsigned int row, unsigned int col) const {
    if (row >= this->nrow || col >= this->ncol) {
        std::cerr << "Error: index out of range" << std::endl;
        static T temp = T();
        return temp;
    }
    for (unsigned int i = 0; i < this->nnz; i++) {
        if (rows[i] == row && cols[i] == col) {
            return this->values[i];
        }
    }
    static T temp = T();
    return temp;
}

// insert or update value at (row, col)
template<typename T>
T& COO_SparseMatrix<T>::operator()(unsigned int row, unsigned int col) {
    if (row >= this->nrow || col >= this->ncol) {
        std::cerr << "Error: index out of range" << std::endl;
        return this->values[0]; // Considera il comportamento di default appropriato
    }
    for (unsigned int i = 0; i < this->nnz; i++) {
        if (rows[i] == row && cols[i] == col) {
            return this->values[i];
        }
    }
    rows.push_back(row);
    cols.push_back(col);
    this->values.push_back(T());
    return this->values[this->nnz++];
}

// matrix-vector product with override on * operator
template<typename T>
std::vector<T> COO_SparseMatrix<T>::operator*(const std::vector<T>& vec) const {
    if (vec.size() != this->ncol) {
        std::cerr << "Error: vector size does not match matrix size" << std::endl;
        return std::vector<T>();
    }
    std::vector<T> res(this->nrow, T());
    for (unsigned int i = 0; i < this->nnz; i++) {
        res[rows[i]] += this->values[i] * vec[cols[i]];
    }
    return res;
}

template<typename T>
bool COO_SparseMatrix<T>::operator==(const SparseMatrix<T>& other) const {
    if (this->nrow != other.get_rows() || this->ncol != other.get_cols() || this->nnz != other.get_nnz()) {
        return false;
    }
    for (unsigned int i = 0; i < this->nnz; i++) {
        if (other(rows[i], cols[i]) != this->values[i]) {
            return false;
        }
    }
    return true;
}

#endif
