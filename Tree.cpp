#include "Tree.h"

Tree::Tree(){
    head = NULL;
    tail = NULL;
    size = 0;
}

void Tree::makeTree(vector<pair<char, int> > &v){
    //making a linked list from the vector pair since we have to merge two smallest nodes 
    //and insert the merged node in order and keep doing it until we only have the root
    for (int i=0; i<v.size();i++){
        Node* temp = new Node();
        temp->character = v[i].first;
        temp->frequency = v[i].second;
        if (head == NULL){
            head = tail = temp;
            size = 1;
        }
        else {
            tail->next = temp;
            temp->prev = tail;
            tail = tail->next;
            size++;
        }
    }

    while (size > 1){  //now building the tree from the linked list
        Node* temp = new Node();
        temp->character = '\0';
        temp->frequency = head->frequency+head->next->frequency;
        temp->left = head;
        temp->right = head->next;
        head = head->next->next;
        size -= 2;
        temp->left->next = temp->right->next = NULL;

        if (head == NULL){
            head = tail = temp; //if linked list is empty
        }
        else if (temp->frequency <= head->frequency){
            temp->next = head; //if frequency is smaller than all elements
            head->prev = temp;
            head = temp;
        }
        else if (temp->frequency >= tail->frequency){
            tail->next = temp; //if frequency is bigger than all elements
            temp->prev = tail;
            tail = temp;
        }
        else {
            Node* itr = new Node();
            itr = head->next;
            while (itr != NULL){
                if (temp->frequency <= itr->frequency){
                    itr->prev->next = temp;
                    temp->next = itr;
                    temp->prev = itr->prev;
                    itr->prev = temp;
                    break;
                }
                itr = itr->next;
            }
        }
        size++;
    }
}
    
void Tree::encode(Node* current, string code){ //inserting each letter's encodings into a map
    if (current->left != NULL){
        encode(current->left, code+ "0");
    }
    if (current->right != NULL){
        encode(current->right, code+ "1");
    }
    if (current->character != '\0'){
        map.insert(make_pair(current->character,code));
    }
}
  
void Tree::decode(string &decoded, string &encoded){ 
    for (int i=0; i<encoded.size(); i++){
        if (encoded[i] == '0'){
            current = current->left;
        }
        else if (encoded[i] == '1'){
            current = current->right;
        }
        if (current->character != '\0'){
            decoded += current->character;
            current = root;
        }
    }
}

string Tree::storeTree(){ //to store the tree after encoding, in order to remake it for other commands
    string stored = "";
    for (auto it : map){
        stored += it.first + it.second + "\n";
    }
    return stored;
}

string Tree::getEncoded(string &s, string &encoded){
    for (int i=0; i<s.size(); i++){
        unordered_map<char, string>::iterator it;
        for (it = map.begin(); it != map.end(); it++){
            if (s[i] == it->first){
                encoded += it->second;
                break;
            }
        }
    }
    return encoded;
}

void Tree::insert(int left, pair<char, string> element, int j){
    Node* which = left ? current->left : current->right;
    Node* temp = new Node();

    if (j == element.second.size()-1){
        temp->character = element.first;
        if (left) current->left = temp;
        else current->right = temp;
        current = root;
        return;
    }

    if (which == NULL){
        temp->character = '\0';
        if (left) current->left = temp;
        else current->right = temp;
    }

    current = left ? current->left : current->right;
}

void Tree::remakeTree(vector<pair<char, string> > &v){
    Node* tmp = new Node();
    root = tmp;
    root->character = '\0';
    current = root;

    for (int i=0; i<v.size(); i++){
        for (int j=0; j<v[i].second.size(); j++){
            if (v[i].second[j] == '0')
                insert(1, v[i], j);
            else if (v[i].second[j] == '1')
                insert(0, v[i], j);
        }
    }
}

void Tree::getCharacterEncoding(vector<pair<char, string> > &v, char character){
    string encoded = "";
    for (int i=0; i<v.size();i++){
        if (v[i].first == character){
            encoded = v[i].second;
            break;
        }
    }
    cout << encoded << endl;;
}

void Tree::listTree(Node* current, int distance){
    for (int i=0; i<distance;i++){
        cout << " |" ;
    }
    cout << "+-" << current->character << endl;
    if (current->left != NULL){
        distance++;
        listTree(current->left, distance);
    }
    distance--;
    if (current->right != NULL){
        distance++;
        listTree(current->right, distance);
    }
}
