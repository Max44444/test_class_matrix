#include <iostream>
#include <ctime>
#include <cassert>
#include <cmath>
#include "matrix.h"

using namespace std;

//===================*CONSTRUCTOR*========================
       
Matrix::Matrix(int rows, int colomns){
    srand(time(NULL));
    this->rows = rows; 
    this->colomns = colomns;
    matrix = new int*[rows];

    for(int i = 0; i < rows; i++){
        matrix[i] = new int[colomns];
    }
}

Matrix::Matrix(const Matrix &other){
    srand(time(NULL));
    this->rows = other.rows;
    this->colomns = other.colomns;
    this->matrix = new int*[other.rows];
    for(int i = 0; i < other.rows; i++){
        this->matrix[i] = new int[other.colomns];
    }
    for(int i = 0; i < other.rows; i++){
        for(int j = 0; j < other.colomns; j++){
            this->matrix[i][j] = other.matrix[i][j];
        }
    }
}

//==================*OPERATORS*===============================

Matrix & Matrix::operator = (const Matrix &other){       
    this->rows = other.rows;
    this->colomns = other.colomns;

    if(this->matrix!=nullptr){
        for(int i = 0; i < this->rows; ++i)
            delete[] this->matrix[i];
        delete[] this->matrix;
    }

    this->matrix = new int*[other.rows];
    for(int i = 0; i < other.rows; i++){
        this->matrix[i] = new int[other.colomns];
    }
    for(int i = 0; i < other.rows; i++){
        for(int j = 0; j < other.colomns; j++){
            this->matrix[i][j] = other.matrix[i][j];
        }
    }
    return *this;
}

bool Matrix::operator == (const Matrix &other) const{
    bool result;
    result = this->rows == other.rows && this->colomns == other.colomns;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < colomns; j++){
            if(this->matrix[i][j] != other.matrix[i][j]) result = 0;
        }
    }
    return result;
}

bool Matrix::operator != (const Matrix &other) const{
    bool result;
    result = !(this->rows == other.rows && this->colomns == other.colomns);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < colomns; j++){
            if(this->matrix[i][j] == other.matrix[i][j]) result = 0;
        }
    }
    return result;
}

Matrix Matrix::operator + (const Matrix &other) const{
    assert(this->rows == other.rows && this->colomns == other.colomns);
    Matrix temp(this->rows, this->colomns);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < colomns; j++){
            temp.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }
    return temp;
}

Matrix Matrix::operator - (const Matrix &other) const{
    assert(this->rows == other.rows && this->colomns == other.colomns);
    Matrix temp(this->rows, this->colomns);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < colomns; j++){
            temp.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
        }
    }
    return temp;
}

Matrix Matrix::operator * (const Matrix &other) const{
    assert(this->colomns == other.rows);
    Matrix temp(this->rows, other.colomns);
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < other.colomns; j++){
            for(int k = 0; k < this->colomns; k++){
                temp.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    return temp;
}

int & Matrix::operator()(int index_i, int index_j){
    assert(index_i >= rows || index_i < 0);
    assert(index_j >= colomns || index_j < 0);
    return matrix[index_i][index_j];
}

//===================*FUNCTION*===============================

int Matrix::det() const{
    assert(rows == colomns);
    int det = 0;
    if(rows == 1) return matrix[0][0];
    for(int j = 1; j <= colomns; j++){
        Matrix temp(*this);
        temp.del(1, j);
        det += pow((-1), (j + 1)) * matrix[0][j-1] * temp.det();
    }
    return det;
}

void Matrix::t(){
    Matrix temp(colomns, rows);
    for(int i = 0; i < temp.rows; i++){
        for(int j = 0; j < temp.colomns; j++){
            temp.matrix[i][j] = matrix[j][i];
        }
    }
    *this = temp;
}
//===================*FILLING*================================

void Matrix::random(int from, int before){
    if(from > before) swap(from, before); 
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < colomns; j++) {
            matrix[i][j] = rand() % (before - from + 1) + from;
        }     
    }
}

void Matrix::input(int number){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < colomns; j++){
            matrix[i][j] = number;
        }
    }
}

void Matrix::input(int i_1, int j_1, int i_2, int j_2){
    i_1--;
    j_1--;
    i_2--;
    j_2--;
    do{
        cin >> matrix[j_1][i_1];
        i_1++;

        if(i_1 == colomns){
            i_1 = 0;
            j_1++;
        }

        if(i_1 == i_2 && j_1 == j_2) cin >> matrix[j_1][i_1];
    } while(i_1 != i_2 || j_1 != j_2);
}

//==================*DELETION*================================

void Matrix::rowdel(int index){
    if(index < 0 || index > rows) return;
    index--;
    rows--;
    for(; index < rows; index++){
        for(int j = 0; j < colomns; j++){
            matrix[index][j] = matrix[index+1][j];
        }
    }
}

void Matrix::colomndel(int index){
    if(index < 0 || index > colomns) return;
    index--;
    colomns--;
    for(; index < colomns; index++){
        for(int i = 0; i < rows; i++){
            matrix[i][index] = matrix[i][index+1];
        }
    }
}

void Matrix::del(int row_index, int colomn_index){
    rowdel(row_index);
    colomndel(colomn_index);
}
//===================*OUTPUT*=================================

void Matrix::print() const{
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < colomns; j++) cout << matrix[i][j] << '\t';
        cout << endl;
    }
}

//==================*DESTRUCTOR*============================

Matrix::~Matrix(){
    for(int i = 0; i < rows; ++i){
        delete[] matrix[i];
    }
    delete[] matrix;
}
