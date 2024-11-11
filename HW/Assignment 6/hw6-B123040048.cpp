//Author : 吳紹彰 B123040048
//Date : Nov.11,2024
/*Purpose : 
	
*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;




//NODE為多項式的節點
class NODE {
public:
	int data; //coef為係數，exp為次方
	NODE *left, *right;//nxt為下一個節點
	NODE(NODE *left, NODE *right, int data): left(left), right(right), data(data) {} //constructor
};

class Tree{
	public:
		NODE *root = nullptr;
		Tree();
		void insert(int data);
		void clear(NODE *cur);
		void travel(NODE *cur);
		void del(NODE *pos, NODE *par);
};

Tree::Tree(){
	root = nullptr;
}

void Tree::travel(NODE *cur){
	if(cur->left == nullptr && cur->right == nullptr){
		cout << cur->data << ' '; 
		return;
	}
	travel(cur->left);
	if(!cur->left) cout << cur->left->data << ' ';
	cout << 

}

void Tree::insert(int data){
	if(root == nullptr){
		root = new NODE(nullptr, nullptr, data);
		return;
	}
	NODE *tmp = root;
	NODE *par = nullptr;
	while(tmp != nullptr){

		if(tmp -> data > data){
			par = tmp;
			tmp = tmp -> left;
		}
		else if(tmp -> data < data){
			par = tmp;
			tmp = tmp -> right;
		}
		else{
			del(tmp, par);
			return;
		}

	}
	tmp = new NODE(nullptr, nullptr, data);
}

void Tree::del(NODE *pos, NODE *par){
	if(pos->left == nullptr && pos->right == nullptr){
		if(par == nullptr){
			root = nullptr;
			delete pos;
		}
		else{
			if(par->left == pos){
				delete pos;
				par->left = nullptr;
			}
			else{
				delete pos;
				par->right = nullptr;
			}
		}
	}
	else if(pos->left == nullptr){
		if(par == nullptr){
			root = pos->right;
			delete pos;
		}
		else{
			if(par->left == pos){

				par->left = pos->right;
				delete pos;
			}
			else{
				par->right = pos->right;
				delete pos;
			}
		}
	}
	else if(pos->right == nullptr){
		if(par == nullptr){
			root = pos->left;
			delete pos;
		}
		else{
			if(par->left == pos){

				par->left = pos->left;
				delete pos;
			}
			else{
				par->right = pos->left;
				delete pos;
			}
		}
	}
	else{
		NODE *mn = pos->right;
		NODE *par2 = nullptr;
		while(mn -> left != nullptr){
			par2 = mn;
			mn = mn -> left;
		}
		pos->data = mn->data;

		if(mn->left == nullptr && mn->right == nullptr){
			if(par2->left == mn){
				par2->left = nullptr;
			}
			else{
				par2->right = nullptr;
			}
		}
		else{
			if(par2->left == mn){
				par2->left = mn->right;
			}
			else{
				par2->right = mn->right;
			}
		}
	}
	return;
}

void Tree::clear(NODE *cur){
	if(cur == nullptr){
		return;
	}
	else if(cur->left == nullptr && cur->right == nullptr){
		delete cur;
		return;
	}
	clear(cur->left);
	clear(cur->right);
	clear(cur);
}

int main() {
	ofstream out("hw6-B123040048.out"); //out為輸出的out檔
	while(1){
		Tree t;
		while(1){
			int n;
			if(!cin >> n){
				t.clear(t.root);
				return 0;
			}
			if(n == -1) {
				break;
			}

			t.insert(n);


		}
		cout << "node: ";
		t.travel(t.root);
		t.clear(t.root);
	}
	out.close();//關閉out檔
}