//Author : 吳紹彰 B123040048
//Date : Sept.16,2024
/*Purpose : 
    印出1到N之間所有整數階乘 
*/
#include<iostream>
using namespace std;
signed main(){
    int n; //n代表階乘的數字
    while(cin >> n){
        if(n == 0) break; //如果n為0，則結束程式

        int num[100] = {0};//用此陣列存放數字
        num[0] = 1;//初始化為1
        //計算階乘
        for(int i = 1 ; i <= n ; i ++){ 
            for(auto &j : num){ //對於num中的每一個數字乘以i
                j *= i;
            }
            int carry = 0; //進位儲存
            for(auto &j : num){ //進位
                int tmp = j + carry; //用tmp儲存進位後的數字
                carry = tmp / 10; //進位
                j = tmp % 10; //取個位數
            }
            //輸出結果
            cout << i << "!=";
            bool flag = 0; //flag用來判斷是否為前面數字0
            for(int j = 99 ; j >= 0 ; j--){ //從後面開始輸出
                if(num[j] != 0 || flag == 1){ //如果不是前面的0
                    flag = 1; //設定flag為1
                    cout << num[j]; //輸出
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }
}