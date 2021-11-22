#include "cyoa-step2.hpp"
#define MAX 2147483647
#include <assert.h>

#include <map>
#include <queue>

class StoryGraph {
  class Node {
   private:
    //initially the depth of the page will be MAX
    int depth;
    bool visited;
    int win_or_lose;

   public:
    Node() : depth(MAX), visited(false), win_or_lose(-1) {}
    Node(int winLose) : depth(MAX), visited(false), win_or_lose(winLose) {}

    //getters and setters for the node attribute

    int & getDepth() { return depth; }
    int getWinLose() { return win_or_lose; }
    void setDepth(int dep) { depth = dep; }
    void setWinLose(int wl) { win_or_lose = wl; }
    bool getVisited() { return visited; }
    void setVisited(bool vis) { visited = vis; }
  };

  int nodes_num;

  //use ajacentry matrix to implement the graph
  std::map<int, std::vector<int> > ajaList;
  //page number to Node pointer
  std::map<int, Node *> graph;

 public:
  StoryGraph(Story & story) : nodes_num(story.getPageNum()) {
    //build up the graph according to the story
    //for each node
    for (int i = 0; i < nodes_num; i++) {
      //fill its ajacency list
      ajaList[i + 1] = story.getPageChoices(i);
      //create the node
      graph[i + 1] = new Node(story.getWinLose(i));
    }
  }

  //destructor
  ~StoryGraph() {
    for (int i = 0; i < nodes_num; i++) {
      delete graph[i + 1];
    }
  }

  //get ajacency
  std::vector<int> & getChildren(int index) { return ajaList[index]; }

  //isVisited
  bool isVisited(int index) { return graph[index]->getVisited(); }
  //get depth
  int & depth(int index) { return graph[index]->getDepth(); }

  //get win_or_lose
  int getWinLose(int index) { return graph[index]->getWinLose(); }

  //set visited
  void setVisited(int index, bool vis) { graph[index]->setVisited(vis); }
  //set the depth of the index page
  void setDepth(int index, int dep) { graph[index]->setDepth(dep); };

  //get how many nodes
  int getNodeNum() { return nodes_num; }

  int getDepth(int index) { return graph[index]->getDepth(); };

  //get all the neighbour
  std::vector<int> & getAllNei(int index) { return ajaList[index]; }

  void setAllUnvisited() {
    for (int i = 0; i < nodes_num; i++) {
      graph[i + 1]->setVisited(false);
    }
  }

  //using dfs to get the story depth of all the story
  void printStoryDepth() {
    //key->page num, val->story depth
    std::map<int, int> storyDepth;
    //clear the visited flag
    setAllUnvisited();
    //set the page depth of page1 as 0
    setDepth(1, 0);

    //create thr queue
    std::queue<int> q;

    //set the first page as visited and push into queue
    setVisited(1, true);
    q.push(1);
    while (!q.empty()) {
      //1. pop from q
      int node = q.front();
      q.pop();
      //2. get all the neighbours that are not visited
      std::vector<int> & neighbours = getAllNei(node);
      for (size_t i = 0; i < neighbours.size(); i++) {
        if (!isVisited(neighbours[i])) {
          //3. update the story depth of the neighbour
          setDepth(neighbours[i], getDepth(node) + 1);
          //4. mark as visited and push into queue
          setVisited(neighbours[i], true);
          q.push(neighbours[i]);
        }
      }
    }

    //print out the result
    for (int i = 0; i < nodes_num; i++) {
      int depth = getDepth(i + 1);
      if (depth != MAX) {
        std::cout << "Page " << i + 1 << ":" << getDepth(i + 1) << std::endl;
      }
      else {
        std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
      }
    }
    //reset visited
    setAllUnvisited();
  }

  void findWinPath() {
    //reset the visited attribute of the graph
    this->setAllUnvisited();

    //create an array to hold the path
    std::vector<std::pair<int, int> > path;
    backtrack(1, path);

    this->setAllUnvisited();
  }

  void backtrack(int node, std::vector<std::pair<int, int> > path) {
    //the node is win
    if (getWinLose(node) == 1) {
      //print out the path
      for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i].first << "(" << path[i].second << ")"
                  << ",";
      }
      std::cout << node << "(win)" << std::endl;
      return;
    }
    //the node is lose
    else if (getWinLose(node) == 0) {
      return;
    }

    //else node is choice node mark as visited
    this->setVisited(node, true);
    //find the neighbours
    std::vector<int> & neigh = this->getAllNei(node);
    for (size_t i = 0; i < neigh.size(); i++) {
      //avoid visited node
      if (this->isVisited(neigh[i])) {
        continue;
      }
      //push your choice into path
      path.push_back(std::pair<int, int>(node, i + 1));
      //DFS to next node
      backtrack(neigh[i], path);
      //remove the last node for backtrack
      path.pop_back();
    }
    //set as unvisted backtrack
    this->setVisited(node, false);
    return;
  }
};
