#include "cyoa-step1.hpp"

#include <iostream>

int main(int argc, char ** argv) {
  //we need one arguments for this program
  //which is the address of the page file
  if (!(argc == 2)) {
    std::cerr << "Sorry, please specify the file name" << std::endl;
    exit(EXIT_FAILURE);
  }

  //create the page by call the constructor
  //and give the constructor the file address
  Page page1(argv[1]);
  try {
    //try to read the page file
    page1.read();
  }
  catch (no_file & e) {
    //if some errors, report the error
    //and exit
    std::cerr << e.what();
    std::cerr << "The file:" << argv[1] << " can not open" << std::endl;
    exit(EXIT_FAILURE);
  }

  //then print the whole page
  page1.printPage();
}
