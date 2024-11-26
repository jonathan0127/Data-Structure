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





signed main() {
	int op;

	ofstream outa, outb, outc, outd, oute;
	vector<int> f_input;
	outa.open("outputA.txt");
	outb.open("outputB.txt");

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
	}
	else if (op == 2) {

	}


}
