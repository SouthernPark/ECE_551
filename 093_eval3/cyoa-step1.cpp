#include "cyoa-step1.hpp"

#include <iostream>

int main(int argc, char ** argv) {
  //test for no file
  Page page1("story1/page1.txt");
  page1.read();
  page1.printNav();
  //int num = str_to_posint(std::string("0"));
  //std::cout << num << std::endl;
}
