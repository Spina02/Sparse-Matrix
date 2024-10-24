#include <iostream>
#include <vector>
#include "SparseMatrix.hpp"
#include "COO_SparseMatrix.hpp"
#include "CSR_SparseMatrix.hpp"

void print_vec(std::vector<double> vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << std::endl;
    }
    std::cout << std::endl;

}

int main() {

    // create a COO sparse matrix
    COO_SparseMatrix coo(3, 3);
    coo(0, 1) = 2;
    coo(1, 0) = 2;
    coo(2, 2) = 2;
    coo.print();

    // create a vector
    std::vector<double> vec = {1, 2, 3};

    print_vec(vec);

    // matrix-vector product
    std::vector<double> res = coo * vec;

    print_vec(res);

    return 0;
}