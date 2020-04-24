#include "linkedlist.h"

// constructor
LinkedList::LinkedList() { head = nullptr; }

// destructor
LinkedList::~LinkedList() {
  Node *next = head;
  while (next) {
    Node *deleteMe = next;
    next = next->next;
    delete deleteMe;
  }
}

LinkedList &LinkedList::operator=(const LinkedList &list) {
  head = list.head;
  return *this;
}

// add new string
void LinkedList::add(std::string val) {
  Node *n = new Node();
  n->data = val;
  n->next = head;
  head = n;
}

// remove first element and return it
std::string LinkedList::pop() {
  Node *n = head;
  std::string ret = n->data;
  head = head->next;
  delete n;
  return ret;
}

// returns true if list is empty, false otherwise
bool LinkedList::empty() { return !head; }

// removes all elements from the list
void LinkedList::clear() {
  Node *next = head;
  while (next) {
    Node *deleteMe = next;
    next = next->next;
    delete deleteMe;
  }
  head = nullptr;
}

// returns the number of elements in the list
int LinkedList::length() {
  int counter = 0;
  if (head) {
    Node *next = head;
    while (next) {
      next = next->next;
      counter++;
    }
  }
  return counter;
}

// returns a pointer to a vector cointaining all elements
std::vector<std::string> *LinkedList::getAll() {
  std::vector<std::string> *ret = new std::vector<std::string>();
  if (head) {
    Node *next = head;
    while (next) {
      ret->push_back(next->data);
      next = next->next;
    }
  }
  return ret;
}

void LinkedList::sort() {
  std::vector<std::string> list;

  if (head) {
    Node *next = head;
    while (next) {
      list.push_back(next->data);
      next = next->next;
    }
  }

  if (list.empty()) {
    return;
  }

  bool changed;
  do {
    changed = false;
    for (int i = 0; i < list.size() - 1; i++) {
      std::string left = list[i];
      std::string right = list[i + 1];
      int length =
          (left.length() > right.length() ? right.length() : left.length());

      for (int j = 0; j < length - 1; j++) {
        if (left[j] == right[j])
          continue;
        if (left[j] > right[j]) {
          changed = true;
          std::string temp;
          list[i] = right;
          list[i + 1] = left;
          break;
        } else {
          break;
        }
      }
    }
  } while (changed);

  clear();

  for (int i = list.size(); i-- != 0;) {
    add(list[i]);
  }

  return;
}

// returns index of the first occurance of passed string
int LinkedList::find(std::string what) {
  if (head) {
    Node *next = head;
    int counter = 0;
    while (next) {
      if (next->data == what)
        return counter;
      next = next->next;
      ++counter;
    }
  }
  return -1;
}
