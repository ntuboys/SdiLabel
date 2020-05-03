#include "linkedlist.h"
#include <string>
#include <vector>

namespace Tests {
// testing linked list fuctionality
bool linkedList() {
  LinkedList list;
  list.add("first"); // add elements
  list.add("second");
  if (!(list.pop() == "second") ||
      !(list.pop() == "first")) { // check if they were actually aded
    return false;
  }
  return true;
}
// testing the search algorithm
bool searchAlgorithm() {
  LinkedList list;
  list.add("first"); // add elements
  list.add("second");
  if (!(list.find("first") ==
        1)) { // see if the returned value is what was expected
    return false;
  }
  return true;
}
// sorting algorithm test
bool sortAlgorithm() {
  LinkedList list;
  list.add("first"); // add elements
  list.add("second");
  list.sort();
  if (!(list.find("first") == 0)) { // see if the elements are in expected order
    return false;
  }
  return true;
}
// integration test
bool intTest() {
  bool passed = true;
  LinkedList list;

  list.add("first"); // add elements
  list.add("second");
  if (!(list.pop() == "second") ||
      !(list.pop() == "first")) { // check if they were actually aded
    passed = false;
  }
  list.add("first");
  list.add("second");
  if (!(list.find("first") ==
        1)) { // see if the returned value is what was expected
    passed = false;
  }
  list.sort();
  if (!(list.find("first") == 0)) { // see if the elements are in expected order
    passed = false;
  }

  return passed;
}
} // namespace Tests

int main() {
  // if any of the tests failed return non-zero
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
