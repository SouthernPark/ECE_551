#include "cyoa-step1.hpp"
class invalid_page : public std::exception {
 public:
  const char * what() { return "Invalid page\n"; }
};

class Story {
 private:
  std::vector<Page *> story;
  std::string dir;
  int current_page;
  //this function will read the first page
  //if not exit--> error and return
  void readFirst(std::stringstream & ss) {
    //open page1.txt (error if not exist)
    ss << dir << "/page1.txt";
    Page * page1 = new Page(ss.str());
    try {
      page1->read();
    }
    //page1 not exist
    catch (no_file & e) {
      std::cerr << e.what();
      std::cerr << "There is no page1.txt in " << dir << std::endl;
      exit(EXIT_FAILURE);
    }
    //add page
    story.push_back(page1);
  }

  //this function will read all the pages after the page1.txt inside the dir
  void readFollow(std::stringstream & ss) {
    for (size_t i = 2; true; i++) {
      //empty the ss
      ss.str("");
      ss << dir << "/page" << i << ".txt";
      Page * page = new Page(ss.str());
      try {
        page->read();
      }
      catch (no_file & e) {
        //catch remove the page
        delete page;
        page = NULL;
      }

      if (page != NULL) {
        story.push_back(page);
      }
      else {
        break;
      }
    }
  }

 public:
  Story() : dir(std::string("")), current_page(0) {}
  explicit Story(const char * directory) : dir(std::string(directory)), current_page(0) {}
  explicit Story(std::string directory) : dir(std::string(directory)), current_page(0) {}

  //copy constructor
  Story(const Story & rhs) {
    for (size_t i = 0; i < rhs.story.size(); i++) {
      Page * page = new Page(*rhs.story[i]);
      story.push_back(page);
    }
  }

  //assignment operator
  Story & operator=(const Story & rhs) {
    if (this != &rhs) {
      std::vector<Page *> temp;
      for (size_t i = 0; i < rhs.story.size(); i++) {
        Page * page = new Page(*rhs.story[i]);
        temp.push_back(page);
      }
      for (size_t i = 0; i < story.size(); i++) {
        delete story[i];
      }

      story = temp;
    }

    return *this;
  }

  ~Story() {
    for (size_t i = 0; i < story.size(); i++) {
      delete story[i];
    }
  }

  //this fucntion will read pages in the dir specified
  void read() {
    //2.get the dir of the story
    std::stringstream ss;
    Story story;
    readFirst(ss);
    //4. continuous reading all the page until no continuous page was found
    readFollow(ss);
  }

  //return true if the story is empty
  bool isEmpty() { return story.empty(); }
  //get page at story[index]
  Page * getPage(size_t index) { return story.at(index); }
  //add page
  void push_back(Page * page) { story.push_back(page); }
  size_t size() { return story.size(); }

  //set the directory of the story if not set when init
  void open(const char * str) {
    if (dir.compare("") == 0) {
      dir = std::string(str);
    }
    else {
      std::cout << "The page file has already associated with an address." << std::endl;
    }
  }
  void open(std::string str) {
    if (dir.compare("") == 0) {
      dir = std::string(str);
    }
    else {
      std::cout << "The page file has already associated with an address." << std::endl;
    }
  }

  //this function will check whether
  //the pages are valid
  void valid() throw(invalid_page) {
    //valid reference Every page that is referenced by a choice is valid
    referenceValid();
    //Every page (except page 1) is referenced by at least one *other* pages
    referByOther();
    //At least one page must be a WIN page and at least one page must be LOSE page
    win_lose_page();
  }

  //valid reference Every page that is referenced by a choice is valid
  void referenceValid() throw(invalid_page) {
    int size = (int)this->size();
    //all pages reference should within [1, size]
    for (size_t i = 0; i < story.size(); i++) {
      //get the choice number of the page
      std::vector<int> & choiceNum = story[i]->getChoiceNum();
      for (size_t j = 0; j < choiceNum.size(); j++) {
        int num = choiceNum[j];
        if (!(num >= 1 && num <= size)) {
          std::stringstream ss;
          ss << "Page reference: " << num << " in "
             << "page " << i + 1 << " is out of range\n";
          std::cerr << ss.str();
          throw(invalid_page());
        }
      }
    }
    return;
  }

  //Every page (except page 1) is referenced by at least one *other* pages
  void referByOther() throw(invalid_page) {
    //refer[i] will record whether page i-1 has been recorded
    size_t size = this->size();
    bool * refer = new bool[size]();
    for (size_t i = 0; i < size; i++) {
      refer[i] = false;
    }
    //go through all pages
    for (size_t i = 0; i < size; i++) {
      //get the choice number of the page
      std::vector<int> & choiceNum = story[i]->getChoiceNum();
      for (size_t j = 0; j < choiceNum.size(); j++) {
        //set refer[choiceNum[j]-1] to true
        refer[choiceNum[j] - 1] = true;
      }
    }

    //check whether refer[1...] is all true
    int not_refer = -1;
    for (size_t i = 1; i < size; i++) {
      if (refer[i] == false) {
        not_refer = i;
        break;
      }
    }
    delete[] refer;

    if (not_refer != -1) {
      std::stringstream ss;
      ss << "Page" << not_refer + 1 << "is not refered by other\n";
      std::cerr << ss.str();
      throw(invalid_page());
    }
  }

  void win_lose_page() throw(invalid_page) {
    bool win = false;
    bool lose = false;
    for (size_t i = 0; i < this->size(); i++) {
      if (story[i]->getWinLose() == 0) {
        lose = true;
      }
      else if (story[i]->getWinLose() == 1) {
        win = true;
      }

      if (win == true && lose == true) {
        return;
      }
    }

    std::cerr << "Needs one win page or losee page\n";
    throw(invalid_page());
  }

  int & getCurPage() { return this->current_page; }
  int getPageNum() { return story.size(); };
  std::vector<int> getPageChoices(int index) { return story[index]->getChoiceNum(); };
  int getWinLose(int index) { return story[index]->getWinLose(); }
};

//check whether choice is within [min, max]
bool validChoice(int choice, int min, int max) {
  if (choice >= 1 && choice <= max) {
    return true;
  }

  return false;
}

//this function will continuously get and check userinput
int getUserInput(int size) {
  std::string res;
  bool valid;
  int num = -1;
  do {
    std::getline(std::cin, res);
    //we may encounter a eof
    std::cin.clear();

    num = str_to_posint(res);
    valid = validChoice(num, 1, size);

  } while (!valid);

  return num;
}
