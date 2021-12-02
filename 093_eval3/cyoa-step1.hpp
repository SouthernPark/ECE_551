#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
class no_file : public std::exception {
 public:
  std::string what() {
    std::string mess("File not found exception\n");
    return mess;
  }
};

//this function is used to classify navigation into 4 types;
//return 1 for "WIN"
//return 2 for "LOSE"
//return 3 for "choices" or invalid input
int nav_classify(std::string str);

//this function will check whether the choice in the navigation
//is well formated
//return 1 for well formated
//else return 0
int check_choices(std::string str);

//this function will convert a string to a positive number
//return -1 if unconvertable
//else return the number
int str_to_posint(std::string str);

class Page {
 private:
  //navigation of the page, store the numbers for
  //which page to jump
  std::vector<int> choices_num;
  //store the text after each choice number
  std::vector<std::string> choice_content;
  //text of the pages, store the lines of the txt
  std::vector<std::string> text;

  //if win this will be set as 1, lose 0, else -1
  int win_or_lose;

  //the address/name of the page file
  std::string file;
  //this function will read and store the navigation part
  //of the page
  void readNav(std::ifstream & ifs) {
    //1. read the first line
    std::string line;
    std::getline(ifs, line);
    if (ifs.eof()) {
      std::cerr << "Nothing in the page" << std::endl;
      exit(EXIT_FAILURE);
    }

    //2. check the navigation is choice or "WIN", "LOSE"
    int cat = nav_classify(line);
    //cat == 1, then it is a page for WIN
    if (cat == 1) {
      win_or_lose = 1;
      //read one more line
      std::getline(ifs, line);
    }
    //cat == 2, then it is a page for LOSE
    else if (cat == 2) {
      win_or_lose = 0;
      //read one more line
      std::getline(ifs, line);
    }
    else {
      //otherwise, cat = 3, it is a page whose navigations
      //are all choices
      do {
        //check whether the choice line is valid
        //if valid returns the choice number
        //else return 0
        int val_bit = check_choices(line);

        if (val_bit == 0) {
          //if the choice line is not valid
          //report error and exit
          std::cerr << "The choice is not valid" << std::endl;
          exit(EXIT_FAILURE);
        }

        //then get the choice number and choice content
        //add the choice number
        choices_num.push_back(val_bit);

        //read the content after the ":"
        int first_colon = line.find(':');
        choice_content.push_back(
            line.substr(first_colon + 1, line.length() - first_colon - 1));
        //read the next line
        std::getline(ifs, line);
        //break if we find a line start with '#'
        //which is the end of the navigation
        if (line.at(0) == '#') {
          break;
        }
      } while (!ifs.eof());
    }

    //if the next line after nav is not '#'
    //the page is in wrong format
    if (line.length() <= 0 || line.at(0) != '#') {
      std::cerr << "We do not find a # to seperate betweeen nav and text" << std::endl;
      exit(EXIT_FAILURE);
    }
    //if the status of ifstream is not correct after reading navigation
    //then report error and exit
    if (ifs.bad() || ifs.fail()) {
      std::cerr << "Sorry there is some problem when reading the nav" << std::endl;
      exit(EXIT_FAILURE);
    }

    //clear all the bad status
    ifs.clear();
  }

  //this function will read the text content into
  //the text vector
  void readText(std::ifstream & ifs) {
    std::string line;
    while (!std::getline(ifs, line).eof()) {
      //push each line into the text vector
      text.push_back(line);
    }
  }

 public:
  //constructors
  Page() : win_or_lose(-1), file(std::string("")) {}
  explicit Page(const char * address) : win_or_lose(-1), file(std::string(address)) {}
  explicit Page(std::string address) : win_or_lose(-1), file(address) {}

  //this function will read the whole page including the navigation part
  //and the text part
  void read() throw(no_file) {
    //open the input file stream with address
    std::ifstream input_stream(file.c_str(), std::ifstream::in);
    //check whether the file can open or not
    if (!input_stream.is_open()) {
      throw(no_file());
      //std::cerr << "The file:" << file << " can not open" << std::endl;
      //exit(EXIT_FAILURE);
    }
    std::ifstream & ifs = input_stream;

    //read the navigation
    readNav(ifs);
    //read the text
    readText(ifs);
    //close the stream
    ifs.close();
  }

  //this function will reset the file address
  //if the page object is built using default constructor
  void open(const char * str) {
    if (file.compare("") == 0) {
      file = std::string(str);
    }
    else {
      std::cout << "The page file has already associated with an address." << std::endl;
    }
  }

  //override the open method for differnt parameter input
  void open(std::string str) {
    if (file.compare("") == 0) {
      file = std::string(str);
    }
    else {
      std::cout << "The page file has already associated with an address." << std::endl;
    }
  }

  //this function will print the navigation part
  void printNav() {
    //go through the choice content
    for (size_t i = 0; i < choices_num.size(); i++) {
      //print the selection number
      std::cout << " " << i + 1 << ". ";
      //print the choice content
      std::cout << choice_content[i] << std::endl;
    }
  }

  //print the text part of the page
  void printText() {
    for (size_t i = 0; i < text.size(); i++) {
      std::cout << text[i] << std::endl;
    }
  }

  //print all the content of the page
  //including the navigation part and the choice part
  void printPage() {
    //check WIN, LOSE, or choice page
    if (win_or_lose == -1) {
      //print choice page
      //print the text
      printText();
      //print a blank line, message, blank line
      std::cout << std::endl << "What would you like to do?" << std::endl << std::endl;
      //print choices
      printNav();
    }
    else {
      //print WIN/LOSE page
      printText();
      if (win_or_lose == 1) {
        //print WIN mess
        std::cout << std::endl << "Congratulations! You have won. Hooray!" << std::endl;
      }
      else if (win_or_lose == 0) {
        //print LOSE mess
        std::cout << std::endl
                  << "Sorry, you have lost. Better luck next time!" << std::endl;
      }
      else {
        std::cout << "win_or_lose flag is not set correctly" << std::endl << std::endl;
      }
    }
  }

  //getters for the choice number of this page
  std::vector<int> & getChoiceNum() { return this->choices_num; }
  //getters for the win lose status
  int getWinLose() { return win_or_lose; }
};

//this function is used to classify navigation into 4 types;
//return 1 for "WIN"
//return 2 for "LOSE"
//return 3 for "choices"
//return 4 for wrong navigation line
int nav_classify(std::string str) {
  //firstly check win
  if (str.compare("WIN") == 0) {
    return 1;
  }
  //then check lose
  else if (str.compare("LOSE") == 0) {
    return 2;
  }
  //other wise it is choice page
  return 3;
}

//this function will check whether the choice in the navigation
//is well formated
//return number for well formated
//else return 0
int check_choices(std::string str) {
  //find the first colon
  size_t first_colon = str.find(':');
  //if there is no :, then invalid choice
  if (first_colon == std::string::npos) {
    return 0;
  }

  //check the elements before first_colon is a >0 positive integer or not
  //using string stream
  std::stringstream ss;

  int choice_number = str_to_posint(str.substr(0, first_colon));
  if (choice_number == -1) {
    //std::cerr << "The choice number is not a positive number " << std::endl;
    return 0;
  }

  return choice_number;
}

//this function will convert a string to a positive number
//return -1 if unconvertable
//else return the number
int str_to_posint(std::string str) {
  //firstly check the length of the str
  if (str.length() <= 0) {
    return -1;
  }

  //convert str to char
  char * c_str = new char[str.length() + 1];
  for (size_t i = 0; i < str.length(); i++) {
    c_str[i] = str.at(i);
  }

  c_str[str.length()] = '\0';

  char * first_invalid = NULL;
  int num = strtol(c_str, &first_invalid, 10);

  //check the whether the first_invalid is '\0' or not
  if (*first_invalid != '\0') {
    delete[] c_str;
    return -1;
  }
  //we can not have choice number <= 0
  if (num <= 0) {
    delete[] c_str;
    return -1;
  }
  delete[] c_str;
  return num;
}
