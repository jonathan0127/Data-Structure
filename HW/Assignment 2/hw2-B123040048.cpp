//Author : 吳紹彰 B123040048
//Date : Sept.18,2024
/*Purpose : 
    利用C++製作一個Set的類別，並且實作出交集、聯集、差集、是否包含等功能
*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//Set的類別
class TSet{
    private:
        int size; //Set的大小
        char ch[256]; //Set的內容
    public:
        TSet(string ss); //constructor, ss為Set的內容
        void output(ofstream &out); //輸出Set，out為輸出的檔案
        friend void sort(TSet *st); //排序Set, st為要排序的Set
        friend bool is_contain(TSet a, TSet b); //判斷Set a是否包含Set b
        TSet operator*(TSet st);//this和st的交集
        TSet operator+(TSet st);//this和st的聯集
        TSet operator-(TSet st);//this和st的差集

};
//排序Set
void sort(TSet *st){ //st為要排序的Set
    //使用泡沫排序法
    for(int i = 0 ; i < st->size ; i ++){ //i為要排序的位置
        for(int j = i+1 ; j < st->size; j++){ //j為要比較的位置
            if(st->ch[j] < st->ch[i]){//如果j位置的元素比i位置的元素小，則交換
                //交換
                char tmp = st->ch[j]; //tmp為暫存的變數
                st->ch[j] = st->ch[i];
                st->ch[i] = tmp;
            }
        }
    }
}

//constructor
TSet::TSet(string ss){  //ss為Set的內容
    int idx = 0; //idx為Set的大小
    int used[256] = {0}; //used為紀錄Set中的元素是否使用過
    //將ss中的元素放入Set中
    for(int i = 0 ; i < ss.size() ; i ++){
        //如果元素已經使用過，則跳過
        if(used[(int)ss[i]]){ //ss[i]為元素
            continue;
        }
        //否則將元素放入Set中
        else{
            ch[idx] = ss[i];//放入Set中
            used[(int)ss[i]] = 1;//將元素設為使用過
            idx ++; //Set的大小加一
        }
    }
    size = idx; //設定Set的大小
    sort(this);//排序Set
}

//判斷Set a是否包含Set b
bool is_contain(TSet a, TSet b){ //a為Set a, b為Set b
    //將Set b中的元素和Set a中的元素比較
    for(int i = 0 ; i < b.size ; i++){ //i為Set b中的元素
        bool flag = 1; //flag為是否找到相同的元素
        for(int j = 0 ; j < a.size ; j ++){ //j為Set a中的元素
            if(a.ch[j] == b.ch[i]){ //如果找到相同的元素
                flag = 0; //設定flag為0
                break;
            }
        }
        //如果沒有找到相同的元素，則回傳0
        if(flag){
            return 0;
        }
    }
    //如果找到所有的元素，則回傳1
    return 1;
}

//將char陣列轉換成string
string tostr(char ch[], int size){ //ch為char陣列, size為陣列的大小
    string ret = ""; //ret為回傳的string
    //將char陣列轉換成string
    for(int i = 0 ; i < size ; i ++){
        ret += ch[i]; //將char陣列的元素放入string中
    }
    //回傳string
    return ret;
}

//Set的交集
TSet TSet::operator*(TSet st){ //st為Set st
    string s1 = tostr(this->ch, this->size); //s1為將this中的char陣列轉換成string
    string s2 = tostr(st.ch, size); //s2為將st中的char陣列轉換成string
    string s3 = ""; //s3為交集的string
    //將this和st的元素比較，找出交集
    for(int i = 0 ; i < this->size ; i ++){ //i為this中的元素
        for(int j = 0 ; j < st.size ; j ++){ //j為st中的元素
            //如果找到相同的元素，則放入交集中
            if(s1[i] == s2[j]){
                s3 += s1[i]; //放入交集中
            }
        }
    }
    //回傳交集
    return TSet(s3);
}
//Set的聯集
TSet TSet::operator+(TSet st){ //st為Set st
    string s1 = tostr(this->ch, this->size); //s1為將this中的char陣列轉換成string
    string s2 = tostr(st.ch, st.size); //s2為將st中的char陣列轉換成string
    string s3 = s1 + s2; //s3為聯集的string
    //回傳聯集
    return TSet(s3);
}

//Set的差集
TSet TSet::operator-(TSet st){ //st為Set st
    string s1 = tostr(this->ch, this->size); //s1為將this中的char陣列轉換成string
    string s2 = tostr(st.ch, st.size);//s2為將st中的char陣列轉換成string
    string s3 = ""; //s3為差集的string
    //將this中的元素和st中的元素比較，找出差集
    for(int i = 0 ; i < this->size ; i ++){ //i為this中的元素
        bool flag = 1; //flag為是否找到相同的元素       
        for(int j = 0 ; j < st.size ; j ++){ //j為st中的元素
        //如果找到相同的元素，則設定flag為0
            if(s1[i] == s2[j]){
                flag = 0;
                break;
            }
        }
        //如果沒有找到相同的元素，則放入差集中
        if(flag){
            s3 += s1[i]; //放入差集中
        }
    }
    //回傳差集
    return TSet(s3);
}

//輸出Set
void TSet::output(ofstream &out){ //out為輸出的out檔
//輸出Set
    out << '{';
    //輸出Set中的元素   
    for(int i = 0 ; i < size ; i ++){
        out << ch[i];
    }
    out << "}\n";
}



signed main(){
    int t; //t為測試的次數
    ofstream out("hw2-B123040048.out"); //out為輸出的out檔
    cin >> t;   //輸入測試的次數
    cin.ignore(); //忽略換行符號
    //進行t次的測試
    for(int i = 1 ; i <= t ; i ++){
        string a, b, x; // a為Set a, b為Set b, x為要判斷的char
        getline(cin, a);//輸入Set a
        getline(cin, b);//輸入Set b
        getline(cin, x);//輸入要判斷的char
        TSet A(a);//建立Set A
        TSet B(b);//建立Set B
        out << "Test Case " << i << ":\n";//輸出測試的編號
        out << "A: "; A.output(out);//輸出Set A
        out << "B: "; B.output(out);//輸出Set B
        TSet uni = A + B;//A和B的聯集
        out << "A+B: "; uni.output(out);//輸出A和B的聯集
        TSet intersec = A * B;//A和B的交集
        out << "A*B: "; intersec.output(out);//輸出A和B的交集
        TSet dif1 = A - B;//A和B的差集
        out << "A-B: "; dif1.output(out);//輸出A和B的差集
        TSet dif2 = B - A;//B和A的差集
        out << "B-A: "; dif2.output(out);//輸出B和A的差集   
        //判斷A是否包含B
        if(is_contain(A, B)){ //如果A包含B
            out << "A contains B\n";//輸出A包含B
        }
        //否則輸出A不包含B
        else{
            out << "A does not contain B\n";//輸出A不包含B
        }
        //判斷B是否包含A
        if(is_contain(B, A)){ //如果B包含A
            out << "B contains A\n"; //輸出B包含A
        }
        //否則輸出B不包含A
        else{
            out << "B does not contain A\n";//輸出B不包含A
        }
        //判斷x是否在A和B中
        TSet X(x);//建立Set X
        if(is_contain(A, X)){//如果A包含X
            out << "'" << x << "' is in A\n";//輸出x在A中
        }
        else{//否則輸出x不在A中
            out << "'" << x << "' is not in A\n";//輸出x不在A中
        }
        //判斷x是否在B和A中
        if(is_contain(B, X)){//如果B包含X
            out << "'" << x << "' is in B\n";//輸出x在B中
        }
        //否則輸出x不在B中
        else{
            out << "'" << x << "' is not in B\n";// 輸出x不在B中
        }
        out << '\n';//輸出換行符號
    }
    out.close();//關閉out檔
}