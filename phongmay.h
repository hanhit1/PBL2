//
// Created by DELL on 9/22/2023.
//
#include <iostream>
using namespace std;
#ifndef PBL23_PHONGMAY_H
#define PBL23_PHONGMAY_H
class phongmay{
private:
    long long int id;
    int** tt = new int*[365];;
    long long time_used;
public:
    phongmay();
    ~phongmay();
    phongmay(const phongmay& x);
    void inc(){
        time_used++;
    }
    long long Get_time();
    void ID(long long);
    long long GetId(){
        return id;
    }
    int Gettt(int i,int j){
        return tt[i][j];
    }
    void TT(int , int ,int);
    void T(long long x ){
        time_used=x;
    }
};
phongmay::phongmay(const phongmay& x){
    for (int i = 0; i < 365; i++) {
        this->tt[i] = new int[10];
    }
    this->id=x.id;
    this->time_used=x.time_used;
    for(int i=0;i<365;i++)
        for(int j=0;j<10;j++)
            this->tt[i][j]=x.tt[i][j];
}
phongmay::phongmay(){

    time_used=0;
    for (int i = 0; i < 365; i++) {
        tt[i] = new int[10]();
    }
}
phongmay::~phongmay(){
    for(int i = 0; i < 365; i++) {
        delete[] tt[i];
    }
    delete[] tt;
}
void phongmay::ID(long long x){
    id=x;
}
void phongmay::TT(int i, int j,int x){
    tt[i][j]=x;
}
long long phongmay::Get_time(){
    return time_used;
}
#endif //PBL23_PHONGMAY_H
