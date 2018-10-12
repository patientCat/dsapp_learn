#pragma once

#include <vector> 

#define BTNodePos(T) BTNode<T> *

using std::vector; 

template <typename T>
struct BTNode{
    BTNodePos(T) parent;
    vector<T> key; // 用数组来表示一组key值
    vector<BTNodePos(T) > child; // 孩子向量, 用数组来表示一组指针域

    // 构造函数只能用来创造根节点
    BTNode(): parent(nullptr) { child.insert(child.begin(), nullptr);}
    BTNode(T e, BTNodePos(T) lc = nullptr, BTNodePos(T) rc = nullptr )
    {
        parent = nullptr;
        key.insert(key.begin(), e);
        child.insert(child.begin(), lc);
        child.insert(child.begin() + 1, rc);
        if(lc) lc->parent = this;
        if(rc) rc->parent = this; 
    }
};
