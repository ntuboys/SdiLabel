#include "linkedlist.h"

LinkedList::LinkedList() { head = nullptr; }
LinkedList::~LinkedList() {
  Node *next = head;
  while (next) {
    Node *deleteMe = next;
    next = next->next;
    delete deleteMe;
  }
}
void LinkedList::add(std::string val) {
  Node *n = new Node();
  n->data = val;
  n->next = head;
  head = n;
}
std::string LinkedList::pop() {
  Node *n = head;
  std::string ret = n->data;
  head = head->next;
  delete n;
  return ret;
}
bool LinkedList::empty() { return !head; }
void LinkedList::clear() {
  Node *next = head;
  while (next) {
    Node *deleteMe = next;
    next = next->next;
    delete deleteMe;
  }
  head = nullptr;
}
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
