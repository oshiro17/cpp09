#pragma once
#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include <iostream>
#include <list>
#include <vector>

// 関数プロトタイプ
unsigned long getTime();
unsigned long jacobsthal(unsigned long);

void PmergeMe(int *data, std::size_t size);

// Node クラス（int 型専用）
class Node {
private:
  bool _isLeaf;          // 葉ノードかどうかを示すフラグ
  union Value {          // 値を保持するためのユニオン
    int *leaf;           // 葉ノードの値
    Node *inner;         // 内部ノードのポインタ
  } _value;
  Node *_pair;           // ペアとなるノード

public:
  // コンストラクタ（int* を受け取る）
  explicit Node(int *value) : _isLeaf(true), _pair(nullptr) {
    _value.leaf = value;
  }

  // コンストラクタ（Node* を受け取る）
  explicit Node(Node *value) : _isLeaf(false), _pair(nullptr) {
    _value.inner = value;
  }

  // コピーコンストラクタ
  Node(Node const &rhs) : _isLeaf(rhs._isLeaf), _pair(rhs._pair) {
    if (rhs._isLeaf)
      _value.leaf = rhs._value.leaf;
    else
      _value.inner = rhs._value.inner;
  }

  // デストラクタ
  ~Node() {}

  // ペアが存在するかどうか
  bool hasPair() const {
    return _pair != nullptr;
  }

  // ペアを設定
  void push(Node *node) {
    _pair = node;
  }

  // ペアを取得して解除
  Node *pop() {
    Node *tmp = _pair;
    _pair = nullptr;
    return tmp;
  }

  // 代表値を取得
  int &getTypical() const {
    if (_isLeaf)
      return *_value.leaf;
    else
      return _value.inner->getTypical();
  }

  // 比較演算子
  bool operator<(Node const &rhs) const {
    return getTypical() < rhs.getTypical();
  }

  // 値を取得（int* 用）
  void getValue(int *&value) {
    value = _value.leaf;
  }

  // 値を取得（Node* 用）
  void getValue(Node *&value) {
    value = _value.inner;
  }
};

// データを出力する関数

// void printData(ConstIterator begin, ConstIterator end) {
//   if (begin != end) {
//     std::cout << *begin;
//     while (++begin != end)
//       std::cout << " " << *begin;
//   }
//   std::cout << std::endl;
// };

#endif
