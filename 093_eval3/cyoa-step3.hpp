#include "cyoa-step2.hpp"
#define MAX 2147483647
#include <assert.h>

#include <map>
#include <queue>
#include <set>

//this class will store the story as a graph
//node is the page, connectiong of the node is the choices
//between pages
class StoryGraph {
  //inner class for node
  class Node {
   private:
    //initially the depth of the page will be MAX
    //depth of the node
    int depth;
    //whether the node has been visited
    bool visited;
    //whether this node represent a win page or lose page
    int win_or_lose;

   public:
    //constructors
    Node() : depth(MAX), visited(false), win_or_lose(-1) {}
    Node(int winLose) : depth(MAX), visited(false), win_or_lose(winLose) {}

    //getters and setters for the node attribute
    //get the depth of this node in the graph
    int & getDepth() { return depth; }
    //get win or lose of this node
    int getWinLose() { return win_or_lose; }
    //set the depth of this node
    void setDepth(int dep) { depth = dep; }
    //set win or lose of this node
    void setWinLose(int wl) { win_or_lose = wl; }
    //get whether this node is visited or not
    bool getVisited() { return visited; }
    //set the visited status of this node
    void setVisited(bool vis) { visited = vis; }
  };

  //how many nodes in this graph
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
  std::vector<std::pair<int, int> > getAllUniqueNei(int index) {
    //get all the neighbours of the node
    std::vector<int> & neigh = ajaList[index];
    //<page_num, choice_num>
    std::vector<std::pair<int, int> > pageToChoice;
    //this hash set will record whether page has been counted already
    std::set<int> uniquePage;
    for (size_t i = 0; i < neigh.size(); i++) {
      //if the page is not been recorded
      if (uniquePage.count(neigh[i]) == 0) {
        //push it to pageToChoice
        pageToChoice.push_back(std::pair<int, int>(neigh[i], i + 1));
        uniquePage.insert(neigh[i]);
      }
      //if the page has been recorded, then we do not add it again
    }

    return pageToChoice;
  }
  //this function will get all the neighbours of a node
  std::vector<int> & getAllNei(int index) { return ajaList[index]; }

  //this function will set all the node as un-visited
  void setAllUnvisited() {
    for (int i = 0; i < nodes_num; i++) {
      graph[i + 1]->setVisited(false);
    }
  }

  //this fuction will using dfs to
  //get the story depth of all the story
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
    //find all paths to win form node 1
    backtrack(1, path);
    //after that set all nodes as unvisited
    this->setAllUnvisited();
  }
  //this function will use backtracking algorithm to find all
  //all the possible paths to the win from the specified node
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
    //get all the neighbour (represented as <page_num, choice_num>)
    std::vector<std::pair<int, int> > neigh = this->getAllUniqueNei(node);
    for (size_t i = 0; i < neigh.size(); i++) {
      //avoid visited node
      if (this->isVisited(neigh[i].first)) {
        continue;
      }
      //push your choice into path
      path.push_back(std::pair<int, int>(node, neigh[i].second));
      //DFS to next node
      backtrack(neigh[i].first, path);
      //remove the last node for backtrack
      path.pop_back();
    }
    //set as unvisted backtrack
    this->setVisited(node, false);
    return;
  }
};
