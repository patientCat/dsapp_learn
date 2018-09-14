//c++ program
//design by >^.^<
//@date    2018-09-13 22:02:00

// 这种方式从未见到过
#define Pos(T) LinkNode<T> * 

template <typename T>
struct LinkNode
{
// interface
    LinkNode() = default; //用来构造空节点
    LinkNode(const T &e, Pos(T) p = nullptr, Pos(T) s = nullptr)
    : data(e)
    , pred(p)
    , succ(s)
    {}

    ~LinkNode() = default;
    Pos(T) insertAsPred(const T &e);
    Pos(T) insertAsSucc(const T &e);

// member
    T           data;
    Pos(T)      pred;    
    Pos(T)      succ;    
};

template <typename T>
Pos(T) 
LinkNode<T>::insertAsPred(const T &e)
{
    Pos(T) pnode = new LinkNode<T>(e, pred, this); 
    pred->succ = pnode;
    pred = pnode; 
    return pnode;
}

template <typename T>
Pos(T) 
LinkNode<T>::insertAsSucc(const T &e)
{
    Pos(T) pnode = new LinkNode<T>(e, this, succ); 
    succ->pred = pnode; 
    succ = pnode;
    return pnode;
}
