#pragma once
#ifndef MATRIX_H
#define MATRIX_H
class Matrix {
   private:
    int rows;
    int colomns;
    int **matrix;

   public:
    //================*CONSTRUCTOR*===============

    Matrix(int rows, int colomns);
    Matrix(const Matrix &other);

    //=============*OPERATORS*====================

    Matrix &operator=(const Matrix &other);
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    int &operator()(int index_i, int index_j);

    //================*FUNCTION*======================

    int getrows() const { return rows; };
    int getcolomns() const { return colomns; };
    int det() const;
    void t();

    //===============*FILLING*====================

    void random(int from, int before);
    void input(int number);
    void input(int i_1, int j_1, int i_2, int j_2);

    //===============*DELETION*====================

    void rowdel(int index);
    void colomndel(int index);
    void del(int row_index, int colomn_index);

    //================*OUTPUT*=====================

    void print() const;

    //===============*DESTRUCTOR*=================

    ~Matrix();
};
#endif
