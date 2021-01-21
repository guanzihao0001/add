//
// Created by 关子豪 on 2020/11/4.
//

using namespace  std;
#include "Matrix.h"
#include <vector>
#include <iostream>
#include "math.h"
#include <cassert>

//this is for testing github

//MVector methods
MVector::MVector(int a,double b):coefs(a,b){this->size=a;this->value=b;}

class Bad_Dimensions{};

MVector MVector::operator+(const MVector &MV) {
    if(this->size!=MV.size){
        throw Bad_Dimensions();
    }
    MVector TMV(MV.size,0);
    for(int i=0;i<MV.size;i++){
        TMV.coefs[i]=this->coefs[i]+MV.coefs[i];
    }
    return TMV;
}
MVector MVector::operator-(const MVector &MV) {
    if(this->size!=MV.size){
        throw Bad_Dimensions();
    }
    MVector TMV(MV.size,0);
    for(int i=0;i<MV.size;i++){
        TMV.coefs[i]=this->coefs[i]-MV.coefs[i];
    }
    return TMV;
}

MVector MVector::operator+=(const MVector &MV) {
    if(this->size==MV.size){
        for(int i=0;i<MV.size;i++){
            this->coefs[i]= this->coefs[i]+MV.coefs[i];
        }
    }
    return *this;
}

MVector MVector::operator-=(const MVector &MV) {
    if (this->size == MV.size) {
        for (int i = 0; i < MV.size; i++) {
            this->coefs[i] = this->coefs[i] - MV.coefs[i];
        }
    }
    return *this;
}
double MVector::operator*(const MVector &MV){
    double sum=0;
    for(int i=0;i<MV.size;i++){
        sum+=this->coefs[i]*MV.coefs[i];
    }
    return sum;
}

double MVector::norm() {
    double sqr=0;
    for(int i=0;i<this->size;i++){
        sqr+= this->coefs[i]*this->coefs[i];
    }
    return sqrt(sqr);
}
bool MVector::operator==(const MVector& MV){
    MVector M=*this;
    if(M.coefs.size()==MV.coefs.size()){
        for(int i=0;i<M.coefs.size();i++){
            if(M.coefs[i]!=MV.coefs[i]){
                return false;
            }
            return true;
        }
    }
    return false;
}
istream&operator >>(istream& input, MVector& M){
    input>>M.size>>M.value;
    vector<double> c(M.size,M.value);
    M.coefs=c;
    return input;
}
std::ostream&operator <<(std::ostream& output, const MVector& M){

    output<<'['<<' ';
    if(M.coefs.size()!=0) {
        for (int i = 0; i < M.size;i++) {
            output << M.coefs[i]<<" ";
        }
    }
    output<<']';
    return output;
}

double &MVector::operator[](int i)  {
    return coefs[i];
}
double MVector::operator[](int i) const {
    return coefs[i];
}
//Matrix method
Matrix::Matrix(int r, int s, double v) :coeffs(r,MVector(s,v)){
    this->row=r;
    this->value=MVector(s,v);
}

istream&operator >>(istream& input, Matrix& M){
    input>>M.row>>M.value;
    vector<MVector> c(M.row,M.value);
    M.coeffs=c;
    return input;
}
std::ostream&operator <<(std::ostream& output, const Matrix& M){

    output<<'['<<'\n';
    if(M.coeffs.size()!=0){
        for (int i = 0; i < M.row;i++) {
            output << M.coeffs[i]<<"\n";
        }
    }
    output<<']';
    return output;
}

bool Matrix::operator==(const Matrix &M) {
    if(this->coeffs.size()==M.coeffs.size()){
        for(int i=0;i<M.coeffs.size();i++)
        {
            if(this->coeffs[i].coefs.size()==M.coeffs[i].coefs.size()){
                for(int t=0;t<M.coeffs[i].coefs.size();t++){
                    if(this->coeffs[i].coefs[t]!=M.coeffs[i].coefs[t]){
                        return false;
                    }
                }
        }
        }
        return true;
    }
    return false;
}







Matrix Matrix::operator+=(const Matrix& M){
    if(this->row!=M.row){
        throw Bad_Dimensions();
    }
    for(int i=0;i<M.row;i++){
        this->coeffs[i]+=M.coeffs[i];
    }
    return *this;
}

Matrix Matrix::operator-=(const Matrix &M) {
    if(this->row!=M.row){
        throw Bad_Dimensions();
    }
    for(int i=0;i<M.row;i++){
        this->coeffs[i]-=M.coeffs[i];
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix &M) {
    if(this->row!=M.row){
        throw Bad_Dimensions();
    }
    Matrix resM(M.row,M.value.coefs.size(),0);
    for(int i=0;i<M.row;i++){
        resM.coeffs[i]=this->coeffs[i]-M.coeffs[i];
    }
    return resM;
}

Matrix Matrix::operator+(const Matrix &M) {
    if(this->row!=M.row){
        throw Bad_Dimensions();
    }
    Matrix resM(M.row,M.value.coefs.size(),0);
    for(int i=0;i<M.row;i++){
        resM.coeffs[i]=this->coeffs[i]+M.coeffs[i];
    }
    return resM;
}

Matrix Matrix::operator*=(const Matrix &M) {
    if(this->value.coefs.size()!=M.row){
        throw Bad_Dimensions();
    }
    Matrix resM(this->row,M.coeffs[1].coefs.size(),0);
    for(int i=0;i<this->row;i++){
        for(int j=0;j<M.row;j++){
            resM.coeffs[i].coefs[j]= this->line(i)*M.column(j);
        }
    }
    *this=resM;
    return *this;
}

Matrix Matrix::operator*(const Matrix &M) {
    if(this->value.coefs.size()!=M.row){
        throw Bad_Dimensions();
    }
    Matrix resM(this->row,M.coeffs[1].coefs.size(),0);
    for(int i=0;i<this->row;i++){
        for(int j=0;j<M.value.coefs.size();j++){
            resM.coeffs[i].coefs[j]= this->line(i)*M.column(j);
        }
    }
    return resM;
}



MVector Matrix::line(int i) {
    return this->coeffs[i];
}

MVector Matrix::column(int i) const {
    MVector res(this->row,0);
    for(int j=0;j<this->row;j++){
        res.coefs[j]=this->coeffs[j].coefs[i];
    }
    return res;
}

Matrix Matrix::transpose() {
    Matrix resT=*this;
    Matrix resM(this->value.coefs.size(),this->row,0);
    for(int i=0;i<resM.row;i++){
        for(int j=0;j<this->row;j++){
            resM[i][j]=resT[j][i];
        }
    }
    return resM;
}

MVector &Matrix::operator[](int i) {
    return coeffs[i];
}






Matrix operator~(const Matrix &M) {
    Matrix TM=M;
    return TM.transpose();
}



Matrix& Matrix::operator=(MVector MV) {
    this->row=1;
    this->value=MV;
    return *this;
}

Matrix::Matrix(MVector vector) :coeffs(1,vector){
    row=1;
    value=vector;
}

double Matrix::det() {
    double res=0;
    Matrix M=*this;
    for(int i=0;i<M.row;i++){
        double resP=1;
        double resM=1;
        for(int j=0;j<M.row;j++){
            resP*=M[j][(i+j)%(M.row-1)];
            resM*=M[M.row-j-1][(i+j)%(M.row-1)];
        }
        res=res+resP;
        res=res-resM;
    }
    return res;
}

double &Matrix::operator()(int i, int j) {
    return coeffs[i].coefs[j];

}


