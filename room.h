#include <bits/stdc++.h>
#include "admin.h"
using namespace std;

#ifndef PBL23_ROOM_H
#define PBL23_ROOM_H
class room {
private:
    admin R[10]={admin("E:/Test/ID1.TXT","E:/Test/TT1.txt","E:/Test/Time1.txt"),admin("E:/Test/ID2.TXT","E:/Test/TT2.txt","E:/Test/Time2.txt"),admin("E:/Test/ID3.TXT","E:/Test/TT3.txt","E:/Test/Time3.txt"),admin("E:/Test/ID4.TXT","E:/Test/TT4.txt","E:/Test/Time4.txt"),admin("E:/Test/ID5.TXT","E:/Test/TT5.txt","E:/Test/Time5.txt"),admin("E:/Test/ID6.TXT","E:/Test/TT6.txt","E:/Test/Time6.txt"),admin("E:/Test/ID7.TXT","E:/Test/TT7.txt","E:/Test/Time7.txt"),admin("E:/Test/ID8.TXT","E:/Test/TT8.txt","E:/Test/Time8.txt"),admin("E:/Test/ID9.TXT","E:/Test/TT9.txt","E:/Test/Time9.txt"),admin("E:/Test/ID10.TXT","E:/Test/TT10.txt","E:/Test/Time10.txt")};
    int check[10]={1};
    int Av[10]={0};
public:
    room();
    void check_room(int,int,int,int);
    void thongke();
    void themmay();
    int Get_check(int i){
        return check[i];
    }
    void CHECK(int i,int x){
        check[i]=x;
    }
    int AV(int i){
        return Av[i];
    }
    void dangky(int,int,int,int,int);
    bool check_t(int,int);
    int Size(int );
};
room::room() {
    R[0].Name("C101");
    R[1].Name("C102");
}
void room::check_room(int m,int k,int n,int h) {
    for(int i=0;i<10;i++) CHECK(i,1);
    for(int i=0;i<10;i++)
    {
        Av[i]=R[i].Check(m,k,n);
                if (Av[i]==R[i].Get_size() && R[i].Get_size()>=h) {
                    CHECK(i,0);
                }
                else
                    if (Av[i]>=h)
                    CHECK(i,2);
                else
            CHECK(i,1);
    }
}
void room::themmay() {

}
void room::thongke() {

}
void room::dangky(int k, int n, int t, int i,int h){
    R[i].dk(k,n,t,h);
}
int room::Size(int i){
    return R[i].Get_size();
}
bool room::check_t(int m,int k){
            int v=0;
            if (m==0){
                time_t now = time(0);
                tm *t = localtime(&now);
                int Ehour[10]={7,8,9,10,11,13,14,15,16,17};
                int Esec[10]={50,50,50,50,50,20,20,20,20,20};
                int Shour[10]={7,8,9,10,11,12,13,14, 15,16};
                int Ssec[10]={0,0,0,0,0,30,30,30,30,30};
                while ( ( t->tm_hour > Ehour[v] || (t->tm_hour==Ehour[v] && t->tm_min >=Esec[v]))&& v<10) {
                    v++;
                }
                int ref;
                if (v>9) {

                    return false;
                }
                else
                    if (t->tm_hour<Shour[v] || (t->tm_hour==Shour[v] && t->tm_sec<=Ssec[v])) {
                        ref=1;

                    }
                    else {ref=0;

                    }
                if((ref==1 && k-1<v)||(ref==0 && k-1<=v))
                        return false;
                else
                            return true;
            } else return true;
}
#endif //PBL23_ROOM_H
