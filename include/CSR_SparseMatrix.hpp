#ifndef CSRSPARSEMATRIX_H
#define CSRSPARSEMATRIX_H

#include <vector>
#include "SparseMatrix.hpp"

class CSR_SparseMatrix : public SparseMatrix {
    public:
        // Constructor
        CSR_SparseMatrix(unsigned int nrow, unsigned int ncol);
        // Destructor
        ~CSR_SparseMatrix();
        // get and set values with override on () operator
        double operator()(unsigned int row, unsigned int col) const override;
        double& operator()(unsigned int row, unsigned int col) override;
        // matrix-vextor product with override on * operator
        std::vector<double> operator*(std::vector<double> vec) const override;

    private:
        std::vector<unsigned int> row_idx, cols;
        std::vector<double> values;
};

#endif