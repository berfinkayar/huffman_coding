#include "Huffman.h"

void Huffman::writeToFile(string fileName, string output){
    ofstream outputFile;
    outputFile.open(fileName);
    outputFile << output;
    outputFile.close();
}

void Huffman::encode(string inputfile){
    ifstream file(inputfile); //getting the string to encode
    string line;
    string input = "";
    while (getline(file, line)){
      input += line;
    }
    transform(input.begin(), input.end(), input.begin(), ::tolower); 

    unordered_map<char, int> frequencies; //keeping chars and frequencies in a map
    for (int i = 0; i<input.length(); i++){
      if (frequencies.find(input[i]) == frequencies.end()){
        frequencies.insert(make_pair(input[i], 1));
      }
      else {
        frequencies[input[i]]++;
      }
    }

    vector<pair<char, int> > v; //used vector pair to sort them
    unordered_map<char,int> :: iterator itr;
    for (itr=frequencies.begin(); itr!=frequencies.end(); itr++){
      v.push_back(make_pair(itr->first, itr->second));
    }

    struct sort_pred {
    bool operator()(const pair<int,int> &left, const pair<int,int> &right) {return left.second < right.second;}};
    sort(v.begin(), v.end(), sort_pred());

    string codes =""; //making the tree and encoding the leaf nodes
    t.makeTree(v);
    t.setCurrent();
    t.encode(t.current, codes);

    string encoded = "";
    encoded = t.getEncoded(input, encoded);
    writeToFile("tree.txt", t.storeTree());
    writeToFile("decode.txt", encoded);
    cout << encoded << endl;
}

void Huffman::toRemakeTree(bool isCharEncoding, char letter){
    vector<pair<char, string> > vec; //getting the encoding table from the file to remake the tree
    ifstream file("tree.txt");
    string str;
    while (getline(file, str)){
        vec.push_back(make_pair(str[0],str.substr(1,str.size()-1)));
    }
    t.remakeTree(vec);
    if (isCharEncoding){
        t.getCharacterEncoding(vec, letter);
    }
    else if (letter == 'l'){
        t.listTree(t.current, 0);
    }
}

void Huffman::decode(string fileName){
    string decoded = "";
    string encoded;
    ifstream inputfile(fileName); //getting the encoded string to decode
    getline(inputfile, encoded);
    t.decode(decoded, encoded);
    cout << decoded << endl;
}