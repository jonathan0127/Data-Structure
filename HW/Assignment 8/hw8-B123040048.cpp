#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <iomanip>
using namespace std;

unordered_map<unsigned char, unsigned> freqMap;
vector<unsigned char> rawFile;
unordered_map<unsigned char, string> encode;
unordered_map<string, unsigned char> decode;

class HuffmanNode {
public:
    unsigned char data;
    unsigned frequency;
    HuffmanNode *left, *right;

    HuffmanNode(unsigned char d, unsigned freq) : 
        data(d), frequency(freq), left(nullptr), right(nullptr) {}

    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

struct CompareNode {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        if (l->frequency == r->frequency) {
            return l->data > r->data;
        }
        return l->frequency > r->frequency;
    }
};

HuffmanNode* buildTree(const unordered_map<unsigned char, unsigned>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> minHeap;
    for (const auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();
        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }
    return minHeap.top();
}

void DFS(HuffmanNode* root, string str) {
    if (!root) return;
    if (!root->left && !root->right) {
        encode[root->data] = str;
        decode[str] = root->data;
    }
    DFS(root->left, str + "0");
    DFS(root->right, str + "1");
}

void writeBitStream(ofstream& out, const string& bitString) {
    unsigned char buffer = 0;
    int count = 0;
    for (char bit : bitString) {
        buffer = (buffer << 1) | (bit - '0');
        count++;
        if (count == 8) {
            out.put(buffer);
            buffer = 0;
            count = 0;
        }
    }
    if (count > 0) {
        buffer = buffer << (8 - count);
        out.put(buffer);
    }
}

void compress(const string input, const string output){
    ifstream in(input, ios::in | ios::binary);
    unsigned char ch = in.get();
    while (in.good()) {
        rawFile.emplace_back(ch);
        freqMap[ch]++;
        ch = in.get();
    }
    in.clear();
    in.seekg(0);
    HuffmanNode* root = buildTree(freqMap);
    DFS(root, "");
    ofstream out(output, ios::out | ios::binary);
    size_t mapSize = freqMap.size();
    out.write(reinterpret_cast<const char*>(&mapSize), sizeof(size_t));
    for (const auto& pair : freqMap) {
        out.put(pair.first);
        out.write(reinterpret_cast<const char*>(&pair.second), sizeof(unsigned));
    }
    string bitString;
    for (unsigned char c : rawFile) {
        bitString += encode[c];
    }
    size_t paddingBits = (8 - (bitString.size() % 8)) % 8;
    bitString.append(paddingBits, '0');
    out.write(reinterpret_cast<const char*>(&paddingBits), sizeof(size_t));
    writeBitStream(out, bitString);
    size_t compressedSize = out.tellp();
    cout << "Original Size: " << rawFile.size() << " bytes\n";
    cout << "Compressed Size: " << compressedSize << " bytes\n";
    cout << "Compression Ratio: " << fixed << setprecision(3) << (double)rawFile.size() / compressedSize << "\n";
    delete root;
    in.close();
    out.close();
}

void decompress(const string input, const string output){
    ifstream in(input, ios::in | ios::binary);
    if (!in) {
        cout << "Cannot open input file\n";
        return;
    }
    size_t freqMapSize;
    in.read(reinterpret_cast<char*>(&freqMapSize), sizeof(size_t));
    for (size_t i = 0; i < freqMapSize; ++i) {
        unsigned char ch;
        unsigned freq;
        in.get(reinterpret_cast<char&>(ch));
        in.read(reinterpret_cast<char*>(&freq), sizeof(unsigned));
        freqMap[ch] = freq;
    }
    HuffmanNode* root = buildTree(freqMap);
    DFS(root, "");
    size_t paddingBits;
    in.read(reinterpret_cast<char*>(&paddingBits), sizeof(size_t));
    string bitString;
    unsigned char byte;
    while (in.read(reinterpret_cast<char*>(&byte), 1)) {
        for (int i = 7; i >= 0; --i) {
            bitString += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    bitString = bitString.substr(0, bitString.length() - paddingBits);
    ofstream out(output, ios::out | ios::binary);
    if (!out) {
        cout << "Cannot open output file\n";
        delete root;
        return;
    }
    string cur = "";
    for (const char& c : bitString) {
        cur += c;
        if (decode.find(cur) != decode.end()) {
            out.put(decode[cur]);
            cur = "";
        }
    }
    out.close();
    delete root;
    in.close();
}

signed main(int argc, char *argv[]){
    if(argc != 4){
        cout << "Input Error" << endl;
        return 0;
    }
    if(string(argv[1]) == "-z"){
        compress(string(argv[2]), string(argv[3]));
    }
    else if(string(argv[1]) == "-u"){
        decompress(string(argv[2]), string(argv[3]));
    }
    else{
        cout << "Input Error" << endl;
    }
}
