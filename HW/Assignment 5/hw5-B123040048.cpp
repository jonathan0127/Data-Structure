#include<iostream>
#include<string>
#include<fstream>
using namespace std;





class NODE {
public:
	int coef, exp;
	NODE *nxt;
	NODE(int a, int b, NODE *c): coef(a), exp(b), nxt(c) {}
};


class POLY {
public:
	POLY();
	void clean();
	void addnode(int coef, int exp);
	POLY operator+(const POLY b);
	POLY operator*(const POLY b);
	void output(ofstream &out);
	void wipe();
private:
	NODE *head;


};

POLY::POLY() {
	this->head = nullptr;
}

void POLY::clean() {
	if (head == nullptr) return;
	if (this->head->coef == 0) {
		NODE *tmp = head;
		head = head->nxt;
		delete tmp;
		return;
	}
	NODE *cur = head;
	while (cur) {
		if (cur->nxt == nullptr) return;
		if (cur->nxt->coef == 0) {
			cur->nxt = cur->nxt->nxt;
			delete cur->nxt;
		}
		cur = cur -> nxt;
	}
}

void POLY::addnode(int coef, int exp) {
	if (this->head == nullptr) {
		this->head = new NODE(coef, exp, nullptr);
		return;
	}
	NODE *tmp = head;
	if (tmp->exp < exp) {
		head = new NODE(coef, exp, tmp);
		return;
	}
	if (tmp->exp == exp) {
		tmp->coef += coef;
		return;
	}
	while (tmp) {
		if (tmp->nxt == nullptr) {
			tmp->nxt = new NODE(coef, exp, nullptr);
			return;
		}
		if (tmp->nxt->exp == exp) {
			tmp->nxt->coef += coef;
			return;
		}
		if (tmp->nxt->exp < exp) {
			tmp->nxt = new NODE(coef, exp, tmp->nxt);
			return;
		}
		tmp = tmp -> nxt;
	}

}

POLY POLY::operator+(const POLY b) {
	POLY *ret = new POLY();
	for (NODE *i = this->head ; i != nullptr ; i = i -> nxt) {
		ret->addnode(i->coef, i->exp);
	}
	for (NODE *i = b.head ; i != nullptr ; i = i -> nxt) {
		ret->addnode(i->coef, i->exp);
	}
	ret->clean();
	return *ret;
}

POLY POLY::operator*(const POLY b) {
	POLY *ret = new POLY();
	for (NODE *i = this->head ; i != nullptr ; i = i -> nxt) {
		for (NODE *j = b.head ; j != nullptr ; j = j -> nxt) {
			ret->addnode(i->coef * j->coef, i->exp + j->exp);
		}
	}

	ret->clean();
	return *ret;
}


void POLY::wipe() {
	while (head) {
		NODE *tmp = this->head;
		head = head -> nxt;
		delete tmp;
	}
}
void POLY::output(ofstream &out) {
	for (NODE *i = head; i != nullptr; i = i->nxt)
		out << i->coef << " " << i->exp << endl;
	if (head == nullptr)
		out << "0 0" << endl;
}



int main() {
	ofstream out("hw5-B123040048.out"); //out為輸出的out檔
	int p, q, ca = 1;
	POLY A, B, C, D;
	while (1) {
		A.wipe();
		B.wipe();
		C.wipe();
		D.wipe();
		cin >> p;
		for (int i = 0 ; i < p ; i ++) {
			int c, e;
			cin >> c >> e;
			A.addnode(c, e);
		}
		A.clean();
		cin >> q;
		for (int i = 0 ; i < q ; i ++) {
			int c, e;
			cin >> c >> e;
			B.addnode(c, e);
		}
		B.clean();

		if (p == 0 && q == 0) break;
		out << "Case" << ca++ << ":\n";
		out << "ADD\n";
		C = A + B;
		C.output(out);

		out << "MULTIPLY\n";
		D = A * B;
		D.output(out);


	}
	out.close();//關閉out檔
}