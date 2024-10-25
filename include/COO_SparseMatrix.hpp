#ifndef COOSPARSEMATRIX_H
#define COOSPARSEMATRIX_H

#include <vector>
#include "SparseMatrix.hpp"
//#include "CSR_SparseMatrix.hpp"

class COO_SparseMatrix : public SparseMatrix {
    public:
        //? ------------- Constructors and Destructor ------------
        // Constructor
        COO_SparseMatrix(unsigned int nrow, unsigned int ncol);
        // Copy constructor
        COO_SparseMatrix(const SparseMatrix& other);
        // Destructor
        ~COO_SparseMatrix();

        //? ------------- Utility functions ------------
        static COO_SparseMatrix& random(unsigned int nrow, unsigned int ncol, double density = 0.3);

        //csr to coo converter
        CSR_SparseMatrix coo2csr() const;

        //? ----------- Operator overloading -----------
        // getter with override on () const operator
        double operator()(unsigned int row, unsigned int col) const override;
        // setter with override on () operator
        double& operator()(unsigned int row, unsigned int col) override;
        // matrix-vextor product with override on * operator
        std::vector<double> operator*(std::vector<double> vec) const override;
        // compare two matrices
        bool operator==(const SparseMatrix& other) const override;

    private:
        std::vector<unsigned int> rows, cols;
};

#endif