#include <iostream>
#include <string>
#include <vector>
typedef struct Node {
  std::string data;
  Node *next = nullptr;
} Node;

class LinkedList {
private:
  Node *head;

public:
  LinkedList();
  ~LinkedList();
  void add(std::string);
  std::string pop();
  bool empty();
  void clear();
  int length();
  std::vector<std::string> *getAll();
  int find(std::string);
};
