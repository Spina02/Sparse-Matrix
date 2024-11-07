#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <vector>
#include <iostream>
#include <iomanip>

// Forward declarations
template<typename T> class COO_SparseMatrix;
template<typename T> class CSR_SparseMatrix;

template<typename T>
class SparseMatrix {
public:
    SparseMatrix(unsigned int nrow, unsigned int ncol);
    SparseMatrix(const SparseMatrix& other);
    virtual ~SparseMatrix();

    unsigned int get_rows() const;
    unsigned int get_cols() const;
    unsigned int get_nnz() const;

    void print() const;

    SparseMatrix& operator=(const SparseMatrix& other);
    
    virtual T operator()(unsigned int row, unsigned int col) const = 0;
    virtual T& operator()(unsigned int row, unsigned int col) = 0;
    virtual std::vector<T> operator*(const std::vector<T>& vec) const = 0;
    virtual bool operator==(const SparseMatrix<T>& other) const = 0;

protected:
    unsigned int nrow, ncol, nnz = 0;
    std::vector<T> values;

    // Friend classes
    friend class COO_SparseMatrix<T>;
    friend class CSR_SparseMatrix<T>;
};

//? ------------------- Implementations -------------------

template <typename T>
SparseMatrix<T>::SparseMatrix(unsigned int nrow, unsigned int ncol) : nrow(nrow), ncol(ncol) {
    values = std::vector<T>();
}

// Copy constructor
template <typename T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix& other)
    : nrow(other.nrow), ncol(other.ncol), nnz(other.nnz), values(other.values) {
}

// Destructor
template <typename T>
SparseMatrix<T>::~SparseMatrix() {
    values.clear();
}

// Get the number of rows
template <typename T>
unsigned int SparseMatrix<T>::get_rows() const {
    return nrow;
}

// Get the number of columns
template <typename T>
unsigned int SparseMatrix<T>::get_cols() const {
    return ncol;
}

// Get the number of non-zero elements
template <typename T>
unsigned int SparseMatrix<T>::get_nnz() const {
    return nnz;
}

// Assignment operator
template <typename T>
SparseMatrix<T>& SparseMatrix<T>::operator=(const SparseMatrix& other) {
    if (this != &other) {
        nrow = other.nrow;
        ncol = other.ncol;
        nnz = other.nnz;
        values = other.values;
    }
    return *this;
}

// Print the matrix
template <typename T>
void SparseMatrix<T>::print() const {
    std::cout << std::fixed << std::setprecision(2);
    for (unsigned int i = 0; i < nrow; ++i) {
        for (unsigned int j = 0; j < ncol; ++j) {
            std::cout << std::setw(7) << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#endif
