#define BinNodePos(T) BinNode<T> *
#define stature(p) ((p) ? p->height : -1) // 空节点的高度为-1，叶子节点的高度为0 
using RBcolor = enum {RB_Red, RB_Black};


template <typename T>
class BinNode 
{ 
public: 
    BinNode () //没有初始化data，因为不确定data的类型，所以让其自己初始化
    : height(0), color(RB_Red), npl(1), parent(nullptr), lc(nullptr), rc(nullptr) {}
    BinNode (T e, BinNodePos(T) p = nullptr, BinNodePos(T) l = nullptr, BinNodePos(T) r = nullptr,
            int h= 0, int n = 1, RBcolor c = RB_Red)
    : data(e), height(h), color(c), npl(n), parent(p), lc(l), rc(r) {}

public:
    int size()const;
    BinNodePos(T) insertAsLC(const T &);
    BinNodePos(T) insertAsRC(const T &);
    // 计算中序遍历的后继
    BinNodePos(T) succ();

    // 遍历接口
     
public:  //为了简单起见，成员也声明为public
    T           data;
    int         height;
    RBcolor     color;
    int         npl; // 左式堆
    BinNodePos(T)  parent;
    BinNodePos(T)  lc;
    BinNodePos(T)  rc;
}; 

template <typename T>
int 
BinNode<T>::size()const
{
    int s = 1;
    if(lc->size()) s += lc->size();  
    if(rc->size()) s += rc->size();  
    return s;
}

template <typename T>
BinNodePos(T) 
BinNode<T>::insertAsLC(const T &e)
{
    BinNodePos(T) pnode = new BinNode<T>(e, this);
    lc = pnode;
    return pnode;
}

template <typename T>
BinNodePos(T) 
BinNode<T>::insertAsRC(const T &e)
{
    BinNodePos(T) pnode = new BinNode<T>(e, this);
    rc = pnode;
    return pnode;
}

template <typename T>
BinNodePos(T) 
BinNode<T>::succ()
{
    BinNodePos(T) s = this;
    if(this->rc)
    {
        s = rc;
        while(s) s = s->lc; 
    }
    else{
        while(s == s->parent->rc)  s = s->parent;
        s = s->parent;  
    } 
}
