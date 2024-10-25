#ifndef CSRSPARSEMATRIX_H
#define CSRSPARSEMATRIX_H

#include <vector>
#include "SparseMatrix.hpp"
//#include "COO_SparseMatrix.hpp"

class CSR_SparseMatrix : public SparseMatrix {
    public:
        // Constructor
        CSR_SparseMatrix(unsigned int nrow, unsigned int ncol);
        // Copy constructor
        CSR_SparseMatrix(const SparseMatrix& other);
        // Destructor
        ~CSR_SparseMatrix();

        //coo to csr converter
        COO_SparseMatrix csr2coo() const;

        // getter with override on () const operator
        double operator()(unsigned int row, unsigned int col) const override;
        // setter with override on () operator
        double& operator()(unsigned int row, unsigned int col) override;
        // matrix-vextor product with override on * operator
        std::vector<double> operator*(std::vector<double> vec) const override;
        // compare two matrices
        bool operator==(const SparseMatrix& other) const override;

    private:
        std::vector<unsigned int> row_idx, cols;
};

#endif