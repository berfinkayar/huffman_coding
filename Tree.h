#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <fstream>

using namespace std;

class Tree {
    private:
        struct Node {
        char character;
        int frequency;
        Node* left;
        Node* right;
        Node* next;
        Node* prev;
        };
        int size;
        Node* head;
        Node* tail;
        Node* root;
        unordered_map<char, string> map;
    public:
        Tree();
        Node* current;
        void makeTree(vector<pair<char, int> > &v);
        void encode(Node* current, string code);
        void decode(string &decoded, string &encoded);
        void setCurrent(){current = head;}
        string storeTree();
        string getEncoded(string &s, string &encoded);
        void insert(int left, pair<char, string> element, int j);
        void remakeTree(vector<pair<char, string> > &v);
        void getCharacterEncoding(vector<pair<char, string> > &v, char character);
        void listTree(Node* current, int distance);
};