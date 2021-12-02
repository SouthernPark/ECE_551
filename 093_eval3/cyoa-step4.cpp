#include "cyoa-step3.hpp"

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

  //4.construct the graph
  StoryGraph graph(story);
  //5. find and print all the win path
  graph.findWinPath();
}
