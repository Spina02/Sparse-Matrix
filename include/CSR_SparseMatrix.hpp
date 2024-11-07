#ifndef CSRSPARSEMATRIX_H
#define CSRSPARSEMATRIX_H

#include <vector>
#include <iostream>
#include "SparseMatrix.hpp"
#include "COO_SparseMatrix.hpp"

template<typename T>
class CSR_SparseMatrix : public SparseMatrix<T> {
public:
    // Constructor
    CSR_SparseMatrix(unsigned int nrow, unsigned int ncol);

    // Copy constructor
    CSR_SparseMatrix(const SparseMatrix<T>& other);

    // Destructor
    ~CSR_SparseMatrix();

    // Utility functions
    static CSR_SparseMatrix<T>& random(unsigned int nrow, unsigned int ncol, double density = 0.3);
    COO_SparseMatrix<T> csr2coo() const;

    // Operator overloading
    T operator()(unsigned int row, unsigned int col) const override;
    T& operator()(unsigned int row, unsigned int col) override;
    std::vector<T> operator*(const std::vector<T>& vec) const override;
    bool operator==(const SparseMatrix<T>& other) const override;

private:
    std::vector<unsigned int> row_idx, cols;
};

// Implementation

// Constructor
template<typename T>
CSR_SparseMatrix<T>::CSR_SparseMatrix(unsigned int nrow, unsigned int ncol) : SparseMatrix<T>(nrow, ncol) {
    cols = std::vector<unsigned int>();
    row_idx = std::vector<unsigned int>(nrow + 1, 0);
}

// Copy constructor
template<typename T>
CSR_SparseMatrix<T>::CSR_SparseMatrix(const SparseMatrix<T>& other) : SparseMatrix<T>(other) {
    if (const COO_SparseMatrix<T>* coo = dynamic_cast<const COO_SparseMatrix<T>*>(&other)) {
        *this = coo->coo2csr();
    } else if (const CSR_SparseMatrix<T>* csr = dynamic_cast<const CSR_SparseMatrix<T>*>(&other)) {
        row_idx = csr->row_idx;
        cols = csr->cols;
        this->values = csr->values;
        this->nnz = csr->nnz;
    } else {
        std::cerr << "Error: Unsupported SparseMatrix type" << std::endl;
    }
}

// Destructor
template<typename T>
CSR_SparseMatrix<T>::~CSR_SparseMatrix() {
    cols.clear();
    row_idx.clear();
}

// Operator overloading
template<typename T>
T CSR_SparseMatrix<T>::operator()(unsigned int row, unsigned int col) const {
    if (row >= this->nrow || col >= this->ncol) {
        std::cerr << "Error: index out of range" << std::endl;
        static T temp = T();
        return temp;
    }
    for (unsigned int i = row_idx[row]; i < row_idx[row + 1]; i++) {
        if (cols[i] == col) {
            return this->values[i];
        }
    }
    static T temp = T();
    return temp;
}

template<typename T>
T& CSR_SparseMatrix<T>::operator()(unsigned int row, unsigned int col) {
    if (row >= this->nrow || col >= this->ncol) {
        std::cerr << "Error: index out of range" << std::endl;
        return this->values[0]; // Return a reference to the first element as an error case
    }

    // Search for the position to insert or find existing element
    unsigned int insert_pos = row_idx[row];
    for (; insert_pos < row_idx[row + 1]; insert_pos++) {
        if (cols[insert_pos] == col) {
            // Element already exists
            return this->values[insert_pos];
        }
        else if (cols[insert_pos] > col) {
            // Found insertion point
            break;
        }
    }

    // Insert the new element at insert_pos
    cols.insert(cols.begin() + insert_pos, col);
    this->values.insert(this->values.begin() + insert_pos, T());
    this->nnz++;

    // Update row_idx
    for (unsigned int i = row + 1; i < this->nrow + 1; i++) {
        row_idx[i]++;
    }

    return this->values[insert_pos];
}

template<typename T>
std::vector<T> CSR_SparseMatrix<T>::operator*(const std::vector<T>& vec) const {
    if (vec.size() != this->ncol) {
        std::cerr << "Error: vector size does not match matrix size" << std::endl;
        return std::vector<T>();
    }

    std::vector<T> res(this->nrow, T());
    for (unsigned int i = 0; i < this->nrow; i++) {
        for (unsigned int j = row_idx[i]; j < row_idx[i + 1]; j++) {
            res[i] += this->values[j] * vec[cols[j]];
        }
    }
    return res;
}

template<typename T>
bool CSR_SparseMatrix<T>::operator==(const SparseMatrix<T>& other) const {
    if (this->nrow != other.get_rows() || this->ncol != other.get_cols() || this->nnz != other.get_nnz()) {
        return false;
    }
    for (unsigned int i = 0; i < this->nrow; i++) {
        for (unsigned int j = row_idx[i]; j < row_idx[i + 1]; j++) {
            if (other(i, cols[j]) != this->values[j]) {
                return false;
            }
        }
    }
    return true;
}

// Utility functions
template<typename T>
CSR_SparseMatrix<T>& CSR_SparseMatrix<T>::random(unsigned int nrow, unsigned int ncol, double density) {
    srand(static_cast<unsigned int>(time(0) + 1));
    CSR_SparseMatrix<T>* res = new CSR_SparseMatrix<T>(nrow, ncol);
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

template<typename T>
COO_SparseMatrix<T> CSR_SparseMatrix<T>::csr2coo() const {
    COO_SparseMatrix<T> res(this->nrow, this->ncol);
    for (unsigned int i = 0; i < this->nrow; i++) {
        for (unsigned int j = row_idx[i]; j < row_idx[i + 1]; j++) {
            res(i, cols[j]) = this->values[j];
        }
    }
    return res;
}

#endif
