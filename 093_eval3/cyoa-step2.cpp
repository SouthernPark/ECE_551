#include "cyoa-step2.hpp"

int main(int argc, char ** argv) {
  //1.take the dir name (error if not exist)
  if (argc != 2) {
    std::cerr << "Need one argument\n";
    exit(EXIT_FAILURE);
  }

  //2. create story to hold all the pages
  Story story(argv[1]);
  //read all the pages into story
  try {
    story.read();
  }
  catch (no_file & e) {
    std::cerr << e.what();
    exit(EXIT_FAILURE);
  }

  //3. check if the story is valid
  try {
    story.valid();
  }
  catch (invalid_page & e) {
    std::cerr << e.what();
    exit(EXIT_FAILURE);
  }

  //4. build up the page dispaly process
  while (1) {
    //get the current page of the story
    //at the beginning it is set to 1
    //which is the first page
    int & cur = story.getCurPage();
    //a pointer point to the current page
    Page * cur_page = story.getPage(cur);
    //1. display the current page
    cur_page->printPage();
    //2. check win or lose page
    if (cur_page->getWinLose() != -1) {
      break;
    }
    //3. get the choice number inside current page
    std::vector<int> & choice_num = cur_page->getChoiceNum();

    //4. get user input and valid user input
    int userInput = getUserInput(choice_num.size());

    //6. update current page
    cur = choice_num[userInput - 1] - 1;
  }
}
