//Author : 吳紹彰 B123040048
//Date : Nov.12,2024
/*Purpose :
	利用binary search tree，找出所有出現次數為奇數之數字
*/
#include<iostream>
using namespace std;



//NODE為樹的節點
class NODE {
public:
	int data; //data為節點的值
	NODE *left, *right; //left為左子樹，right為右子樹
	NODE(NODE *left, NODE *right, int data): left(left), right(right), data(data) {} //constructor
};

class Tree {
public:
	NODE *root = nullptr; //root為樹的根節點
	Tree(); //constructor
	void insert(int data); //插入新節點
	void clear(NODE *cur); //清空樹
	void travel(NODE *cur); //中序遍歷
	void travelLeft(NODE *cur); //中序遍歷，並印出左子樹
	void travelRight(NODE *cur); //中序遍歷，並印出右子樹
	void del(NODE *pos, NODE *par); //刪除節點
};

Tree::Tree() {
	root = nullptr;
}
//中序遍歷
void Tree::travel(NODE *cur) {
	if (cur == nullptr) return; //如果節點為空，返回
	travel(cur->left); //遞迴處理左子樹
	cout << cur->data << ' '; //印出節點的值
	travel(cur->right);//遞迴處理右子樹
	return;
}

//中序遍歷，並印出左子樹
void Tree::travelLeft(NODE *cur) {
	if (cur == nullptr) return; //如果節點為空，返回
	travelLeft(cur->left);//遞迴處理左子樹
	//印出左子樹的值
	if (cur->left == nullptr) {
		cout << 0 << ' '; //如果左子樹為空，印出0
	} else {
		cout << cur->left->data << ' '; //印出左子樹的值
	}
	travelLeft(cur->right);//遞迴處理右子樹
}

//中序遍歷，並印出右子樹
void Tree::travelRight(NODE *cur) { //中序遍歷，並印出右子樹
	if (cur == nullptr) return; // 如果節點為空，返回
	travelRight(cur->left); //遞迴處理左子樹
	if (cur->right == nullptr) { //印出右子樹的值
		cout << 0 << ' '; //如果右子樹為空，印出0
	} else {
		cout << cur->right->data << ' '; //印出右子樹的值
	}
	travelRight(cur->right); //遞迴處理右子樹

}

//插入新節點
void Tree::insert(int data) {
	// 如果樹為空，則插入新節點
	if (root == nullptr) {
		root = new NODE(nullptr, nullptr, data);
		return;
	}

	NODE *tmp = root; // tmp為目前節點
	NODE *par = nullptr;// par為目前節點的父節點

	while (tmp != nullptr) { // 遍歷樹
		if (tmp->data == data) {
			// 如果找到相同的值，刪除該節點
			del(tmp, par); //刪除節點
			return;
		}

		par = tmp; // 更新父節點
		// 如果新節點的值小於目前節點的值，則往左子樹走，否則往右子樹走
		if (data < tmp->data) {
			tmp = tmp->left;
		} else {
			tmp = tmp->right;
		}
	}

	// 在找到的位置插入新節點
	NODE* newNode = new NODE(nullptr, nullptr, data);
	// 如果新節點的值小於父節點的值，則插入左子樹，否則插入右子樹
	if (data < par->data) {
		par->left = newNode; //插入左子樹
	}

	else {
		par->right = newNode; //插入右子樹
	}
}

//刪除節點
void Tree::del(NODE *pos, NODE *par) {
	// 如果要刪除的節點為葉節點，則直接刪除
	if (pos->left == nullptr && pos->right == nullptr) {
		if (par == nullptr) { // 如果要刪除的節點為根節點
			root = nullptr;	// 將根節點設為空
			delete pos;
		}
		else {
			// 如果要刪除的節點為父節點的左子樹，則將父節點的左子樹設為空
			if (par->left == pos) {
				delete pos;
				par->left = nullptr;
			}
			// 如果要刪除的節點為父節點的右子樹，則將父節點的右子樹設為空
			else {
				delete pos;
				par->right = nullptr;
			}
		}
	}
	// 如果要刪除的節點只有一個子樹，則將子樹接到父節點的位置
	else if (pos->left == nullptr) {
		// 如果要刪除的節點為根節點，則將根節點設為右子樹
		if (par == nullptr) {
			root = pos->right;
			delete pos;
		}
		// 如果要刪除的節點為父節點的左子樹，則將父節點的左子樹設為右子樹
		else {
			// 將父節點的左子樹設為右子樹
			if (par->left == pos) {

				par->left = pos->right;
				delete pos;
			}
			// 將父節點的右子樹設為右子樹
			else {
				par->right = pos->right;
				delete pos;
			}
		}
	}
	// 如果要刪除的節點只有一個子樹，則將子樹接到父節點的位置
	else if (pos->right == nullptr) {
		// 如果要刪除的節點為根節點，則將根節點設為左子樹
		if (par == nullptr) {
			root = pos->left;
			delete pos;
		}
		// 如果要刪除的節點為父節點的左子樹，則將父節點的左子樹設為左子樹
		else {
			// 將父節點的左子樹設為左子樹
			if (par->left == pos) {

				par->left = pos->left;
				delete pos;
			}
			// 將父節點的右子樹設為左子樹
			else {
				par->right = pos->left;
				delete pos;
			}
		}
	}
	// 如果要刪除的節點有兩個子樹，則將右子樹的最小節點取代要刪除的節點
	else {
		NODE *mn = pos->right; // mn為右子樹的最小節點
		NODE *par2 = pos;  // 改為從 pos 開始找最小節點的父節點
		// 找到右子樹的最小節點
		while (mn->left != nullptr) {
			par2 = mn; // 更新父節點
			mn = mn->left;// 找到最小節點
		}
		// 將最小節點的值取代要刪除的節點
		pos->data = mn->data;
		// 刪除最小節點

		if (par2 == pos) {// 如果最小節點為要刪除的節點的右子樹
			pos->right = mn->right; //將右子樹設為最小節點的右子樹
		} 
		else {
			par2->left = mn->right; //將最小節點的右子樹設為空
		}
		delete mn; //刪除最小節點
	}
	return;
}

//清空樹
void Tree::clear(NODE *cur) {
	if (cur == nullptr) {
		return;
	}
	// 遞迴處理左子樹和右子樹
	clear(cur->left);
	clear(cur->right);
	delete cur;
}

int main() {
	while (1) {

		Tree t; //建立樹
		//讀入數字
		while (1) {
			int n; //n為讀入的數字
			//若EOF則清空樹並結束程式
			if (!(cin >> n)) {
				t.clear(t.root);
				return 0;
			}
			//若讀入-1則結束讀入
			if (n == -1) {
				break;
			}

			t.insert(n); //插入新節點


		}
		//印出結果
		cout << "node: ";
		t.travel(t.root); //中序遍歷
		cout << "\nleft: ";
		t.travelLeft(t.root); //中序遍歷，並印出左子樹
		cout << "\nright: ";
		t.travelRight(t.root); //中序遍歷，並印出右子樹
		cout << "\n\n";

		t.clear(t.root); //清空樹
	}
}