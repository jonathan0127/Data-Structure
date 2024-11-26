#include<bits/stdc++.h>
using namespace std;
const int INT = 2147483647;
int main(){
    srand(time(0));
    ofstream file;
    file.open("input.txt");
    for(int i=0;i<250;i++){
        file<<rand()%INT<<endl;
    }
    file.close();
}