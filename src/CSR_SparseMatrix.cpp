#include "CSR_SparseMatrix.hpp"
#include "COO_SparseMatrix.hpp"
#include <iostream>

// contructor
CSR_SparseMatrix::CSR_SparseMatrix(unsigned int nrow, unsigned int ncol) : SparseMatrix(nrow, ncol) {
    // initialize empty vectors
    cols = std::vector<unsigned int>();
    // initialize row_idx with nrow+1 elements
    row_idx = std::vector<unsigned int>(nrow + 1, 0);
}

// copy constructor
// override of = operator, if other is csr matrix, convert it to coo matrix
CSR_SparseMatrix::CSR_SparseMatrix(const SparseMatrix& other) : SparseMatrix(other) {

    if (const COO_SparseMatrix* coo = dynamic_cast<const COO_SparseMatrix*>(&other)) {
        // convert other to coo matrix
        *this = coo->coo2csr();
    } else {
        // cast other to coo matrix
        const CSR_SparseMatrix& csr = dynamic_cast<const CSR_SparseMatrix&>(other);
        // copy values
        row_idx = csr.row_idx;
        cols = csr.cols;
    }
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

bool CSR_SparseMatrix::operator==(const SparseMatrix& other) const {
    if (nrow != other.get_rows() || ncol != other.get_cols() || nnz != other.get_nnz()) {
        return false;
    }
    for (unsigned int i = 0; i < nrow; i++) {
        for (unsigned int j = row_idx[i]; j < row_idx[i+1]; j++) {
            if (other(i, cols[j]) != values[j]) {
                return false;
            }
        }
    }
    return true;
}

// convert coo to csr matrix
COO_SparseMatrix CSR_SparseMatrix::csr2coo() const {
    COO_SparseMatrix res(nrow, ncol);
    for (unsigned int i = 0; i < nrow; i++) {
        for (unsigned int j = row_idx[i]; j < row_idx[i+1]; j++) {
            res(i, cols[j]) = values[j];
        }
    }
    return res;
}

// random csr matrix generator
CSR_SparseMatrix& CSR_SparseMatrix::random(unsigned int nrow, unsigned int ncol, double density) {
    // seed random number generator
    srand(static_cast<unsigned int>(time(0)+1)); // +1 to avoid same random matrix as coo
    CSR_SparseMatrix* res = new CSR_SparseMatrix(nrow, ncol);
    for (unsigned int i = 0; i < nrow; i++) {
        for (unsigned int j = 0; j < ncol; j++) {
            if ((double)rand() / RAND_MAX < density) {
                double mantissa = (double) rand() / RAND_MAX;
                double intpart = (double) (rand()%100);
                (*res)(i, j) =  mantissa + intpart;
            }
        }
    }
    return *res;
}