#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

//this template function will read the file and sort the file
//according to different file stream type

void read(std::istream & s, std::vector<std::string> & file) {
  std::string line;
  while (std::getline(s, line)) {
    file.push_back(line);
  }
}
std::ostream & operator<<(std::ostream & os, std::vector<std::string> v) {
  for (size_t i = 0; i < v.size(); i++) {
    os << v[i] << std::endl;
  }
  return os;
}
int main(int argc, char ** argv) {
  //create a list to hold the file
  std::vector<std::string> * lines = new std::vector<std::string>;
  std::vector<std::string> & file = *lines;
  //create a fstream to read from the file
  std::ifstream rfile;

  if (argc == 1) {
    //call std::cin to read to the file
    read(std::cin, file);
    //sort the file
    std::sort(file.begin(), file.end());
    //print
    std::cout << file;
  }
  else {
    //for every file we need to open and read it
    for (int i = 1; i < argc; i++) {
      char * filename = argv[i];
      //open the filestream
      rfile.open(filename, std::ifstream::in);
      //check whether the file is opened
      if (rfile.fail()) {
        std::cout << "The file " << filename << "Can not be open" << std::endl;
        return EXIT_FAILURE;
      }
      //call the function to read the file
      read(rfile, file);
      //sort the file
      std::sort(file.begin(), file.end());
      //print it put
      std::cout << file;
      //close the file
      rfile.close();
      //clear the vector
      file.clear();
    }

    //delete memory
    delete lines;
  }

  return EXIT_SUCCESS;
}
