#include "cyoa-step1.hpp"

#include <iostream>

int main(int argc, char ** argv) {
  //test for no file
  if (!(argc == 2)) {
    std::cerr << "Sorry, please specify the file name" << std::endl;
    exit(EXIT_FAILURE);
  }

  Page page1(argv[1]);
  page1.read();
  page1.printPage();
  //page1.printText();
  //int num = str_to_posint(std::string("0"));
  //std::cout << num << std::endl;
}
