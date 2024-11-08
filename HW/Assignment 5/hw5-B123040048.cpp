//Author : 吳紹彰 B123040048
//Date : Oct.31,2024
/*Purpose : 
	利用linked list處理兩個多項式之加法與乘法
*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;




//NODE為多項式的節點
class NODE {
public:
	int coef, exp; //coef為係數，exp為次方
	NODE *nxt;//nxt為下一個節點
	NODE(int a, int b, NODE *c): coef(a), exp(b), nxt(c) {} //constructor
};

//POLY為多項式
class POLY {
public:
	POLY(); //constructor
	void clean(); //clean為清除多餘的節點
	void addnode(int coef, int exp); //addnode為增加節點
	POLY operator+(const POLY b); //operator+為多項式的加法
	POLY operator*(const POLY b);//operator*為多項式的乘法
	void output(ofstream &out);//output為輸出多項式
	void wipe();//wipe為清除多項式
private:
	NODE *head;//head為多項式的頭


};

POLY::POLY() {
	this->head = nullptr; //初始化head為nullptr
}

void POLY::clean() {
	//如果head為nullptr，則回傳
	if (head == nullptr) return;
	//如果head的coef為0，則刪除head
	if (this->head->coef == 0) {
		NODE *tmp = head;
		head = head->nxt;
		delete tmp;
		return;
	}
	//檢查多餘的節點
	NODE *cur = head; //cur為目前的節點
	while (cur) {//如果cur不為nullptr，則繼續
		if (cur->nxt == nullptr) return;
		//如果下一個節點的coef為0，則刪除下一個節點
		if (cur->nxt->coef == 0) {
			cur->nxt = cur->nxt->nxt;
			delete cur->nxt;
		}
		cur = cur -> nxt;
	}
}


void POLY::addnode(int coef, int exp) {
	//如果head為nullptr，則增加節點
	if (this->head == nullptr) {
		this->head = new NODE(coef, exp, nullptr); //增加節點
		return;
	}
	//如果head的exp小於exp，則增加節點
	NODE *tmp = head; //tmp為目前的節點
	if (tmp->exp < exp) {
		head = new NODE(coef, exp, tmp);
		return;
	}
	//檢查是否有重複的exp，如果有，則合併
	if (tmp->exp == exp) {
		tmp->coef += coef;
		return;
	}
	//檢查是否有比exp大的exp，如果有，則增加節點
	while (tmp) {
		//如果下一個節點為nullptr，則增加節點到最後
		if (tmp->nxt == nullptr) {
			tmp->nxt = new NODE(coef, exp, nullptr);
			return;
		}
		//如果下一個節點的exp等於exp，則合併
		if (tmp->nxt->exp == exp) {
			tmp->nxt->coef += coef;
			return;
		}
		//如果下一個節點的exp小於exp，則增加節點
		if (tmp->nxt->exp < exp) {
			tmp->nxt = new NODE(coef, exp, tmp->nxt);
			return;
		}
		tmp = tmp -> nxt; //繼續檢查下一個節點
	}

}

POLY POLY::operator+(const POLY b) {
	//ret為回傳的多項式
	POLY *ret = new POLY();
	//將兩個多項式合併
	for (NODE *i = this->head ; i != nullptr ; i = i -> nxt) {
		ret->addnode(i->coef, i->exp); //增加節點
	}
	for (NODE *i = b.head ; i != nullptr ; i = i -> nxt) {
		ret->addnode(i->coef, i->exp); //增加節點
	}
	//清除多餘的節點
	ret->clean();
	return *ret; //回傳ret
}

POLY POLY::operator*(const POLY b) {
	POLY *ret = new POLY(); //ret為回傳的多項式
	//將兩個多項式相乘
	for (NODE *i = this->head ; i != nullptr ; i = i -> nxt) {
		for (NODE *j = b.head ; j != nullptr ; j = j -> nxt) {
			ret->addnode(i->coef * j->coef, i->exp + j->exp); //coef相乘，exp相加
		}
	}
	//清除多餘的節點
	ret->clean();
	return *ret; //回傳ret
}


void POLY::wipe() {
	//刪除所有的節點
	while (head) {
		NODE *tmp = this->head;
		head = head -> nxt;
		delete tmp;
	}
}
void POLY::output(ofstream &out) {
	//輸出多項式
	for (NODE *i = head; i != nullptr; i = i->nxt)
		out << i->coef << " " << i->exp << endl;
	//如果head為nullptr，則輸出0 0
	if (head == nullptr)
		out << "0 0" << endl;
}



int main() {
	ofstream out("hw5-B123040048.out"); //out為輸出的out檔
	int p, q, ca = 1; //p為第一個多項式的節點數，q為第二個多項式的節點數，ca為case的編號
	POLY A, B, C, D; //A, B, C, D為多項式
	while (1) {
		//清除多項式
		A.wipe();
		B.wipe();
		C.wipe();
		D.wipe();

		cin >> p; //讀取p
		//讀取第一個多項式的節點
		for (int i = 0 ; i < p ; i ++) {
			int c, e; //c為係數，e為次方
			cin >> c >> e;
			A.addnode(c, e); //增加節點
		}
		A.clean(); //清除多餘的節點

		cin >> q; //讀取q
		//讀取第二個多項式的節點
		for (int i = 0 ; i < q ; i ++) {
			int c, e; //c為係數，e為次方
			cin >> c >> e;
			B.addnode(c, e); //增加節點
		}
		//清除多餘的節點
		B.clean();
		//如果p和q都為0，則break
		if (p == 0 && q == 0) break;
		out << "Case" << ca++ << ":\n"; //輸出case的編號
		//輸出ADD和MULTIPLY
		out << "ADD\n"; 
		C = A + B; //C為A和B相加的結果
		C.output(out); //輸出C

		out << "MULTIPLY\n"; 
		D = A * B; //D為A和B相乘的結果
		D.output(out); //輸出D


	}
	out.close();//關閉out檔
}