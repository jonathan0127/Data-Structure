//Author : 吳紹彰 B123040048
//Date : Oct.4,2024
/*Purpose : 
	利用recursion檢查騎士能不能走完棋盤
*/
#include<iostream>
using namespace std;

bool flag;//flag為是否有解

int K[9][2] = {{0, 0}, { -2, 1}, { -1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, { -1, -2}, { -2, -1}}; //K為騎士的移動方式
int ans[7][7]; //ans為存放騎士的位置

//檢查是否有空格
bool chk(int t) {
	//將所有的位置檢查一遍，如果有空格，則回傳1，否則回傳0
	for (int i = 1 ; i <= t ; i ++) {
		for (int j = 1 ; j <= t ; j ++) {
			if (ans[i][j] == 0)
				return 0;
		}
	}
	return 1;
}
//遞迴檢查騎士能不能走完棋盤
void dfs(int t, int i, int j, int dir, int cnt){ //t為棋盤的大小，i, j為騎士的位置，dir為騎士的方向，cnt為騎士的順序
    //如果已經找到解，則不繼續
    if(flag == 0) return;

    //如果找到解，則輸出解
    if(chk(t)){
        //輸出解
        for (int i = 1 ; i <= t ; i ++) {
			for (int j = 1 ; j <= t ; j ++) {
				cout << ans[i][j] << ' ';
			}
			cout << '\n';
		}
        cout << '\n';
        //設定flag為0
        flag = 0;
        return;
    }
    //檢查騎士的移動
    for(int x = dir ; x <= 8 ; x++){
        //如果騎士不能走，則continue
        if (i + K[x][0] < 1 || i + K[x][0] > t || j + K[x][1] < 1 || j + K[x][1] > t || ans[i + K[x][0]][j + K[x][1]] != 0) {
            continue;
        }
        else{
            ans[i + K[x][0]][j + K[x][1]] = cnt; //設定騎士的位置
            dfs(t, i + K[x][0], j + K[x][1], 1, cnt+1); //遞迴繼續檢查下一個位置
        }

    }
    ans[i][j] = 0; //將騎士回歸原來的位置
}

signed main() {
	//輸出1到6的棋盤
	for (int t = 1 ; t <= 6 ; t ++) {
		//初始化棋盤
		for (int i = 0 ; i < 7 ; i ++) {
			for (int j = 0 ; j < 7 ; j ++) {
				ans[i][j] = 0;
			}
		}
        flag = 1; //設定flag為1
        ans[1][1] = 1; //預設第一個騎士在(1, 1)
        dfs(t, 1, 1, 1, 2); //遞迴檢查騎士能不能走完棋盤
        //如果沒有解，則輸出no solution
		if(flag){
            cout << "no solution\n\n";
        }
	}
}