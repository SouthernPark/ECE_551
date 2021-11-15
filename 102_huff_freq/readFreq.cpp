#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!

  //1. read the file
  std::ifstream input(fname, std::ifstream::in);

  //2. store the char
  uint64_t * res = new uint64_t[257]();
  //fill all the array
  for (size_t i = 0; i < 257; i++) {
    res[i] = 0;
  }

  int c;
  while (true) {
    c = input.get();
    if (c == -1) {
      break;
    }
    //add the requency count by 1
    res[c] += 1;
  }

  //if it is eof, then add res[256] 1
  if (input.eof()) {
    res[256] += 1;
  }

  input.clear();
  //close the filestream
  input.close();
  return res;
}
