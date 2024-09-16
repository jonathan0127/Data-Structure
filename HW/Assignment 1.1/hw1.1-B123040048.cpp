//Author : 吳紹彰 B123040048
//Date : Sept.16,2024
/*Purpose : 
    輸出1, 3, 5, 7, 9階魔方陣
*/

#include <iostream>
#include <iomanip>
using namespace std;
int matrix[9][9]; //用此二維陣列存放魔方陣

//印出n階魔方陣
void solve(int n){ //n代表魔方陣的階數
    //將陣列初始化為0
    for(int i = 0 ; i < 9 ; i ++){
        for(int j = 0 ; j < 9 ; j ++){
            matrix[i][j] = 0;
        }
    }


    int r = 0, c = n / 2; //r,c分別代表行與列，初始化為第一行的中間
    int cur = 1; //cur代表目前的數字
    //填入數字
    while(cur <= n * n){ //當數字還沒填完時
        //如果（r-1, c-1）已經有數字，則往(r+1, c)填
        while(matrix[r][c] != 0){ //如果已經有數字
            //往下移兩格，右移一格，直到找到空格
            r += 2;
            c++;
            //如果超出邊界，則循環
            if(r >= n){ //如果r超出邊界
                r -= n; //循環
            }
            if(c >= n){ //如果c超出邊界
                c -= n; //循環
            }
        }
        matrix[r][c] = cur; //填入數字
        cur ++; //數字加一
        //往左上移一格
        r--; 
        c--; 
        //如果超出邊界，則循環
        if(r < 0){ //如果r超出邊界
            r += n; //循環
        }
        if(c < 0){ //如果c超出邊界
            c += n; //循環
        }
    }
    //輸出結果
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            cout << setw(3) << matrix[i][j]; //設定寬度為3並輸出
        }
        cout << "\n";
    }
    cout << '\n';

}



signed main(){
    //分別解決1,3,5,7,9的魔方陣
    solve(1); //1*1的魔方陣
    solve(3); //3*3的魔方陣
    solve(5); //5*5的魔方陣
    solve(7); //7*7的魔方陣
    solve(9); //9*9的魔方陣
}