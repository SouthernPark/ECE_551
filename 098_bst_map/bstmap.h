#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  //create node class as inner class
  class Node {
   public:
    //what value should the node store?
    K key;
    V val;
    Node * left;
    Node * right;
    //constructor
    Node() : left(NULL), right(NULL) {}
    Node(K _key, V _val) : key(_key), val(_val), left(NULL), right(NULL) {}
    Node(K _key, V _val, Node * _left, Node * _right) :
        key(_key),
        val(_val),
        left(_left),
        right(_right) {}
    //destructor
    ~Node() {}
  };
  //what shoud this tree have ? -- (a pointer to the root node)
  Node * root;

  //delete the tree using post order traversal
  static void deleteTree(Node * _root) {
    if (_root == NULL) {
      return;
    }

    //delete the left subtree
    deleteTree(_root->left);
    //delete the right subtree
    deleteTree(_root->right);

    //finally the root
    delete _root;

    return;
  }

  static void preorder(Node * _root) {
    if (_root == NULL) {
      return;
    }
    std::cout << "key:" << _root->key << std::endl;
    //std::cout << "value:" << _root->val << std::endl;
    preorder(_root->left);
    preorder(_root->right);
  }

  //this function will return a copied tree from _root
  static Node * copy_tree(Node * _root) {
    //copy the root
    Node * res = new Node(_root->key, _root->val);
    //copy the left-sub tree
    res->left = copy_tree(_root->left);
    //copy the right-sub tree
    res->right = copy_tree(_root->right);
    //return the created tree
    return res;
  }

 public:
  //implement constructor
  BstMap() : root(NULL) {}
  //implement copy constructor
  BstMap(const BstMap & rhs) : root(NULL) {
    //create the copied tree
    root = copy_tree(rhs.root);
  }

  //implement assignment operator
  BstMap & operator=(const BstMap & rhs) {
    if (&rhs != this) {
      Node * temp = copy_tree(rhs.root);
      //then delete the original tree
      delete_tree(this->root);
      root = temp;
    }
    return *this;
  }

  BstMap & operator=(const BstMap & rhs) const {
    if (&rhs != this) {
      Node * temp = copy_tree(rhs.root);
      //then delete the original tree
      delete_tree(this->root);
      root = temp;
    }
    return *this;
  }

  //implement add
  virtual void add(const K & key, const V & value) {
    //implement using Node **
    Node ** cur = &root;
    //find the box we want to change
    while (*cur != NULL) {
      //find the node with key
      if ((*cur)->key == key) {
        break;
      }

      if (key < (*cur)->key) {
        //go to the left
        cur = &((*cur)->left);
      }
      else {
        //go to the right
        cur = &((*cur)->right);
      }
    }

    //check whether we find a node with key or not
    if (*cur == NULL) {
      //do not have a key value pair
      *cur = new Node(key, value, NULL, NULL);
    }
    else {
      //find a key value pair
      //just change the value
      (*cur)->val = value;
    }
  }

  //implement lookup
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    //implement using Node **
    Node * const * cur = &root;
    //find the box we want to change
    while (*cur != NULL) {
      //find the node with key
      if ((*cur)->key == key) {
        return (*cur)->val;
      }

      if (key < (*cur)->key) {
        //go to the left
        cur = &((*cur)->left);
      }
      else {
        //go to the right
        cur = &((*cur)->right);
      }
    }

    //check whether we find a node with key or not
    if (*cur == NULL) {
      throw std::invalid_argument("We do not find the value according to the key\n");
    }

    return (*cur)->val;
  }
  //implement remove
  virtual void remove(const K & key) {
    //find the node we want to remove
    Node ** cur = &root;
    while (*cur != NULL) {
      //find the node with key
      if ((*cur)->key == key) {
        break;
      }

      if (key < (*cur)->key) {
        //go to the left
        cur = &((*cur)->left);
      }
      else {
        //go to the right
        cur = &((*cur)->right);
      }
    }

    //does not find the node
    if (*cur == NULL) {
      return;
    }

    //check whether the node is single linked list ot not
    if ((*cur)->left == NULL || (*cur)->right == NULL) {
      if ((*cur)->left == NULL) {
        Node * temp = *cur;
        *cur = temp->right;
        delete temp;
      }
      else {
        Node * temp = *cur;
        *cur = temp->left;
        delete temp;
      }
    }
    //else the node we want to delete has two childs
    else {
      //sink the node down
      //go right once
      Node ** temp = &((*cur)->right);
      //we want *temp points at the node we want to swap
      while ((*temp)->left != NULL) {
        //go to the left
        temp = &((*temp)->left);
      }
      //change key val of temp with cur
      (*cur)->key = (*temp)->key;
      (*cur)->val = (*temp)->val;
      //remove the temp
      Node * rm = *temp;
      *temp = (*temp)->right;
      delete rm;
    }
  }

  //implement destructor
  virtual ~BstMap() {
    //delete tree using post order traveral
    deleteTree(this->root);
  }

  void print_tree() { preorder(root); }
};
