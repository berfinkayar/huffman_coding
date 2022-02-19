#include <sstream>
#include <string.h>
#include "Huffman.h"

using namespace std;

int main(int argc, char** argv) {
  Huffman h;

  if (strcmp(argv[1],"-i")== 0 && strcmp(argv[3],"-encode") == 0){
    h.encode(argv[2]);
  }

  else if (strcmp(argv[1],"-i") == 0 && strcmp(argv[3],"-decode") == 0){
    h.toRemakeTree(0, 'i');
    h.decode(argv[2]);
  }

  else if (strcmp(argv[1],"-s") == 0){
    char c = *(argv[2]);
    h.toRemakeTree(1, c);
  }

  else if (strcmp(argv[1],"-l") == 0){
    h.toRemakeTree(0, 'l');
  }
}