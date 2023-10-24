// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12
#include "linkedlist.hpp"

int main() {
  List mylist;
  int inputValue;

  cout << "Enter a sequence of numbers (0 to stop):" << endl;
  while (true) {
    cin >> inputValue;

    if (inputValue == 0) {
      break;
    }

    mylist.insert(inputValue);
    mylist.print();
  }

  return 0;
}
int List::length() {
  int count = 0;
  if (head==nullptr)
    return 0;
  else
    return head->length();
};

int Node::length() {
  if (!has_next())
    return 1;
  else
    return 1+next->length();
};

/*
 * Iterative alternative
 * to recursive computation
 */
int List::length_iterative() {
  int count = 0;
  if (head!=nullptr) {
    auto current_node = head;
    while (current_node->has_next()) {
      current_node = current_node->nextnode(); count += 1;
    }
  }
  return count;
}; 

void Node::print() {
  cout << datavalue;
  if (next != nullptr) {
    cout << ", ";
    next->print();
  }
}

void List::print() {
  cout << "List: ";
  if (head != nullptr) {
    head->print();
  }
  cout << '\n';
}

void List::insert(int value) {
  if (head == nullptr || value < head->value()) {
    head = make_shared<Node>(value, head);
  } else {
    head->insert(value);
  }
}

void Node::insert(int value) {
  if (next == nullptr || value < next->value()) {
    shared_ptr<Node> new_node = make_shared<Node>(value, next);
    next = new_node;
  } else {
    next->insert(value);
  }
}
