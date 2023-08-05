#include "hw1.h"
#include<iostream>
#include<vector>
#include<stdexcept>
#include<random>
#include<iomanip>

using std::cin; using std::cout; using std::endl;
using std::vector;

namespace algebra{ //namespace

Matrix zeros(size_t n, size_t m){
    if(m <= 0 || n <= 0){ //Checkout if arguments valid. 
        throw std::invalid_argument("Invalid_arguement! ");
    }
    Matrix createzeros;
    for(int i = 0;i < n; ++i){
        vector<double> tmp(m, 0);
        createzeros.push_back(tmp); 
    }
    return createzeros;
}

Matrix ones(size_t n, size_t m){
    if(m <= 0 || n <= 0){ //Checkout if arguments valid. 
        throw std::invalid_argument("Invalid_arguement! ");
    }
    Matrix createones;
    for(int i = 0;i < n; ++i){
        vector<double> tmp(m, 1);
        createones.push_back(tmp); 
    }
    return createones;
}

Matrix random(size_t n, size_t m, double min, double max){
    if(m <= 0 || n <= 0){ //Checkout if arguments valid. 
        throw std::invalid_argument("Invalid_arguement! ");
    }
    if(min > max){
        throw std::invalid_argument("min should not be greater than m=ax. ");        
    }
    Matrix create_Random;
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(min, max);
    e.seed(time(0));
    for(int i = 0; i < n; ++i){
        vector<double> tmp(m, 0);
        for(int j = 0; j < m; ++j){
            tmp[j] = u(e);
        }
        create_Random.push_back(tmp);
    }
    return create_Random;
}

void show(const Matrix& matrix){
    for(auto vec: matrix){
        for(auto num: vec){
            cout << std::setw(10) << std::fixed << std::setprecision(3) 
                << num <<' '; 
        }
        cout << endl;
    }
}

Matrix multiply(const Matrix& matrix, double c){
    if(matrix.size()==0)return matrix;
    Matrix new_matrix = matrix;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            new_matrix[i][j] = matrix[i][j] * c;
        }
    }
    return new_matrix;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2){
    if (matrix1.empty() && matrix2.empty()) {
        return matrix1;
    }
    if (matrix1.empty() || matrix2.empty()) {
        throw std::logic_error("calculation error\n");
    }
    int r1 = matrix1.size();
    int c1 = matrix1[0].size();
    int r2 = matrix2.size();
    int c2 = matrix2[0].size();
    if(c1 != r2){
        throw std::invalid_argument("Two matrixes can't multiply. ");
    }
    Matrix new_matrix = zeros(r1, c2);
    for(int i = 0; i < r1; ++i){
        for(int j = 0; j < c2; ++j){
            for(int k = 0; k < c1; ++k){
                new_matrix[i][j] += matrix1[i][k]*matrix2[k][j];
            }
        }
    }
    return new_matrix;
}

Matrix sum(const Matrix& matrix, double c){
    if (matrix.empty()) {
        return matrix;
    }
    Matrix new_matrix = matrix;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            new_matrix[i][j] = matrix[i][j] + c;
        }
    }
    return new_matrix;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2){
    if (matrix1.empty() && matrix2.empty()) {
        return matrix1;
    }
    if (matrix1.empty() || matrix2.empty()) {
        throw std::logic_error("calculation error\n");
    }
    int r1 = matrix1.size();
    int c1 = matrix1[0].size();
    int r2 = matrix2.size();
    int c2 = matrix2[0].size();
    if(r1 != r2 || c1 != c2){
        throw std::invalid_argument("Two matrixes are not the same scale. ");
    }
    Matrix new_matrix = matrix1;
    for(int i = 0; i < r1; ++i){
        for(int j = 0; j < c1; ++j){
            new_matrix[i][j] += matrix2[i][j];
        }
    }
    return new_matrix;
}

Matrix transpose(const Matrix& matrix){
    if (matrix.empty()) {
        return matrix;
    }
    int r = matrix.size();
    int c = matrix[0].size();
    Matrix new_matrix = zeros(c, r);
    for(int i = 0; i < c; ++i){
        for(int j = 0; j < r; ++j){
            new_matrix[i][j] = matrix[j][i];
        }
    }
    return new_matrix;
}

// Matrix minor(const Matrix& matrix, size_t n, size_t m){
//     if(n < 0 || m < 0 || n >= matrix.size() || m >= matrix[0].size()){
//         throw std::invalid_argument("Invalid arguments");
//     }
//     Matrix new_matrix;
//     for(int i = 0; i < matrix.size(); ++i){
//         if(i == n)continue; // drop this row
//         vector<double> rowvec;
//         for(int j = 0; j , matrix[0].size(); ++j){
//             if(j == m)continue; // drop the mth number in each row
//             rowvec.push_back(matrix[i][j]);
//         }
//         new_matrix.push_back(rowvec);
//     }
//     return new_matrix;
// } why segmentation fault?

Matrix minor(const Matrix& matrix, size_t n, size_t m) {
    if (n < 0 || n >= matrix.size() || m < 0 || m >= matrix[0].size()) {
        throw std::logic_error("out of bound\n");
    }

    Matrix x;
    for (int i = 0; i < matrix.size(); i++) {
        if (i == n) {
            continue;
        }
        vector<double> y;
        for (int j = 0; j < matrix[0].size(); j++) {
            if (j == m) {
                continue;
            }
            y.push_back(matrix[i][j]);
        }
        x.push_back(y);
    }
    return x;
}

double determinant(const Matrix& matrix){
    if(matrix.size() == 0)
        return 1;
    if(matrix.size() != matrix[0].size()){
        throw std::invalid_argument("The matrix is not square");
    }
    
    if(matrix.size() == 1)
        return matrix[0][0];
    else if(matrix.size() == 0)
        return matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
    double res = 0;
    //Algebraic congruence method
    for(int i = 0; i < matrix.size(); ++i){
        int flag = i%2==0? 1: -1;
        Matrix tmp = minor(matrix, 0, i);
        res += flag*matrix[0][i]*determinant(tmp);
    }
    return res;
}

Matrix inverse(const Matrix& matrix){
    if (matrix.size() == 0) {
        return matrix;
    }
    int det = determinant(matrix);
    if(matrix.size() != matrix[0].size()){
        throw std::invalid_argument("The matrix is not square");
    }else if(det == 0){
        throw std::invalid_argument("determinant = 0, inverse doesn't exist");
    }
    // I don't know how to compute an inverse of matrix in machine
    // so, the answer is copied from 
    //https://github.com/Daniel741312/AUT-1400/blob/main/AP1400-2-HW1-main/src/hw1.cpp
    int n = matrix.size();
    Matrix mat = zeros(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sign = (i + j) & 1 ? -1 : 1;
            Matrix mr = minor(matrix, i, j);
            mat[i][j] = sign * determinant(mr);
        }
    }
    mat = transpose(mat);
    return multiply(mat,1/det);
}

Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis){
    int r1 = matrix1.size(), r2 = matrix2.size();
    if(r1 == 0)return matrix2;
    if(r2 == 0)return matrix1;
    int c1 = matrix1[0].size(), c2 = matrix2[0].size();
    Matrix new_matrix;
    if(axis == 0){
        if(c1 != c2){
            throw std::invalid_argument("collum numbers do not match.");
        }
        new_matrix = zeros(r1 + r2, c1);
        for(int i = 0; i < r1+r2; ++i){
            for(int j = 0; j < c1; ++j){
                new_matrix[i][j] = i<r1?matrix1[i][j]: matrix2[i-r1][j];
            }
        }
        return new_matrix;
    }else if(axis == 1){
        if(r1 != r2){
            throw std::invalid_argument("row numbers do not match.");
        }
        new_matrix = zeros(r1, c1 + c2);
        for(int i = 0; i < r1; ++i){
            for(int j = 0; j < c1+c2; ++j){
                new_matrix[i][j] = j<c1?matrix1[i][j]: matrix2[i][j-c1];
            }
        }
        return new_matrix;
    }else{
        throw std::invalid_argument("axis must be 0 || 1");
    }
    
}

Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2){
    if(r1 >= matrix.size() || r2 >= matrix.size()){
        throw std::invalid_argument("row number too big");
    }
    Matrix new_matrix = matrix;
    vector<double> tmpvec = matrix[r1];
    new_matrix[r1] = matrix[r2];
    new_matrix[r2] = tmpvec;
    return new_matrix;
}

Matrix ero_multiply(const Matrix& matrix, size_t r, double c){
    if(r >= matrix.size()){
        throw std::invalid_argument("row number too big");
    }
    Matrix new_matrix = matrix;
    for(auto &i: new_matrix[r]){
        i *= c;
    }
    return new_matrix;
}

Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2){
    if(r1 >= matrix.size() || r2 >= matrix.size()){
        throw std::invalid_argument("row number too big");
    }
    Matrix new_matrix = matrix;
    vector<double> row_r1 = matrix[r1];
    for(int i = 0; i < matrix[0].size(); ++i){
        new_matrix[r2][i] += c*row_r1[i];
    }
    return new_matrix;
}

Matrix upper_triangular(const Matrix& matrix){
    if(matrix.size() <= 1)return matrix;
    if(matrix.size() != matrix[0].size()){
        throw std::invalid_argument("The matrix is not square");
    }
    Matrix new_matrix = matrix;
    for(int i = 0; i < new_matrix.size(); ++i){
        double x = new_matrix[i][i];
        for(int j = 0; j < new_matrix.size(); ++j){
            double y = new_matrix[j][i];
            new_matrix = ero_sum(new_matrix, i, -y/x, j);
        }
    }
    return new_matrix;
}

}