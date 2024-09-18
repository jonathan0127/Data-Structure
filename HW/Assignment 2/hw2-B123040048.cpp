//Author : 吳紹彰 B123040048
//Date : Sept.17,2024
/*Purpose : 

*/
#include<iostream>
using namespace std;


class TSet{
    private:
        int size;
        char ch[256];
    public:
        TSet(string ss);
        void output();
        friend void sort(TSet *st);
        TSet operator*(TSet st);
        TSet operator+(TSet st);
        TSet operator-(TSet st);
        //friend TSet check(TSet st);

};

// TSet check(TSet st){

// }
void sort(TSet *st){
    for(int i = 0 ; i < st->size ; i ++){
        for(int j = i+1 ; j < st->size; j++){
            if(st->ch[j] < st->ch[i]){
                char tmp = st->ch[j];
                st->ch[j] = st->ch[i];
                st->ch[i] = tmp;
            }
        }
    }
}


TSet::TSet(string ss){
    int idx = 0;
    int used[256] = {0};
    for(int i = 0 ; i < ss.size() ; i ++){
        if(used[(int)ss[i]]){
            continue;
        }
        else{
            ch[idx] = ss[i];
            used[(int)ss[i]] = 1;
            idx ++;
        }
    }
    size = idx;
    sort(this);
}

string tostr(char ch[], int size){
    string ret = "";
    for(int i = 0 ; i < size ; i ++){
        ret += ch[i];
    }
    return ret;
}

TSet TSet::operator*(TSet st){
    string s1 = tostr(this->ch, this->size);
    string s2 = tostr(st.ch, size);
    string s3 = "";
    for(int i = 0 ; i < this->size ; i ++){
        for(int j = 0 ; j < st.size ; j ++){
            if(s1[i] == s2[j]){
                s3 += s1[i];
            }
        }
    }
    
    return TSet(s3);
}
TSet TSet::operator+(TSet st){
    string s1 = tostr(this->ch, this->size);
    string s2 = tostr(st.ch, size);
    string s3 = s1 + s2;
    return TSet(s3);
}

TSet TSet::operator*(TSet st){
    string s1 = tostr(this->ch, this->size);
    string s2 = tostr(st.ch, size);
    string s3 = "";
    for(int i = 0 ; i < this->size ; i ++){
        bool flag = 1;
        for(int j = 0 ; j < st.size ; j ++){
            if(s1[i] == s2[j]){
                flag = 0;
                break;
            }
        }
        if(flag){
            s3 += s1[i];
        }
    }
    
    return TSet(s3);
}

void TSet::output(){
    cout << '{';
    for(int i = 0 ; i < size ; i ++){
        cout << ch[i];
    }
    cout << '}';
}



signed main(){
    int t;
    cin >> t;
    for(int i = 1 ; i <= t ; i ++){
        string a, b;
        cin >> a >> b;
        TSet A(a);
        TSet B(b);
    }
}