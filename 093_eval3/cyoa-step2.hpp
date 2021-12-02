#include "cyoa-step1.hpp"

//exception class build for if there is some page
//that are invalid
class invalid_page : public std::exception {
 public:
  const char * what() { return "Invalid page\n"; }
};

//this class will all the pages under a directory
class Story {
 private:
  //vector to hold all the pages under a dir
  std::vector<Page *> story;
  //the name/address of the dir
  std::string dir;
  //what is the current page we are currently look
  int current_page;
  //this function will read the first page
  //if not page1.txt exit--> error and return
  void readFirst(std::stringstream & ss) {
    //open page1.txt (error if not exist)
    ss << dir << "/page1.txt";
    //create page object for page1.txt
    Page * page1 = new Page(ss.str());
    try {
      //try to read the page from os
      page1->read();
    }
    //page1 not exist
    catch (no_file & e) {
      //report error and exit
      std::cerr << e.what();
      std::cerr << "There is no page1.txt in " << dir << std::endl;
      exit(EXIT_FAILURE);
    }
    //add page1 to the story
    story.push_back(page1);
  }

  //this function will read all the pages
  //after the page1.txt inside the dir such as
  //page2.txt , page3.txt ..
  void readFollow(std::stringstream & ss) {
    for (size_t i = 2; true; i++) {
      //empty the string buffer
      ss.str("");
      //construct pagei.txt
      ss << dir << "/page" << i << ".txt";
      //create the page
      Page * page = new Page(ss.str());
      try {
        //read the page into the object from os
        page->read();
      }
      catch (no_file & e) {
        //we have read all the files
        //the current page is invalid
        //delete it to avoid memory leak
        delete page;
        page = NULL;
      }
      //add the valid pages to story
      if (page != NULL) {
        story.push_back(page);
      }
      else {
        //stop reading pages if we are at the end
        //of the story
        break;
      }
    }
  }

 public:
  //construcor
  Story() : dir(std::string("")), current_page(0) {}
  explicit Story(const char * directory) : dir(std::string(directory)), current_page(0) {}
  explicit Story(std::string directory) : dir(std::string(directory)), current_page(0) {}

  //copy constructor
  Story(const Story & rhs) {
    //copy all the pages to rhs
    //in page we do not have pointer staff as attribute
    //thus we do not need to deep copy page
    for (size_t i = 0; i < rhs.story.size(); i++) {
      Page * page = new Page(*rhs.story[i]);
      story.push_back(page);
    }
  }

  //assignment operator
  Story & operator=(const Story & rhs) {
    //assign this story to rhs if the are not pointer
    //to the same thing
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

  //destructor
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
  //normally we do not use this function if the dir has been
  //specified in constructor
  void open(const char * str) {
    if (dir.compare("") == 0) {
      dir = std::string(str);
    }
    else {
      std::cout << "The page file has already associated with an address." << std::endl;
    }
  }
  //the same function, but override the method to support
  //differnt kinds of parameters
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

  //this function will check whether the choice number inside each page
  //is valid
  //more specifically, we want to check whether the choice number
  //really points to [1, max_page_number]
  void referenceValid() throw(invalid_page) {
    //the size of the story is also the max
    //page number for the story
    int size = (int)this->size();
    //all pages reference should within [1, size]
    for (size_t i = 0; i < story.size(); i++) {
      //get the choice number of the page
      std::vector<int> & choiceNum = story[i]->getChoiceNum();
      for (size_t j = 0; j < choiceNum.size(); j++) {
        //check whether the page is withn [1, max page number]
        int num = choiceNum[j];
        if (!(num >= 1 && num <= size)) {
          //if the choice is point to some pages does not exist
          //report error and throw exception
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

  //this function will check :
  //for every page if it is referenced by other pages except
  //by itsef
  void referByOther() throw(invalid_page) {
    //refer[i] will record whether page i-1 has been refered
    size_t size = this->size();
    bool * refer = new bool[size]();
    //initially set refer[i] all to false
    for (size_t i = 0; i < size; i++) {
      refer[i] = false;
    }
    //go through all pages (pagei+1.txt)
    for (size_t i = 0; i < size; i++) {
      //get the choice number of the page
      std::vector<int> & choiceNum = story[i]->getChoiceNum();
      for (size_t j = 0; j < choiceNum.size(); j++) {
        //set refer[choiceNum[j]-1] to true
        //which means the page choiceNum[j] has been refered
        //also the choice can not be itself
        if (choiceNum[j] != (int)(i + 1)) {
          refer[choiceNum[j] - 1] = true;
        }
      }
    }

    //check whether refer[1...] is all true
    int not_refer = -1;
    //not_refer if teh first page we detected that
    //has not been pointed by other pages
    for (size_t i = 1; i < size; i++) {
      if (refer[i] == false) {
        not_refer = i;
        break;
      }
    }
    delete[] refer;
    //not_refer == -1, then it means there is no page
    //that is not refered by other pages
    if (not_refer != -1) {
      std::stringstream ss;
      //print out which page is not refered by others
      ss << "Page" << not_refer + 1 << "is not refered by other\n";
      std::cerr << ss.str();
      //throw exception
      throw(invalid_page());
    }
  }

  //this function will check whether there is at least one
  //WIN page and LOSE page in the story
  void win_lose_page() throw(invalid_page) {
    //win will record whether a win page occured
    bool win = false;
    //lose will record whetther a lise page occured
    bool lose = false;
    //loop through the pages
    for (size_t i = 0; i < this->size(); i++) {
      //if there is a lose page
      if (story[i]->getWinLose() == 0) {
        //set lose to true
        lose = true;
      }
      //if there is a win page
      //set win to true
      else if (story[i]->getWinLose() == 1) {
        win = true;
      }
      //return if there is one win page and lose page
      if (win == true && lose == true) {
        return;
      }
    }

    //otherwise report errors and throw exceptions
    std::cerr << "Needs one win page or losee page\n";
    throw(invalid_page());
  }
  //get the page that the story is currently displayed
  int & getCurPage() { return this->current_page; }
  //get how many pages the story has
  int getPageNum() { return story.size(); };
  //get ther choice number for a paricular page of the story
  std::vector<int> getPageChoices(int index) { return story[index]->getChoiceNum(); };
  //get win or lose for a paricular page of the story
  int getWinLose(int index) { return story[index]->getWinLose(); }
};

//check whether choice is within [min, max]
bool validChoice(int choice, int min, int max) {
  if (choice >= 1 && choice <= max) {
    return true;
  }

  //print some messages
  std::cout << "That is not a valid choice, please try again\n";

  return false;
}

//this function will continuously get and check userinput
int getUserInput(int size) {
  std::string res;
  bool valid;
  int num = -1;
  do {
    //get the user input and store it inside res
    std::getline(std::cin, res);
    //we may encounter a eof, thus clear the state
    std::cin.clear();

    //convert the string input t oa positive number
    //returns -1 if the the string is not a positive number
    num = str_to_posint(res);
    //check whether the input is valid
    //if the input is not valid
    valid = validChoice(num, 1, size);
    //if it is not valid, continuously read the input until

  } while (!valid);

  return num;
}
