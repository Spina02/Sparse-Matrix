#include "tests.hpp"

void print_vec(std::vector<double> vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << std::endl;
    }
    std::cout << std::endl;
}

bool test_equal() {
    std::cout << "Testing equality operator" << std::endl;

    // store tests result
    bool passed = 1;
    std::vector res = std::vector<bool>(6, false);

    CSR_SparseMatrix csr1(3, 3);
    csr1(0, 1) = 2;
    csr1(1, 0) = 2;
    csr1(2, 2) = 2;

    CSR_SparseMatrix csr2(3, 3);
    csr2(0, 1) = 2;
    csr2(1, 0) = 2;
    csr2(2, 2) = 2;

    CSR_SparseMatrix csr3(3, 3);
    csr3(0, 1) = 2;
    csr3(1, 0) = 2;
    csr3(2, 2) = 3;

    COO_SparseMatrix coo1(3, 3);
    coo1(0, 1) = 2;
    coo1(1, 0) = 2;
    coo1(2, 2) = 2;

    COO_SparseMatrix coo2(3, 3);
    coo2(0, 1) = 2;
    coo2(1, 0) = 2;
    coo2(2, 2) = 2;

    COO_SparseMatrix coo3(3, 3);
    coo3(0, 1) = 2;
    coo3(1, 0) = 2;
    coo3(2, 2) = 3;

    res[0] = (csr1 == csr2) == true;
    res[1] = (csr1 == csr3) == false;
    res[2] = (coo1 == coo2) == true;
    res[3] = (coo1 == coo3) == false;
    res[4] = (csr1 == coo1) == true;
    res[5] = (csr1 == coo3) == false;

    for (unsigned int i = 0; i < res.size(); i++) {
        if (res[i]) {
            std::cout << "Test " << i << " passed" << std::endl;
        } else {
            passed = 0;
            std::cout << "Test " << i << " failed" << std::endl;
        }
    }

    // free memory
    res.clear();

    return passed;
}

bool test_matrix_vector_product() {
    std::cout << "Testing matrix-vector product" << std::endl;

    // store tests result
    bool passed = 1;
    std::vector res = std::vector<bool>(4, false);

    CSR_SparseMatrix csr(3, 3);
    csr(0, 1) = 2;
    csr(1, 0) = 2;
    csr(2, 2) = 2;

    COO_SparseMatrix coo(3, 3);
    coo(0, 1) = 2;
    coo(1, 0) = 2;
    coo(2, 2) = 2;

    std::vector<double> vec1 = {1, 2, 3};
    std::vector<double> vec2 = {-1, 0, 1};

    std::vector<double> res_csr1 = csr*vec1;
    std::vector<double> res_coo1 = coo*vec1;
    std::vector<double> res_csr2 = csr*vec2;
    std::vector<double> res_coo2 = coo*vec2;

    res[0] = (res_coo1 == std::vector<double>({4, 2, 6}));
    res[1] = (res_csr1 == std::vector<double>({4, 2, 6}));
    res[2] = (res_coo2 == std::vector<double>({0, -2, 2}));
    res[3] = (res_csr2 == std::vector<double>({0, -2, 2}));

    for (unsigned int i = 0; i < res.size(); i++) {
        if (res[i]) {
            std::cout << "Test " << i << " passed" << std::endl;
        } else {
            passed = 0;
            std::cout << "Test " << i << " failed" << std::endl;
        }
    }

    // free memory
    res_csr1.clear();
    res_coo1.clear();
    res_csr2.clear();
    res_coo2.clear();
    res.clear();

    return passed;
}

bool test_conversion() {
    std::cout << "Testing conversion" << std::endl;

    // store tests result
    bool passed = 1;
    std::vector res = std::vector<bool>(2, false);

    CSR_SparseMatrix csr(3, 3);
    csr(0, 1) = 2;
    csr(1, 0) = 2;
    csr(2, 2) = 2;

    COO_SparseMatrix coo = csr;

    CSR_SparseMatrix csr2 = coo;

    res[0] = (coo == csr);
    res[1] = (csr == csr2);

    for (unsigned int i = 0; i < res.size(); i++) {
        if (res[i]) {
            std::cout << "Test " << i << " passed" << std::endl;
        } else {
            passed = 0;
            std::cout << "Test " << i << " failed" << std::endl;
        }
    }

    // free memory
    res.clear();

    return passed;
}

bool test_copy() {
    std::cout << "Testing copy" << std::endl;

    // store tests result
    bool passed = 1;
    std::vector res = std::vector<bool>(8, false);

    CSR_SparseMatrix csr(3, 3);
    csr(0, 1) = 2;
    csr(1, 0) = 2;
    csr(2, 2) = 2;

    CSR_SparseMatrix csr_eq = csr;
    COO_SparseMatrix coo_cp(csr);
    COO_SparseMatrix coo_eq = csr;

    res[0] = (csr == csr_eq);
    res[1] = (csr == coo_cp);
    res[2] = (csr == coo_eq);
    res[3] = (coo_cp == coo_eq);

    COO_SparseMatrix coo(3, 3);
    coo(0, 0) = 2;
    coo(1, 2) = 2;
    coo(2, 1) = 2;

    COO_SparseMatrix coo_eq2 = coo;
    CSR_SparseMatrix csr_cp(coo);
    CSR_SparseMatrix csr_eq2 = coo;

    res[4] = (coo == coo_eq2);
    res[5] = (coo == csr_cp);
    res[6] = (coo == csr_eq2);
    res[7] = (csr_cp == csr_eq2);

    for (unsigned int i = 0; i < res.size(); i++) {
        if (res[i]) {
            std::cout << "Test " << i << " passed" << std::endl;
        } else {
            passed = 0;
            std::cout << "Test " << i << " failed" << std::endl;
        }
    }

    // free memory
    res.clear();

    return passed;
}