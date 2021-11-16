#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  std::ifstream input(inFile, std::ifstream::in);
  //check the file exist
  if (!input.is_open()) {
    std::cerr << "The file does not exist\n";
    exit(EXIT_FAILURE);
  }
  // //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  int c;
  while (true) {
    //get the char
    c = input.get();
    if (c == -1) {
      break;
    }
    //get the proper bitstring
    BitString str = (*theMap.find(c)).second;
    //write to file
    bfw.writeBitString(str);
  }

  //dont forget to lookup 256 for the EOF marker, and write it out.
  if (input.eof()) {
    bfw.writeBitString((*theMap.find(256)).second);
  }

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
  input.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this

  //read the file and count the frequency
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);
  //build up the huffman tree
  Node * tree = buildTree(counts);
  delete[] counts;
  //build up the map according to the tree
  std::map<unsigned, BitString> theMap;
  BitString empty;
  tree->buildMap(empty, theMap);

  //read the file and compress it and write to output
  writeCompressedOutput(argv[1], argv[2], theMap);

  delete tree;

  return EXIT_SUCCESS;
}
