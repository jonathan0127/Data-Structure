//Author : 吳紹彰 B123040048
//Date : Nov.26,2024
/*Purpose :
	比較各個sort的時間
*/
#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include <random>
#include <stdlib.h>
#include<ctime>
#include<iomanip>

using namespace std;

//從檔案讀取資料
void read(vector<int> &f_input) {
	ifstream in; //輸入檔案
	in.open("input.txt");

	int f_n; //資料的數量
	in >> f_n; //讀取資料的數量
	f_input.clear(); //清空f_input
	//讀取資料
	for (int i = 0 ; i < f_n ; i ++) {
		int tmp;
		in >> tmp;
		f_input.push_back(tmp); //將資料放入f_input
	}
	in.close(); //關閉檔案
}

//輸出資料
void output(ofstream &out, vector<int> &f_input, string method) {
	out << method << '\n'; //輸出方法
	//輸出資料
	for (int i : f_input) {
		out << i << '\n'; //輸出資料
	}
	out.close(); //關閉檔案
}

//選擇排序
void selection(vector<int> &vt) {
	int n = vt.size(); //資料的數量
	for (int i = 0 ; i < n - 1 ; i ++) {
		int mn = i; //最小值的位置
		for (int j = i + 1 ; j < n ; j ++) {
			//如果vt[j]比vt[mn]小，則將mn設為j
			if (vt[j] < vt[mn]) {
				mn = j;
			}
		}
		swap(vt[i], vt[mn]); //交換vt[i]和vt[mn]
	}
}

//調整heap
void adjust(vector<int> &vt, int last, int cur) {
	int l = 2 * cur + 1; //左子節點
	int r = 2 * cur + 2;//右子節點

	int large; //最大值的位置
	
	//如果左子節點比cur大，則將large設為l
	if (l <= last && vt[l] > vt[cur]) {
		large = l;
	}
	else {
		large = cur; //否則將large設為cur
	}

	//如果右子節點比large大，則將large設為r
	if (r <= last && vt[r] > vt[large]) {
		large = r;//否則將large設為r
	}

	//如果large不等於cur，則交換vt[cur]和vt[large]
	if (large != cur) {
		swap(vt[cur], vt[large]); //交換vt[cur]和vt[large]
		adjust(vt, last, large); //調整heap
	}
}

//堆積排序
void heap(vector<int> &vt) {
	//建立heap
	for (int i = vt.size() / 2 - 1 ; i >= 0 ; i --) { //i為heap的父節點
		adjust(vt, vt.size() - 1, i); //調整heap
	}

	//排序
	for (int i = vt.size() - 1 ; i > 0 ; i --) {
		swap(vt[0], vt[i]); //交換vt[0]和vt[i]
		adjust(vt, i - 1, 0); //調整heap
	}

}

//快速排序
void Quick(vector<int> &vt, int l, int r) {
	//如果l大於等於r，則回傳
	if(l >= r){
		return;
	}

	int i = l; //i為左邊的位置
	int j = r;//j為右邊的位置
	int pivot = vt[(l + r) / 2]; //pivot為中間的值
	//分割
	while(i <= j){
		//找到左邊比pivot大的值
		while(vt[i] < pivot){
			i ++;
		}
		//找到右邊比pivot小的值
		while (vt[j] > pivot){
			j --;
		}
		//如果i小於等於j，則交換vt[i]和vt[j]
		if(i <= j) {
			swap(vt[i], vt[j]);
			i ++;
			j --;
		}
	}

	Quick(vt, l, j); //快速排序左邊
	Quick(vt, i, r); //快速排序右邊
}

//隨機產生資料
void random(int n, vector<int> &vt) {
	vt.clear(); //清空vt
	srand(time(NULL));
	for (int i = 0 ; i < n ; i ++) {
		vt.push_back(rand() % 5000000); //產生隨機數
	}
}

//比較各個sort的時間
void randomsort(int size) { //size為資料的數量
	vector<int> r_input[10]; //隨機產生的資料
	//產生隨機資料
	for(int i = 0 ; i < 10 ; i ++){
		random(size, r_input[i]); //產生隨機資料
	}


	double start, end, time; //時間
	time = 0; 
	cout << "\ndata size : " << size << '\n'; //輸出資料的數量
	//比較各個sort的時間
	cout << "Selection sort......"; //選擇排序
	for(int i = 0 ; i < 10 ; i ++){//比較10次取平均
		start = clock(); //開始時間
		selection(r_input[i]);//選擇排序
		end = clock(); //結束時間
		time += (end - start) / CLOCKS_PER_SEC; //計算時間
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n"; //輸出時間

	time = 0;
	cout << "Heap sort......";//堆積排序
	for(int i = 0 ; i < 10 ; i ++){
		start = clock();
		heap(r_input[i]); //堆積排序
		end = clock();
		time += (end - start) / CLOCKS_PER_SEC;
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n";

	time = 0;
	cout << "Quick sort......"; //快速排序
	for(int i = 0 ; i < 10 ; i ++){
		start = clock();
		Quick(r_input[i], 0, r_input[i].size() - 1); //快速排序
		end = clock();
		time += (end - start) / CLOCKS_PER_SEC;
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n";

	time = 0;
	cout << "C library sort......"; //C library排序
	for(int i = 0 ; i < 10 ; i ++){
		start = clock();
		qsort(&r_input[i][0], r_input[i].size(), sizeof(int), [](const void *a, const void *b) -> int {
			return *(int *)a - *(int *)b;
		}); //C library排序
		end = clock();
		time += (end - start) / CLOCKS_PER_SEC;
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n";

	time = 0;
	cout << "Cpp library sort......"; //Cpp library排序
	for(int i = 0 ; i < 10 ; i ++){
		start = clock();
		sort(r_input[i].begin(), r_input[i].end()); //Cpp library排序
		end = clock();
		time += (end - start) / CLOCKS_PER_SEC;
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n";
}

signed main() {
	int op;

	ofstream outa, outb, outc, outd, oute; //輸出檔案
	vector<int> f_input;//資料
	//開啟檔案
	outa.open("outputA.txt");
	outb.open("outputB.txt");
	outc.open("outputC.txt");
	outd.open("outputD.txt");
	oute.open("outputE.txt");

	cout << "1. sort the input.txt\n2. sort the random data\n"; //選擇
	cin >> op;
	//選擇1，則進行sort the input.txt
	if (op == 1) {

		read(f_input);//讀取資料
		cout << "Selection sort......";
		selection(f_input); //選擇排序
		output(outa, f_input, "Selection Sort"); //輸出資料
		cout << "Finish!\n";

		read(f_input);//讀取資料
		cout << "Heap sort......";
		heap(f_input); //堆積排序
		output(outb, f_input, "Heap Sort"); //輸出資料
		cout << "Finish!\n";

		read(f_input);//讀取資料
		cout << "Quick sort......";
		Quick(f_input, 0, f_input.size() - 1); //快速排序
		output(outc, f_input, "Quick Sort");//輸出資料
		cout << "Finish!\n";

		read(f_input);
		cout << "C library sort......"; //C library排序
		qsort(&f_input[0], f_input.size(), sizeof(int), [](const void *a, const void *b) -> int {
			return *(int *)a - *(int *)b;
		});//C library排序
		output(outd, f_input, "C library Sort"); //輸出資料
		cout << "Finish!\n";

		read(f_input);
		cout << "Cpp library sort......"; //Cpp library排序
		sort(f_input.begin(), f_input.end());
		output(oute, f_input, "Cpp library Sort"); //輸出資料
		cout << "Finish!\n";
	}
	//如果選擇2，則進行sort the random data
	else if (op == 2) {
		//比較各個sort的時間
		randomsort(100); 
		randomsort(500);
		randomsort(1000);
		randomsort(5000);
		randomsort(10000);
		randomsort(50000);


		


	}


}
