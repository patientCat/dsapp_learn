#ifndef _Skiplist_hh_
#define _Skiplist_hh_

#include "Quadlist.hh" 
#include <list> 
#include <iostream> 

using std::list; 
using std::pair; 
using namespace std;

template <typename K, typename V>
class Skiplist 
{ 
public: 
    using ITER = typename list< Quadlist<pair<K, V>> *>::iterator;
     
    int size() const    {   return _list.size() ? _list[_list.size() - 1].size() : 0;   }
    int level() const   {   return _list.size();    }
    bool empty() const  {   return _list.empty();    }
    bool put(K, V); // 插入
    V *get(K k); // 读取
    bool remove(K k); // 删除

    // 测试使用 就简单自上而下输出key就够了
    void print()
    {
        auto qlist = _list.begin();
        while(qlist != _list.end())
        {
            for(auto begin = (*qlist)->first(); begin != (*qlist)->last(); begin = begin->next)
            {
                cout << begin->entry.first << "   ";
            } 
            ++qlist;
            cout << endl;
        }
    }
protected:
    bool skipSearch(ITER &iter , typename Quadlist<pair<K, V>>::QuadlistNode * &p, K &k);

private: 
    list< Quadlist<pair<K, V>> *> _list;
}; 


template <typename K, typename V>
V * 
Skiplist<K, V>::get(K key)
{
    if(empty())
        return nullptr;
    auto qlist = _list.begin();
    auto p = (*qlist)->first();
    if(skipSearch(qlist, p, key))
        return &p->entry.second;
    else
        return nullptr;
} 

template <typename K, typename V>
bool 
Skiplist<K, V>::skipSearch(ITER &iter, typename Quadlist<pair<K, V>>::QuadlistNode * &p, K &key)
{
    while(true)
    {
        // p->next 为假时，p指向_tailer节点，p->prev为假时，p指向_header节点
        while(p->next && p->entry.first <= key)
            p = p->next;
        p = p->prev;
        if(p->prev && (key == p->entry.first)) return true; // 如果命中，返回
        // 否则，转入下一层
        ++iter;
        if(iter == _list.end()) return false; // 如果已经穿透底层，则意味着失败
        p = (p->prev) ? p->below : (*iter)->first();
    }
}

template <typename K, typename V>
bool 
Skiplist<K, V>::put(K k, V v) // 跳转表词条插入算法
{
    pair<K, V> e{k, v}; 
    if(empty()) _list.push_back(new Quadlist<pair<K, V>>); // 插入首个entry
    auto qlist = _list.begin();
    auto p = (*qlist)->first();
    if(skipSearch(qlist, p, k)) // 查找适当的插入位置，不大于关键码k的最后一个节点
        while(p->below) p = p->below;   // 若已有雷同词条，则需强制转换到塔底

    qlist = --_list.end();
    auto b = (*qlist)->insertAfterAbove(e, p);
    while(rand() & 1) // 随机决定是否需要长高新塔
    {
        while((*qlist)->valid(p) && !p->above) p = p->prev;
        if(!(*qlist)->valid(p)) // 若前驱是header
        {
            if(qlist == _list.begin()) // 且当前已经是最顶层，则意味着必须创建一个新层
            {
                _list.push_front(new Quadlist<pair<K, V>>);
                p = _list.front()->first()->prev;
            }
            else{
                p = (*--qlist)->first()->prev; // p 转至上一层的_header
            }
        }
        else{ // 否则
            p = p->above;
        }
        --qlist;
        b = (*qlist)->insertAfterAbove(e, p, b); // 将新节点插入p之后，b之上
    }
    return true;
} 

template <typename K, typename V>
bool Skiplist<K, V>::remove(K k) // 删除
{
    if(empty()) return false; // 空表情况
    auto qlist = _list.begin(); // 从顶层的quadlist开始
    auto p = (*qlist)->first();
    if(!skipSearch(qlist, p, k)) // 若目标不存在，则直接返回
        return false;
    // 如果目标存在，则逐层拆除与之对应的塔
    do{
        auto lower = p->below;
        (*qlist)->remove(p);
        p = lower; 
        ++qlist;
    }while(qlist != _list.end()); // 直到塔基
    while(!empty() && (*_list.begin())->empty()) // 反复清除可能已经不含有词条的顶层quadlist
    {
        _list.erase(_list.begin());
    }
    return true; // 删除操作成功
} 


#endif // Skiplist.hh
