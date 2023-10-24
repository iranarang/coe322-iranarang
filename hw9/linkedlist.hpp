#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

class Node; // Forward definition
class List {
private:
  shared_ptr<Node> head{nullptr};

public:
  List() {};
  auto headnode() { return head; };
  void insert(int value);
  int length();
  int length_iterative();
  bool contains_value(int v);
  void print();
};

class Node {
private:
  int datavalue{0},datacount{0};
  shared_ptr<Node> next{nullptr};

public:
  Node() {};
  Node(int value, shared_ptr<Node> next = nullptr)
      : datavalue(value), next(next) {};
  int value() { return datavalue; };
  auto nextnode() { return next; };
  int length();
  int count() {
    return datacount; };
  bool has_next() {
    return next!=nullptr; };
  void insert(int value);
  void print();
};

#endif 