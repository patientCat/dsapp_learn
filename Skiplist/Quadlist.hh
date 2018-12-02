#ifndef _Quadlist_hh_
#define _Quadlist_hh_


template <typename T>
class Quadlist 
{ 
public:
    struct QuadlistNode{
        T entry;
        QuadlistNode * prev;
        QuadlistNode * next;
        QuadlistNode * above;
        QuadlistNode * below;

        QuadlistNode(T e = T(), QuadlistNode * p = nullptr, QuadlistNode * n = nullptr, QuadlistNode * a = nullptr, QuadlistNode * b = nullptr)
        : entry{ e }
        , prev{ p }
        , next{ n }
        , above{ a }
        , below{ b }
        {}

        // 插入新节点，以当前节点为前驱，以b节点为下邻
        QuadlistNode * insertAsSuccAbove(const T &e, QuadlistNode * b = nullptr) 
        {
            QuadlistNode * x = new QuadlistNode(e, this, next, nullptr, b); // 创建新节点
            if(next)
                next->prev = x;
            next = x;
            if(b) b->above = x;
            return x;
        }
    };

public: 
    using QNode = QuadlistNode;
    Quadlist () 
    {
        init();
    }
    ~Quadlist ()
    {
        clear();
    }
     
    int size() const {  return _size;   }
    bool empty() const {    return !_size;  }
    QNode * first() const   {   return _header->next;   }
    QNode * last() const    {   return _tailer;   }
    bool valid(QNode * p) // 判断p的位置是否合法
    {
        return p && p != _tailer && p != _header;
    }

    QNode * insertAfterAbove(const T &e, QNode * p, QNode * b = nullptr) // 将e作为p的后继，b的上邻插入到quadlist
    {
        ++_size;
        return p->insertAsSuccAbove(e, b);
    }
    // 修改接口
    T remove(QNode * p) // 删除p处的节点，返回被删除节点的数值
    {
        auto t = p;
        auto ret = t->entry;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete t;
        return ret;
    }

protected:
    void init(); // 初始化
    int clear(); // 清楚所有节点
private: 
    int _size;
    QNode * _header;
    QNode * _tailer;
}; 

template <typename T>
void 
Quadlist<T>::init()
{
    _header = new QuadlistNode;
    _tailer = new QuadlistNode;
    _header->next = _tailer; _header->prev = nullptr;
    _tailer->prev = _header; _tailer->next = nullptr;
    _header->above = _tailer->above = nullptr;
    _header->below = _tailer->below = nullptr;
    _size = 0;
}

#endif // Quadlist.hh
