#include "linkedlist.h"
#include <string>
#include <vector>

namespace Tests {
bool linkedList() {
  LinkedList list;
  list.add("first");
  list.add("second");
  if (!(list.pop() == "second") || !(list.pop() == "first")) {
    return false;
  }
  return true;
}
bool searchAlgorithm() {
  LinkedList list;
  list.add("first");
  list.add("second");
  if (!(list.find("first") == 1)) {
    return false;
  }
  return true;
}
bool sortAlgorithm() {
  LinkedList list;
  list.add("first");
  list.add("second");
  list.sort();
  if (!(list.find("first") == 0)) {
    return false;
  }
  return true;
}
bool intTest() {
  bool passed = true;
  LinkedList list;

  list.add("first");
  list.add("second");
  if (!(list.pop() == "second") || !(list.pop() == "first")) {
    passed = false;
  }
  list.add("first");
  list.add("second");
  if (!(list.find("first") == 1)) {
    passed = false;
  }
  list.sort();
  if (!(list.find("first") == 0)) {
    passed = false;
  }

  return passed;
}
} // namespace Tests

int main() {
  bool failed = false;
  if (!Tests::linkedList()) {
    std::cout << "Linked list test failed" << std::endl;
    failed = true;
  } else {
    std::cout << "Linked list test passed" << std::endl;
  }
  if (!Tests::searchAlgorithm()) {
    std::cout << "Search algorithm test failed" << std::endl;
    failed = true;
  } else {
    std::cout << "Search algorithm test passed" << std::endl;
  }
  if (!Tests::sortAlgorithm()) {
    std::cout << "Sort algorithm test failed" << std::endl;
    failed = true;
  } else {
    std::cout << "Sort algorithm test passed" << std::endl;
  }
  if (!Tests::intTest()) {
    std::cout << "Integration test failed" << std::endl;
    failed = true;
  } else {
    std::cout << "Integration test passed" << std::endl;
  }

  return failed;
}
