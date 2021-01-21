//
// Created by 关子豪 on 2020/11/4.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H


#include <vector>
//MVector class
class MVector {
protected:
    int size;
    double value;


public:
    std::vector<double> coefs;
    bool  operator==(const MVector& MV);
     MVector operator+(const MVector& MV);
     MVector operator+=(const MVector& MV);
     MVector operator-=(const MVector& MV);
     MVector operator-(const MVector& MV);
    double operator*(const MVector& MV);
    double &operator[](int i);
    double operator[](int i)const;
    double norm();
    MVector(int a=0, double b=0);
    class Bad_Dimensions{};
    class out_of_bound;
    friend std::istream&operator >>(std::istream& input,MVector& M);
    friend std::ostream&operator <<(std::ostream& output, const MVector& M);
};
//Matrix class
class Matrix : public MVector {
    int  row;
    MVector value;
public:
    Matrix friend operator~(const Matrix &M);
    std::vector<MVector> coeffs;
    class Bad_Dimensions{};
    Matrix(int r=0,int s=0,double v=0);
    friend istream&operator >>(istream& input, Matrix& M);
    friend std::ostream&operator <<(std::ostream& output, const Matrix& M);
    bool  operator==(const Matrix& M);
     Matrix operator+=(const Matrix& M);
     Matrix operator-=(const Matrix& M);
     Matrix operator+(const Matrix& M);
     Matrix operator-(const Matrix& M);
    Matrix operator*=(const Matrix& M);
    Matrix operator*(const Matrix& M);
    MVector line(int i);
    MVector column(int i) const;
    Matrix transpose();
    MVector &operator[](int i);
    double &operator()(int i,int j);
    Matrix& operator=(MVector MV);
    Matrix(MVector vector);

    double det();
};

#endif //MATRIX_MATRIX_H
