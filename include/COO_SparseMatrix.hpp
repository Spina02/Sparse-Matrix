#ifndef COOSPARSEMATRIX_H
#define COOSPARSEMATRIX_H

#include <vector>
#include "SparseMatrix.hpp"

class COO_SparseMatrix : public SparseMatrix {
    public:
        // Constructor
        COO_SparseMatrix(unsigned int nrow, unsigned int ncol);
        // Destructor
        ~COO_SparseMatrix();
        // get and set values with override on () operator
        double operator()(unsigned int row, unsigned int col) const override;
        double& operator()(unsigned int row, unsigned int col) override;
        // matrix-vextor product with override on * operator
        std::vector<double> operator*(std::vector<double> vec) const override;
        // print matrix
        void print() const override;

    private:
        std::vector<unsigned int> rows, cols;
};

#endif