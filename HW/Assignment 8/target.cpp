#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

// Node for Huffman Tree
struct HuffmanNode {
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

// Comparator for priority queue
struct CompareNode {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        if (l->frequency == r->frequency) {
            // If frequencies are equal, compare lexicographically
            return l->data > r->data;
        }
        return l->frequency > r->frequency;
    }
};

class HuffmanCoder {
private:
    std::unordered_map<unsigned char, std::string> huffmanCodes;
    std::unordered_map<std::string, unsigned char> reverseHuffmanCodes;

    // Generate Huffman codes recursively
    void generateCodes(HuffmanNode* root, const std::string& str) {
        if (!root) return;

        if (!root->left && !root->right) {
            huffmanCodes[root->data] = str;
            reverseHuffmanCodes[str] = root->data;
        }

        generateCodes(root->left, str + "0");
        generateCodes(root->right, str + "1");
    }

    // Build Huffman Tree
    HuffmanNode* buildHuffmanTree(const std::unordered_map<unsigned char, unsigned>& freqMap) {
        // Create a priority queue
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> minHeap;

        // Create leaf nodes for each character
        for (const auto& pair : freqMap) {
            minHeap.push(new HuffmanNode(pair.first, pair.second));
        }

        // Build the Huffman tree
        while (minHeap.size() > 1) {
            HuffmanNode* left = minHeap.top(); minHeap.pop();
            HuffmanNode* right = minHeap.top(); minHeap.pop();

            // Create a new internal node
            HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
            parent->left = left;
            parent->right = right;

            minHeap.push(parent);
        }

        return minHeap.top();
    }

public:
    // Compress file
    bool compressFile(const std::string& inputFile, const std::string& outputFile) {
        // Read input file
        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile) {
            std::cerr << "Cannot open input file\n";
            return false;
        }

        // Calculate frequency
        std::unordered_map<unsigned char, unsigned> freqMap;
        unsigned char byte;
        while (inFile.read(reinterpret_cast<char*>(&byte), 1)) {
            freqMap[byte]++;
        }

        // Reset file pointer
        inFile.clear();
        inFile.seekg(0);

        // Build Huffman tree and generate codes
        HuffmanNode* root = buildHuffmanTree(freqMap);
        generateCodes(root, "");

        // Open output file
        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile) {
            std::cerr << "Cannot open output file\n";
            delete root;
            return false;
        }

        // Write file header
        size_t originalSize = inFile.seekg(0, std::ios::end).tellg();
        inFile.seekg(0);

        // Write original size
        outFile.write(reinterpret_cast<const char*>(&originalSize), sizeof(originalSize));

        // Write frequency map size and frequencies
        size_t freqMapSize = freqMap.size();
        outFile.write(reinterpret_cast<const char*>(&freqMapSize), sizeof(freqMapSize));

        for (const auto& pair : freqMap) {
            outFile.write(reinterpret_cast<const char*>(&pair.first), sizeof(pair.first));
            outFile.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
        }

        // Compress file content
        std::string bitString;
        while (inFile.read(reinterpret_cast<char*>(&byte), 1)) {
            bitString += huffmanCodes[byte];
        }

        // Pad bitstring to full bytes
        size_t paddingBits = 8 - (bitString.length() % 8);
        bitString += std::string(paddingBits, '0');
        outFile.write(reinterpret_cast<const char*>(&paddingBits), sizeof(paddingBits));

        // Write compressed data
        for (size_t i = 0; i < bitString.length(); i += 8) {
            byte = 0;
            for (int j = 0; j < 8; ++j) {
                byte = (byte << 1) | (bitString[i + j] - '0');
            }
            outFile.write(reinterpret_cast<const char*>(&byte), 1);
        }

        // Output compression info
        size_t compressedSize = outFile.tellp();
        double compressionRatio = static_cast<double>(compressedSize) / originalSize;

        std::cout << "Original file size: " << originalSize << " bytes\n";
        std::cout << "Compressed file size: " << compressedSize << " bytes\n";
        std::cout << "Compression ratio: " << compressionRatio << "\n";

        // Output Huffman encoding table
        std::ofstream tableFile("huffman_table.txt");
        for (const auto& pair : huffmanCodes) {
            tableFile << "'" << pair.first << "': " << pair.second << "\n";
        }

        delete root;
        return true;
    }

    // Decompress file
    bool decompressFile(const std::string& inputFile, const std::string& outputFile) {
        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile) {
            std::cerr << "Cannot open input file\n";
            return false;
        }

        // Read original file size
        size_t originalSize;
        inFile.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));

        // Read frequency map
        std::unordered_map<unsigned char, unsigned> freqMap;
        size_t freqMapSize;
        inFile.read(reinterpret_cast<char*>(&freqMapSize), sizeof(freqMapSize));

        for (size_t i = 0; i < freqMapSize; ++i) {
            unsigned char ch;
            unsigned freq;
            inFile.read(reinterpret_cast<char*>(&ch), sizeof(ch));
            inFile.read(reinterpret_cast<char*>(&freq), sizeof(freq));
            freqMap[ch] = freq;
        }

        // Rebuild Huffman tree
        HuffmanNode* root = buildHuffmanTree(freqMap);
        generateCodes(root, "");

        // Read padding bits
        size_t paddingBits;
        inFile.read(reinterpret_cast<char*>(&paddingBits), sizeof(paddingBits));

        // Read and convert compressed data to bit string
        std::string bitString;
        unsigned char byte;
        while (inFile.read(reinterpret_cast<char*>(&byte), 1)) {
            for (int i = 7; i >= 0; --i) {
                bitString += ((byte >> i) & 1) ? '1' : '0';
            }
        }

        // Remove padding bits
        bitString = bitString.substr(0, bitString.length() - paddingBits);

        // Decompress
        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile) {
            std::cerr << "Cannot open output file\n";
            delete root;
            return false;
        }

        HuffmanNode* current = root;
        for (char bit : bitString) {
            current = (bit == '0') ? current->left : current->right;

            if (!current->left && !current->right) {
                outFile.write(reinterpret_cast<const char*>(&current->data), 1);
                current = root;
            }
        }

        // Output decompression info
        std::cout << "Decompressed file size: " << originalSize << " bytes\n";

        delete root;
        return true;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Usage:\n";
        std::cerr << "Compress: huffman -c -i <input_file> -o <output_file>\n";
        std::cerr << "Decompress: huffman -u -i <input_file> -o <output_file>\n";
        return 1;
    }

    HuffmanCoder coder;
    bool success = false;

    if (std::string(argv[1]) == "-c") {
        success = coder.compressFile(argv[3], argv[5]);
    } else if (std::string(argv[1]) == "-u") {
        success = coder.decompressFile(argv[3], argv[5]);
    } else {
        std::cerr << "Invalid operation. Use -c for compression or -u for decompression.\n";
        return 1;
    }

    return success ? 0 : 1;
}