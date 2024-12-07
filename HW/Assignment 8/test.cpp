#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// Author:�����a B093040044
// Date:Dec.18.2020
// Huffman Compress

// Header�Φr���x�s

vector<unsigned char> RawFile;
vector<unsigned char> Result;
map<unsigned char, int> FreqPerChar;
map<unsigned char, string> HuffmanTable;
map<string, unsigned char> DecodeTable;
int totalbit = 0;

struct HuffmanNode {
    HuffmanNode* LC = NULL;
    HuffmanNode* RC = NULL;
    int freq;
    unsigned char ch;
    HuffmanNode(unsigned char c, int f) {
        ch = c;
        freq = f;
    }
};

// PriorityQueue������禡
struct cmp {
    bool operator()(HuffmanNode* n1, HuffmanNode* n2) {
        //���Ƭ۵��h�r��Ǥp���u�����X
        if (n1->freq == n2->freq) {
            return n1->ch > n2->ch;
        }
        return n1->freq > n2->freq;
    }
};

//�M�中�l �s�@�s�X��
void DFS(string Code, HuffmanNode* nowNode) {
    if (nowNode->LC == NULL && nowNode->RC == NULL) {
        HuffmanTable.emplace(make_pair(nowNode->ch, Code));
        return;
    }
    DFS(Code + '0', nowNode->LC);
    DFS(Code + '1', nowNode->RC);
}

//�i��s�X �C8��bit�নunsigned char
void Encode() {
    int cnt = 0;
    unsigned char tmp = 0;
    for (auto i : RawFile) {
        for (int j = 0; j < HuffmanTable[i].size(); j++) {
            totalbit++;
            tmp <<= 1;
            cnt++;
            tmp += (HuffmanTable[i][j] - '0');
            if (cnt == 8) {
                cnt = 0;
                Result.emplace_back(tmp);
                tmp = 0;
            }
        }
    }
    if (cnt) Result.emplace_back(tmp);
}

//�ѽX�ÿ�X���G
void Decode(string FileName) {
    fstream OutFile;
    OutFile.open(FileName, ios::out | ios::binary);
    string buff = "";
    int Prefix = (totalbit / 8) * 8, bitcnt = 0;
    for (auto i : RawFile) {
        for (int j = 7; j >= 0; j--) {
            bitcnt++;

            //�����㪺byte�B�z
            if (bitcnt > Prefix && bitcnt <= Prefix + (8 - totalbit % 8))
                continue;

            // char to bool
            buff += (((i >> j) & 1) + '0');

            if (DecodeTable.count(buff)) {
                OutFile << DecodeTable[buff];
                buff = "";
            }
        }
    }
    OutFile.close();
}

//Ū�J�n���Y���ɮ�
void ReadFile(string FileName) {
    ifstream InputFile;
    InputFile.open(FileName, ios::in | ios::binary);

    unsigned char ch = InputFile.get();
    while (InputFile.good()) {
        RawFile.emplace_back(ch);

        //�x�s����
        FreqPerChar[ch]++;

        ch = InputFile.get();
    }
    InputFile.close();
}

//Ū�J���Y�L���ɮ�
void ReadBinFile(string FileName) {
    ifstream InputFile;
    InputFile.open(FileName, ios::in | ios::binary);
    int n = 0;

    int buffC;
    string buffS;

    // n�ӽs�X Ū�Jtotalbit�H�i�楼���㪺byte�B�z
    InputFile >> n >> totalbit;

    for (int i = 0; i < n; i++) {
        InputFile >> buffC >> buffS;
        DecodeTable[buffS] = buffC;
    }

    //���Y�ebyte,���Y��byte,���Y�v
    string Before, After, compressRatio;
    InputFile >> Before >> After >> compressRatio;
    InputFile.get();
    unsigned char ch = InputFile.get();
    while (InputFile.good()) {
        RawFile.emplace_back(ch);
        ch = InputFile.get();
    }
    InputFile.close();
}

HuffmanNode* BuildHuffmanTree() {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, cmp> pq;
    for (auto i : FreqPerChar) {
        pq.push(new HuffmanNode(i.first, i.second));
    }
    while (pq.size() != 1) {
        HuffmanNode *n1, *n2, *tmp;
        n1 = pq.top();
        pq.pop();
        n2 = pq.top();
        pq.pop();
        unsigned char cmin = min(n1->ch, n2->ch);
        tmp = new HuffmanNode(cmin, n1->freq + n2->freq);
        if (cmin == n1->ch) {
            tmp->LC = n1;
            tmp->RC = n2;
        } else {
            tmp->RC = n1;
            tmp->LC = n2;
        }
        pq.push(tmp);
    }
    return pq.top();
}

void GenZipFile(string FileName) {
    fstream OutFile;
    OutFile.open(FileName, ios::out | ios::binary);
    OutFile << HuffmanTable.size() << ' ' << totalbit << '\n';

    //��X�s�X��
    for (auto i : HuffmanTable) {
        cout << i.first << ": " << i.second << '\n';
        OutFile << (int)i.first << ' ' << i.second << '\n';
    }

    //�p��ÿ�X���Y�v�����Y�e�᪺byte
    OutFile << RawFile.size() << '\n';
    int Headersize = 6 + OutFile.tellg();
    int digit = 0, temp = Headersize + Result.size();
    while (temp) {
        temp /= 10;
        digit++;
        
    }
    int CompressedSize = Result.size() + Headersize + digit + 1;
    OutFile << CompressedSize << '\n';
    OutFile << fixed << setprecision(3) << 1.0 * RawFile.size() / CompressedSize
            << '\n';

    cout << "Origin:" << RawFile.size() << "Bytes\n";
    cout << "Compressed:" << CompressedSize << "Bytes\n";
    cout << "Compression Ratio:" << 1.0 * RawFile.size() / CompressedSize
         << '\n';

    for (auto i : Result) {
        OutFile << i;
    }
    OutFile.close();
}

void Zip(string InputFileName, string OutputFileName) {
    ReadFile(InputFileName);
    HuffmanNode* root = BuildHuffmanTree();
    DFS("", root);
    Encode();
    GenZipFile(OutputFileName);
}

void Unzip(string InputFileName, string OutputFileName) {
    ReadBinFile(InputFileName);
    Decode(OutputFileName);
}

int main(int argc, char* argv[]) {
    if (argc == 4) {
        if (string(argv[1]) == "-z") {
            Zip(string(argv[2]), string(argv[3]));
        } else if (string(argv[1]) == "-u") {
            Unzip(string(argv[2]), string(argv[3]));
        } else {
            printf("ERROR1\n");
        }
    } else {
        printf("ERROR2\n");
    }
    return 0;
}