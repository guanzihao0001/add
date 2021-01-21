//
// Created by 关子豪 on 2020/10/14.
//
#include <vector>
#include <vector>
#ifndef MVECTOR_MVECTOR_H
#define MVECTOR_MVECTOR_H
class MVector {

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
#endif //MVECTOR_MVECTOR_H
