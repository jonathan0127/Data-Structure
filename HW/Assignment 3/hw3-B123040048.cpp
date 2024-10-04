//Author : 吳紹彰 B123040048
//Date : Oct.4,2024
/*Purpose : 
	利用C++製作一個Stack，並且實作出push、pop、top、empty來檢查騎士能不能走完棋盤
*/
#include<iostream>
using namespace std;

//E為存放騎士的位置和方向
struct E {
	//i, j為騎士的位置
	int i; 
	int j;
	//dir為騎士的方向
	int dir;
};

//Node為存放stack資料的節點
template <typename T>
class Node {
public:
	T data; //data為存放的資料
	Node *nxt; //nxt為下一個節點的指標
};

//存放資料的stack
template <typename T>
class stack {
public:
	Node<T> *head; //head為stack的頂端
	//constructor
	stack() {
		head = nullptr; //設定頂端為空
	}
	//push函數，將資料放入stack
	void push(T val) {
		Node<T>* n = new Node<T>; //n為新的節點
		n -> data = val; //設定新節點的資料
		n -> nxt = head; //設定新節點的下一個節點為原來的頂點
		head = n; //設定新節點為頂點
	}
	//empty函數，檢查stack是否為空，為空回傳1，不為空回傳0
	bool empty() {
		//如果頂端為空，則回傳1
		if (head == nullptr) {
			return 1;
		}
		//否則回傳0
		return 0;
	}
	//pop函數，將頂端的資料移除
	void pop() {
		//如果頂端為空，則不做任何事
		if (head == nullptr) return;
		//否則將頂端的資料移除
		Node<T> *tmp = head; //tmp為暫存頂端的節點
		head = head -> nxt; //將頂端設定為下一個節點
		delete tmp; //刪除暫存的節點
	}
	//top函數，回傳頂端的資料
	T top() {
		//如果頂端為空，則例外
		if (head == nullptr)throw;
		//否則回傳頂端的資料
		return head -> data;
	}
	//destructor
	~stack() {
		Node<T> *cur = head; //cur為目前的節點
		//將所有的節點刪除
		while (head != nullptr) {
			pop();
		}
	}

};

int K[9][2] = {{0, 0}, { -2, 1}, { -1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, { -1, -2}, { -2, -1}}; //K為騎士的移動方式
int ans[7][7]; //ans為存放騎士的位置

//檢查是否有空格
bool chk(int t) {
	//將所有的位置檢查一遍，如果有空格，則回傳1，否則回傳0
	for (int i = 1 ; i <= t ; i ++) {
		for (int j = 1 ; j <= t ; j ++) {
			if (ans[i][j] == 0)
				return 1;
		}
	}
	return 0;
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

		stack<E> st; //st為存放騎士的stack
		int cur = 1; //cur為順序
		st.push({1, 1, 1}); //將第一個騎士放入stack
		ans[1][1] = 1; //預設第一個騎士在(1, 1)
		bool flag = 0; //flag為是否有解
		//如果有空格，則繼續
		while (chk(t)) {
			//如果stack為空，則沒有解
			if (st.empty()) {
				cout << "no solution\n\n";
				flag = 1;
				break;
			}
			//否則繼續
			E pos = st.top();//pos為stack的頂端
			//如果騎士不能走，則將騎士移除
			if (pos.i + K[pos.dir][0] < 1 || pos.i + K[pos.dir][0] > t || pos.j + K[pos.dir][1] < 1 || pos.j + K[pos.dir][1] > t || ans[pos.i + K[pos.dir][0]][pos.j + K[pos.dir][1]] != 0) {
				st.pop(); //將騎士移除
				//如果方向小於8，則檢查下一個方向
				if (pos.dir < 8) {
					st.push({pos.i, pos.j, pos.dir + 1}); //將下一個方向放入stack
				}
				//否則將騎士移除
				else {
					ans[pos.i][pos.j] = 0; //將騎士移除
					cur--; //cur減一
				}
			}
			//否則繼續
			else{
				st.pop();//將騎士移除
				ans[pos.i + K[pos.dir][0]][pos.j + K[pos.dir][1]] = ++cur; //將騎士放入新的位置
				st.push({pos.i, pos.j, pos.dir + 1});//將下一個方向放入stack
				st.push({pos.i + K[pos.dir][0], pos.j + K[pos.dir][1], 1});//將新的騎士放入stack
			}


		}
		//如果有解，則continue
		if (flag) continue;
		//輸出棋盤
		for (int i = 1 ; i <= t ; i ++) {
			for (int j = 1 ; j <= t ; j ++) {
				cout << ans[i][j] << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
}