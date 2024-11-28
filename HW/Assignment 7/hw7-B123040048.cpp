//Author : 吳紹彰 B123040048
//Date : Nov.26,2024
/*Purpose :
	利用binary search tree，找出所有出現次數為奇數之數字
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

void read(vector<int> &f_input) {
	ifstream in;
	in.open("input.txt");
	int f_n;
	in >> f_n;
	f_input.clear();
	for (int i = 0 ; i < f_n ; i ++) {
		int tmp;
		in >> tmp;
		f_input.push_back(tmp);
	}
	in.close();
}

void output(ofstream &out, vector<int> &f_input, string method) {
	out << method << '\n';
	for (int i : f_input) {
		out << i << '\n';
	}
	out.close();
}

void selection(vector<int> &vt) {
	int n = vt.size();
	for (int i = 0 ; i < n - 1 ; i ++) {
		int mn = i;
		for (int j = i + 1 ; j < n ; j ++) {
			if (vt[j] < vt[mn]) {
				mn = j;
			}
		}
		swap(vt[i], vt[mn]);
	}
}

void adjust(vector<int> &vt, int last, int cur) {
	int l = 2 * cur + 1;
	int r = 2 * cur + 2;

	int large;

	if (l <= last && vt[l] > vt[cur]) {
		large = l;
	}
	else {
		large = cur;
	}

	if (r <= last && vt[r] > vt[large]) {
		large = r;
	}

	if (large != cur) {
		swap(vt[cur], vt[large]);
		adjust(vt, last, large);
	}
}


void heap(vector<int> &vt) {
	for (int i = vt.size() / 2 - 1 ; i >= 0 ; i --) {
		adjust(vt, vt.size() - 1, i);
	}

	for (int i = vt.size() - 1 ; i > 0 ; i --) {
		swap(vt[0], vt[i]);
		adjust(vt, i - 1, 0);
	}

}


void Quick(vector<int> &vt, int l, int r) {
	if(l >= r){
		return;
	}

	int i = l;
	int j = r;
	int pivot = vt[(l + r) / 2];

	while(i <= j){
		while(vt[i] < pivot){
			i ++;
		}
		while (vt[j] > pivot){
			j --;
		}
		if(i <= j) {
			swap(vt[i], vt[j]);
			i ++;
			j --;
		}
	}

	Quick(vt, l, j);
	Quick(vt, i, r);
}

void random(int n, vector<int> &vt) {
	vt.clear();
	srand(time(NULL));
	for (int i = 0 ; i < n ; i ++) {
		vt.push_back(rand() % 5000000);
	}
}

void randomsort(vector<int> &vt, int size) {
	vector<int> r_input[10];
	for(int i = 0 ; i < 10 ; i ++){
		random(size, r_input[i]);
	}
	double start, end, time;
	time = 0;
	cout << "\ndata size : " << size << '\n';
	cout << "Selection sort......";
	for(int i = 0 ; i < 10 ; i ++){
		start = clock();
		selection(r_input[i]);
		end = clock();
		time += (end - start) / CLOCKS_PER_SEC;
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n";

	time = 0;
	cout << "Heap sort......";
	for(int i = 0 ; i < 10 ; i ++){
		start = clock();
		heap(r_input[i]);
		end = clock();
		time += (end - start) / CLOCKS_PER_SEC;
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n";

	time = 0;
	cout << "Quick sort......";
	for(int i = 0 ; i < 10 ; i ++){
		start = clock();
		Quick(r_input[i], 0, r_input[i].size() - 1);
		end = clock();
		time += (end - start) / CLOCKS_PER_SEC;
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n";

	time = 0;
	cout << "C library sort......";
	for(int i = 0 ; i < 10 ; i ++){
		start = clock();
		qsort(&r_input[i][0], r_input[i].size(), sizeof(int), [](const void *a, const void *b) -> int {
			return *(int *)a - *(int *)b;
		});
		end = clock();
		time += (end - start) / CLOCKS_PER_SEC;
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n";

	time = 0;
	cout << "Cpp library sort......";
	for(int i = 0 ; i < 10 ; i ++){
		start = clock();
		sort(r_input[i].begin(), r_input[i].end());
		end = clock();
		time += (end - start) / CLOCKS_PER_SEC;
	}
	cout << "Finish!\n";
	cout << "\tTime : " << fixed << setprecision(7) << time / 10 << "s\n";
}

signed main() {
	int op;

	ofstream outa, outb, outc, outd, oute;
	vector<int> f_input;
	outa.open("outputA.txt");
	outb.open("outputB.txt");
	outc.open("outputC.txt");
	outd.open("outputD.txt");
	oute.open("outputE.txt");

	cout << "1. sort the input.txt\n2. sort the random data\n";
	cin >> op;
	if (op == 1) {

		read(f_input);
		cout << "Selection sort......";
		selection(f_input);
		output(outa, f_input, "Selection Sort");
		cout << "Finish!\n";

		read(f_input);
		cout << "Heap sort......";
		heap(f_input);
		output(outb, f_input, "Heap Sort");
		cout << "Finish!\n";

		read(f_input);
		cout << "Quick sort......";
		Quick(f_input, 0, f_input.size() - 1);
		output(outc, f_input, "Quick Sort");
		cout << "Finish!\n";

		read(f_input);
		cout << "C library sort......";
		qsort(&f_input[0], f_input.size(), sizeof(int), [](const void *a, const void *b) -> int {
			return *(int *)a - *(int *)b;
		});
		output(outd, f_input, "C library Sort");
		cout << "Finish!\n";

		read(f_input);
		cout << "Cpp library sort......";
		sort(f_input.begin(), f_input.end());
		output(oute, f_input, "Cpp library Sort");
		cout << "Finish!\n";
	}
	else if (op == 2) {
		randomsort(f_input, 100);
		randomsort(f_input, 500);
		randomsort(f_input, 1000);
		randomsort(f_input, 5000);
		randomsort(f_input, 10000);
		randomsort(f_input, 50000);


		


	}


}
