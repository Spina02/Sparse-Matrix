#include <vector>
#include <iostream>

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

class COO_SparseMatrix; // Forward declaration
class CSR_SparseMatrix; // Forward declaration

class SparseMatrix {
    public:
        //? ------------- Constructors and Destructor ------------
        // Constructor
        SparseMatrix(unsigned int nrow, unsigned int ncol);
        // Copy constructor
        SparseMatrix(const SparseMatrix& other);
        // Destructor
        virtual ~SparseMatrix() = 0;

        //? ------------- Utility functions ------------
        
        // get number of rows, columns, and non-zero elements
        unsigned int get_rows() const;
        unsigned int get_cols() const;
        unsigned int get_nnz() const;

        // print matrix
        void print() const;

        //? ----------- Operator overloading -----------
        
        // Copy assignment operator
        SparseMatrix& operator=(const SparseMatrix& other);
        
        // getter with override on () const operator
        virtual double operator()(unsigned int row, unsigned int col) const = 0;
        // setter with override on () operator
        virtual double& operator()(unsigned int row, unsigned int col) = 0;
        
        // matrix-vextor product with override on * operator
        virtual std::vector<double> operator*(std::vector<double> vec) const = 0;
        
        // compare two matrices
        virtual bool operator==(const SparseMatrix& other) const = 0;

    protected:
        unsigned int nrow, ncol, nnz = 0;
        std::vector<double> values;

        // Friend classes for double dispatch
        friend class COO_SparseMatrix;
        friend class CSR_SparseMatrix;
};

#endif