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

}



signed main() {
	int op;

	ofstream outa, outb, outc, outd, oute;
	vector<int> f_input;
	outa.open("outputA.txt");
	outb.open("outputB.txt");
	outc.open("outputC.txt");

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

	}
	else if (op == 2) {

	}


}
