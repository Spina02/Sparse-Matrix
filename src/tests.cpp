#include "tests.hpp"
#include <algorithm>

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

    CSR_SparseMatrix csr3 = CSR_SparseMatrix::random(3, 3);

    COO_SparseMatrix coo1(3, 3);
    coo1(0, 1) = 2;
    coo1(1, 0) = 2;
    coo1(2, 2) = 2;

    COO_SparseMatrix coo2(3, 3);
    coo2(0, 1) = 2;
    coo2(1, 0) = 2;
    coo2(2, 2) = 2;

    COO_SparseMatrix coo3 = COO_SparseMatrix::random(3, 3);

    res[0] = (csr1 == csr2) == true;
    res[1] = (csr1 == csr3) == false;
    res[2] = (coo1 == coo2) == true;
    res[3] = (coo1 == coo3) == false;
    res[4] = (csr1 == coo1) == true;
    res[5] = (csr1 == coo3) == false;


    // free memory
    res.clear();

    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

bool test_matrix_vector_product() {
    std::cout << "Testing matrix-vector product" << std::endl;

    // store tests result
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
        std::cout << "Test " << i << (res[i] ? " passed" : "failed") << std::endl;
    }

    // free memory
    res_csr1.clear();
    res_coo1.clear();
    res_csr2.clear();
    res_coo2.clear();
    res.clear();

    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

bool test_copy_convertion() {
    std::cout << "Testing copy and conversion" << std::endl;

    // store tests result
    std::vector res = std::vector<bool>(8, false);

    CSR_SparseMatrix csr = CSR_SparseMatrix::random(3, 3);

    CSR_SparseMatrix csr_eq = csr;
    COO_SparseMatrix coo_cp(csr);
    COO_SparseMatrix coo_eq = csr;

    res[0] = (csr == csr_eq);
    res[1] = (csr == coo_cp);
    res[2] = (csr == coo_eq);
    res[3] = (coo_cp == coo_eq);

    COO_SparseMatrix coo = COO_SparseMatrix::random(3, 3);

    COO_SparseMatrix coo_eq2 = coo;
    CSR_SparseMatrix csr_cp(coo);
    CSR_SparseMatrix csr_eq2 = coo;

    res[4] = (coo == coo_eq2);
    res[5] = (coo == csr_cp);
    res[6] = (coo == csr_eq2);
    res[7] = (csr_cp == csr_eq2);

    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Test " << i << (res[i] ? " passed" : "failed") << std::endl;
    }

    // free memory
    res.clear();

    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

bool test_row_sum() {
    std::cout << "Testing matrix-vector product with vector of ones" << std::endl;
    
    std::vector<bool> res(4, false);
    
    // Create test matrices
    CSR_SparseMatrix csr(3, 3);
    csr(0, 0) = 1; csr(0, 1) = 2; csr(0, 2) = 3;
    csr(1, 0) = 4; csr(1, 2) = 5;
    csr(2, 1) = 6; csr(2, 2) = 7;
    
    COO_SparseMatrix coo(3, 3);
    coo(0, 0) = 1; coo(0, 1) = 2; coo(0, 2) = 3;
    coo(1, 0) = 4; coo(1, 2) = 5;
    coo(2, 1) = 6; coo(2, 2) = 7;
    
    // Vector of ones
    std::vector<double> ones(3, 1.0);
    
    // Expected row sums
    std::vector<double> expected_sums = {6, 9, 13};  // Sum of each row
    
    // Test CSR and COO implementations
    auto csr_result = csr * ones;
    auto coo_result = coo * ones;
    
    res[0] = (csr_result == expected_sums);
    res[1] = (coo_result == expected_sums);
    
    // Test that both implementations give same results
    res[2] = (csr_result == coo_result);
    
    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Test " << i << (res[i] ? " passed" : " failed") << std::endl;
    }
    
    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

bool test_canonical_basis() {
    std::cout << "Testing matrix-vector product with canonical basis vectors" << std::endl;
    
    std::vector<bool> res;
    
    // Create test matrices
    CSR_SparseMatrix csr(3, 3);
    csr(0, 0) = 1; csr(0, 1) = 2; csr(0, 2) = 3;
    csr(1, 0) = 4; csr(1, 2) = 5;
    csr(2, 1) = 6; csr(2, 2) = 7;
    
    // Test with each canonical basis vector
    for (size_t i = 0; i < 3; ++i) {
        std::vector<double> e_i(3, 0.0);
        e_i[i] = 1.0;
        
        auto result = csr * e_i;
        
        // Verify that result matches the i-th column
        for (size_t j = 0; j < 3; ++j) {
            res.push_back(std::abs(result[j] - csr(j, i)) < 1e-10);
        }
    }
    
    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Test " << i << (res[i] ? " passed" : " failed") << std::endl;
    }
    
    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}

bool test_empty_matrix() {
    std::cout << "Testing edge cases (ignore errors)" << std::endl;
    
    std::vector<bool> res;
    
    // Test 0x0 matrix
    CSR_SparseMatrix empty_csr(0, 0);
    std::vector<double> empty_vec;
    auto result = empty_csr * empty_vec;
    res.push_back(result.empty());
    
    // Test matrix-vector multiplication with mismatched dimensions
    CSR_SparseMatrix csr(3, 3);
    std::vector<double> wrong_size_vec(4, 1.0);
    result = csr * wrong_size_vec;
    res.push_back(result.empty());
    
    for (unsigned int i = 0; i < res.size(); i++) {
        std::cout << "Test " << i << (res[i] ? " passed" : " failed") << std::endl;
    }
    
    return std::all_of(res.begin(), res.end(), [](bool v) { return v; });
}