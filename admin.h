//
// Created by DELL on 9/22/2023.
//
#include<ctime>
#include<fstream>
#include "day.h"
#include "phongmay.h"
using namespace std;
#ifndef PBL23_ADMIN_H
#define PBL23_ADMIN_H
class admin {
private:
    vector <phongmay> cpt;
    string name,NameTT,NameT,NameID;
    int hourr,mini;
public:
    admin(const string ,const string , const string );
    void add(const string ,const string , const string);
    void show ();
    void dk(int,int ,int,int);
    void lk();
    void tk(const string);
    void outfile();
    void Hour(int x);
    void Min(int x);
    int Get_hour();
    int Get_min();
    void Name(string);
    string Get_name();
    string Get_NameTime();
    string Get_NameID();
    string Get_NameTT();
    int Check(int,int,int);
    int Get_size();
};
admin::admin(const string s1,const string s2, const string s3) {
    ifstream file(s1);
    ifstream fileTT(s2);
    ifstream fileT(s3);
    NameID=s1;
    NameTT=s2;
    NameT=s3;
    time_t now = time(0);
    tm *t = localtime(&now);
    // cout << t->tm_mday << " " << t->tm_mon+1 << "  " << t->tm_year+1900<<endl;
    Date ttt,z;
    z.NGAY(t->tm_mday);
    z.THANG(t->tm_mon+1);
    z.NAM(t->tm_year+1900);
    int k;
    fileTT >> k;
    ttt.NGAY(k);
    fileTT >> k;
    ttt.THANG(k);
    fileTT >> k;
    ttt.NAM(k);
    long long n= diff(ttt,z);
    long long m;
    while (file >> m) {
        phongmay x;
        x.ID(m);
        cpt.push_back(x);
    }
    int y;
    fileT >> y;
    Hour(y);
    fileT >> y;
    Min(y);
    for(int i=0;i<cpt.size();i++){
        int y;
        fileT >> y;
        cpt[i].T(y);
    }
    int h=0;
    if (n>0) {
        h++;
        int hour[10]={7,8,9,10,11,13,14,15,16,17};
        int sec[10]={50,50,50,50,50,20,20,20,20,20};
        int v=0;
        while ( ( Get_hour() > hour[v] || (Get_hour()==hour[v] && Get_min()>sec[v]))&& v<10) {
            v++;
        }
        Hour(0);
        Min(0);
        for (int i = 0; i < cpt.size(); i++)
            for (int j = v; j < 10; j++) {
                if (cpt[i].Gettt(0,j) == 1) cpt[i].inc();
            }
    }
    for(int i=0;i<cpt.size();i++){
        for (int j = h; j < 365; j++) {
            for (int t = 0; t < 10; t++) {
                int k;
                fileTT >> k;
                if (j<n){
                    if (k==1) cpt[i].inc();
                }
                else cpt[i].TT(j-n,t, k);
            }
        }
    }
    file.close();
    fileTT.close();
    fileT.close();
}
//void admin::add(const string s1 ,const string s2 , const string s3){
//    phongmay x;
//    long long k;
//    cout << "nhap id cua may moi ";
//    cin >> k;
//    x.ID(k);
//    cpt.push_back(x);
//    ofstream file(s1, ios::app);
//    file << k << endl;
//    file.close();
//    ofstream fileT(s3, ios::app);
//    fileT << 0 << endl;
//    fileT.close();
//    ofstream fileTT(s2, ios::app);
//    for (int j = 0; j < 10; j++) {
//        for (int t = 0; t < 10; t++)
//            fileTT << 0 << " ";
//        fileTT << endl;
//    }
//    fileTT.close();

//}
long long dif(){
    time_t now = time(0);
    tm *t = localtime(&now);
    cout << t->tm_mday << " " << t->tm_mon+1 << "  " << t->tm_year+1900<<endl;
    Date ttt,z;
    z.NGAY(t->tm_mday);
    z.THANG(t->tm_mon+1);
    z.NAM(t->tm_year+1900);
    cin >>ttt;
    cout << ttt;
    return diff(z,ttt);
}
//void admin::show() {
//    for (int i = 0; i < cpt.size(); i++) {
//        cout << cpt[i].GetId() << endl;
//    }
//    //cout <<cpt.size();
//    for (int i=0;i<cpt.size();i++) {
//        for (int j = 0; j < 10; j++) {
//            for (int t = 0; t < 10; t++) {
//                int k = cpt[i].Gettt(j, t);
//                cout << k << " ";
//            }
//            cout << endl;
//        }
//        cout << endl;
//    }
//}
void admin::dk(int k,int n,int t,int h){
    int m=0;
    for(int i=0;i< cpt.size();i++) {
        for (int j = n; j <=t; j++)
            if (cpt[i].Gettt(k,j)==0){
                m++;
                    cpt[i].TT(k,j, 1);
                if (m==h*(t-n+1)) {
                    outfile();
                    return;
                }

            }
    }

    cout << endl;
}
//void admin::lk() {
//    long long k=dif();
//    long long l;
//    cout << "nhap tiet muon xem ";
//    cin >> l;
//    for(int i=0;i<cpt.size();i++){
//        int m=cpt[i].Gettt(l-1,k);
//        cout <<  m <<" ";
//    }
//    cout << endl;
//}
//void admin::tk(const string s3) {
//    time_t now = time(0);
//    tm *t = localtime(&now);
//    int hour[10]={7,8,9,10,11,13,14,15,16,17};
//    int sec[10]={50,50,50,50,50,20,20,20,20,20};
//    int k=0;
//    while ( ( Get_hour() > hour[k] || (Get_hour()==hour[k] && Get_min()>sec[k]))&& k<10) {
//        k++;
//    }
//    Hour(t->tm_hour);
//    Min(t->tm_min);
//    for(int i=0;i<cpt.size();i++)
//        for(int j=k;j<10;j++){
//            if (cpt[i].Gettt(j,0)==1)
//                if(t->tm_hour > hour[j] || (t->tm_hour==hour[j] && t->tm_sec>sec[j])) cpt[i].inc();
//        }
//    cout << " nhap lua chon " << endl;
//    cout << "1.Mot may" << endl << "2.Tat ca cac may" << endl;
//    int m;
//    cin >>m;
//    if (m==1){
//        cout << " Chon may \n";
//        int k;
//        cin >> k;
//        cout << cpt[k-1].Get_time() << endl;

//    }
//    else
//    {
//        cout << "   ID" << "   Time_used " <<endl;
//        for(int i=0;i<cpt.size();i++){
//            cout << setw(5)<< cpt[i].GetId()<< setw(9) << cpt[i].Get_time() << endl;
//        }
//    }
//    ofstream fileT(s3);
//    fileT <<Get_hour() << " " << Get_min() << endl;
//    for (int i=0;i<cpt.size();i++){
//        fileT << cpt[i].Get_time()<< endl;
//    }
//    fileT.close();
//}

void admin::outfile(){
    ofstream file(Get_NameID());
    for (int i=0;i<cpt.size();i++){
        file << cpt[i].GetId() << endl;
    }
    file.close();

    ofstream fileTT(Get_NameTT());
    time_t now = time(0);
    tm *t = localtime(&now);
    fileTT << t->tm_mday << " " << t->tm_mon+1 << " " << t->tm_year+1900<<endl;
    for (int i=0;i<cpt.size();i++) {
        for (int j = 0; j < 365; j++) {
            for (int t = 0; t < 10; t++) {
                fileTT << cpt[i].Gettt(j, t) << " ";
            }
            fileTT << endl;
        }
    }
    fileTT.close();


    ofstream fileT(Get_NameTime());
    fileT <<Get_hour() << " " << Get_min() << endl;
    for (int i=0;i<cpt.size();i++){
        fileT << cpt[i].Get_time()<< endl;
    }
    fileT.close();
}
void admin::Hour(int x){
    hourr=x;
}
void admin::Min(int x) {
    mini=x;
}
int admin::Get_hour(){
    return hourr;
}
int admin::Get_min(){
    return mini;
}
void admin::Name(string s){
    name=s;
}
string admin::Get_name() {
    return name;
}
int admin::Check(int k, int n, int t) {
    int m=0;
    for(int i=0;i< cpt.size();i++)
    {
        int l=0;
        for(int j=n;j<=t;j++)
        if (cpt[i].Gettt(k,j)==0) l++;
        if (l==t-n+1) m++;
    }
    return m;
}
int admin::Get_size() {
    return cpt.size();
}
string admin::Get_NameID() {
    return NameID;
}
string admin::Get_NameTT() {
    return NameTT;
}
string admin::Get_NameTime() {
    return NameT;
}
#endif //PBL23_ADMIN_H
