#include <algorithm>
using namespace std;
#include "Tree.h"

class  Huffman {
    private:
        Tree t;
    public:
        void writeToFile(string fileName, string output);
        void encode(string inputfile);
        void toRemakeTree(bool isCharEncoding, char letter);
        void decode(string fileName);
};