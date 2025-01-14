#pragma once
#ifndef __PMERGEME_HPP__
#define __PMERGEME_HPP__

#include <iostream>
#include <list>
#include <vector>

#include <iostream>

// Node クラスの定義
class Node {
public:
    int n;       // 値を格納するメンバ変数
    int* pop;   // 次の Node のアドレスを格納するメンバ変数

    // コンストラクタ
    // 引数 val を n に設定し、pop は nullptr に初期化する
    Node(int val)
        : n(val), pop(nullptr)
    {
    }
};

#endif // NODE_HPP
