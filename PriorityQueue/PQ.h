#pragma once

#include <vector> 
#include <iterator> 

// 判断秩i，或者说节点i是否在n节点的堆中
#define InHeap(n, i) (((i) > -1) && ((i) < (n)))
// 获取父节点的秩
#define Parent(i) (((i) - 1) >> 1)
// 获取左孩子节点的秩
#define LChild(i) (1 + ((i) << 1))
// 获取右孩子节点的秩
#define RChild(i) (((i) + 1) << 1)
// 判断父亲有父亲节点
#define ParentValid(i) ((i) > -1)
// 判断存在左孩子节点
#define LChildValid(n, i) (InHeap((n), LChild(i)))

using std::vector;

using Rank = int;
template <typename T>
class PriorityQueue 
{ 
public: 
    PriorityQueue () = default;
    PriorityQueue (typename vector<T>::iterator begin,  typename vector<T>::iterator end)
    {
        std::copy(begin, end, back_inserter(_data));
        heapify(size());
    }

    // 按照优先级次序插入词条
    void insert(T);
    // 取出优先级最高的词条
    T getMax();
    // 删除优先级最高的词条
    T delMax();

    size_t size()const {   return _data.size();    }
protected:
    // 下滤 将秩为i的元素在节点为n的堆下滤
    Rank percolateDown(Rank n, Rank i);
    // 优化版本下滤
    Rank percolateDown2(Rank n, Rank i);
    // 上滤 将秩为i的元素上滤
    Rank percolateUp(Rank i);
    // 优化版本上滤
    Rank percolateUp2(Rank i);
    // 建堆
    void heapify(Rank n); // Floyd 建堆算法 
private: 
    // 底层实现采用向量的方式
    vector<T>     _data;
};  

template <typename T>
T
PriorityQueue<T>::getMax()
{
    return _data[0];
} 

template <typename T>
void
PriorityQueue<T>::insert(T e)
{
    // 先插入到向量末尾
    _data.push_back(e);
    // 上滤
    percolateUp(_data.size() - 1);
} 

template <typename T>
Rank
PriorityQueue<T>::percolateUp(Rank i)
{
    while(ParentValid(i))
    {
        Rank j = Parent(i);
        if(_data[j] >= _data[i])
            break;
        std::swap(_data[i], _data(j));  // 这里可以再优化
        i = j;
    }
    return i;
} 

template <typename T>
Rank
PriorityQueue<T>::percolateUp2(Rank i) // 做到了常数级别的优化
{
    T backup = _data[i];
    while(ParentValid(i))
    {
        Rank j = Parent(i);
        if(_data[j] >= backup)
            break;
        _data[i] = _data[j];
        i = j;
    }
    _data[i] = backup;
    return i;
} 

/*
 * 对于以向量表示的完全二叉树，对于任何一个秩为r的节点，其上溯h代的表示为
 *      (r + 1) >> h - 1 
 */

template <typename T>
T
PriorityQueue<T>::delMax()
{
    // 删除堆顶元素，将末尾元素提到堆顶，最快保持堆的结构性不变。
    T ret = _data[0];
    _data[0] = _data[_data.size() - 1];
    _data.pop_back();
    // 下滤，注意
    percolateDown(_data.size(), 0);
    return ret;
} 

template <typename T>
Rank
PriorityQueue<T>::percolateDown(Rank n, Rank i)
{
    while(LChildValid(n, i))
    {
        int j = _data[LChild(i)] > _data[RChild(i)] ? LChild(i) : RChild(i);
        if(_data[i] > _data[j]) // 如果父亲节点大于最大的大孩子节点
            break;
        std::swap(_data[i], _data[j]); 
        i = j; 
    }
    return i;
} 

template <typename T>
Rank
PriorityQueue<T>::percolateDown2(Rank n, Rank i)
{
    T backup = _data[i];
    while(LChildValid(n, i))
    {
        int j = _data[LChild(i)] > _data[RChild(i)] ? LChild(i) : RChild(i);
        if(backup > _data[j]) // 如果父亲节点大于最大的大孩子节点
            break;
        _data[i] = _data[j];
        i = j; 
    }
    _data[i] = backup;
    return i;
} 

template <typename T> 
void
PriorityQueue<T>::heapify(Rank n)
{ // 给定任意n个元素，然后建堆
    int lastInternal = (n >> 1) - 1;
    for(Rank i = lastInternal; InHeap(n, i); --i)
        percolateDown(n, i);
} 
