#include <vector>

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

class SparseMatrix {
    public:
        // Constructor
        SparseMatrix(unsigned int nrow, unsigned int ncol);
        // Destructor
        virtual ~SparseMatrix() = 0;

        // get number of rows, columns, and non-zero elements
        unsigned int get_rows() const;
        unsigned int get_cols() const;
        unsigned int get_nnz() const;

        // get and set values with override on () operator
        virtual double operator()(unsigned int row, unsigned int col) const = 0; // get
        virtual double& operator()(unsigned int row, unsigned int col) = 0;      // set

        // matrix-vextor product with override on * operator
        virtual std::vector<double> operator*(std::vector<double> vec) const = 0;

        // print matrix
        void print() const;

    protected:
        unsigned int nrow, ncol, nnz = 0;
        std::vector<double> values;
};

#endif