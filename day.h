#include<ctime>
#include<iostream>
using namespace std;
#ifndef PBL23_DAY_H
#define PBL23_DAY_H
class Date{
private:
    int ngay,thang,nam;
    time_t noww = time(0);
    tm *tt= localtime(&noww);
public:
    friend ostream& operator << (ostream& out, Date a);
    friend istream& operator >> (istream& in, Date& a);
    int checknhuan();
    int checkngay();
    int checkthang();
    int checknam();
    int check();
    void NGAY(int x) {
        ngay=x;
    }
    void THANG(int x) {
        thang = x;
    }
    void NAM(int x){
        nam=x;
    }
    friend int diff(Date date1,Date date2);
};

ostream& operator << (ostream& out, Date a){
    out << a.ngay <<"/" << a.thang << "/" <<a.nam <<endl;
    return out;
}
int Date::checknhuan(){
    if ((nam % 4==0 && nam %100 !=0)|| nam % 400==0) return 1;
    return 0;
}
int Date::checkngay() {
    if (ngay<tt->tm_mday && thang==tt->tm_mon+1 && nam ==tt->tm_year+1900) return 0;
    if ((ngay>0 && ngay <= 31) && (thang == 1||thang == 3 || thang == 5 || thang == 7 || thang == 8 || thang == 10 || thang == 12))  return 1;
    if ((ngay>0 && ngay < 31) && (thang == 4||thang == 6 || thang == 9 || thang == 11 ))    return 1;
    if (thang==2) {
        if (checknhuan()==1 && ngay>0 && ngay <30) return 1;
        if (checknhuan()==0 && ngay>0 && ngay <29) return 1;
    }
    return 0;
}
int Date::checkthang() {
    if (thang<tt->tm_mon+1 && nam ==tt->tm_year+1900 ) return 0;
    if (thang > 0 && thang < 13) return 1;
    return 0;
}
int Date::checknam() {
    if(nam<tt->tm_year+1900) return 0;
    if (nam > 0 ) return 1;
    return 0;
}
int Date::check(){
    if(checkngay()==1 && checkthang()==1 && checknam()==1 ) return 1;
    return 0;
}
istream& operator >> (istream& in, Date& a){
    int t=0;
    do {
        cout << "nhap ngay "; in >> a.ngay;
        cout << "nhap thang "; in >> a.thang;
        cout << "nhap nam "; in >> a.nam;
        t=a.check();
        if (t==0)
            cout << "Nhap sai nhap lai nao ! " << endl;
    }  while (t==0);

    return in;
}
int diff(Date date1, Date date2) {
    int daysDiff = 0;
    int day[13]={31,28,31,30,31,30,31,31,30,31,30,31};
    int t=0,m=0;
    for(int i=1;i<date1.thang;i++){
        t+=day[i-1];
        if (i==2 && date1.checknhuan()) t++;
    }
    t+=date1.ngay;
    for(int i=1;i<date2.thang;i++){
        m+=day[i-1];
        if (i==2 && date2.checknhuan()) m++;
    }
    m+=date2.ngay;
    if(date1.nam==date2.nam) daysDiff=m-t;
    else{
        for(int i=date1.nam+1;i<date2.nam+1;i++){
            if ((i % 4==0 && i %100 !=0)|| i % 400==0) daysDiff+=366;
            else daysDiff+=365;
        }
        if (date1.checknhuan()) t=366-t;
        else t=365-t;
        daysDiff+=t+m;
    }
    return daysDiff;
}

#endif
