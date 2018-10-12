#include "BinTree.h" 


template <typename T>
class BST
: public BinTree<T>
{ 
public: 
    using BinTree<T>::_root; 
    using BinTree<T>::_size; 
    using BinTree<T>::updateHeightAbove; 
    using BinTree<T>::updateHeight; 
    // 查找
    virtual BinNodePos(T) &search(const T &); 
    // 插入
    virtual BinNodePos(T) insert(const T &); 
    // 删除
    virtual bool remove(const T &); 
protected:
    BinNodePos(T) _hot; //命中节点的父亲
    BinNodePos(T) connect34( // 3+4 重构
            BinNodePos(T) , BinNodePos(T) , BinNodePos(T) ,
            BinNodePos(T) , BinNodePos(T) , BinNodePos(T) , BinNodePos(T) );
    BinNodePos(T) rotateAt(BinNodePos(T) ); // 旋转调整
    static BinNodePos(T) & searchIn(BinNodePos(T) &  , const T &, BinNodePos(T)  &);
private:
    static BinNodePos(T) & searchInIter(BinNodePos(T) &  , const T &, BinNodePos(T)  &);
    static BinNodePos(T) removeAt(BinNodePos(T) & x, BinNodePos(T) & hot);
}; 

template <typename T>
BinNodePos(T)  &
BST<T>::search(const T &e)
{
    return searchIn(_root, e, _hot = NULL);
} 

template <typename T>
BinNodePos(T) & 
BST<T>::searchIn(BinNodePos(T) &v  , const T &key, BinNodePos(T) &hot /*记忆热点*/)
{
    if(!v || (key == v->data))    return v; 
    hot = v;
    return searchIn(( key < v->data ? v->lc : v->rc), key, hot);
}

template <typename T>
BinNodePos(T) & 
BST<T>::searchInIter(BinNodePos(T) &v  , const T &key, BinNodePos(T) &hot /*记忆热点*/)
{ // 这里的迭代有些问题，
    BinNodePos(T) vv = v; // 必须借用vv指向v来实现向下更迭
    // 需要注意的是一定要让vv指向函数之外的东西，大致意思就是不要指向局部变量
    if(!vv || (key == vv->data))    return vv; 
    while(1)
    {
        if(key < vv->data)
        {
            hot = vv;
            vv = vv->left;
        }
        else if(key > vv->data){
            hot = vv;
            vv = vv->right;
        }
        else{
            break;
        }
    }
    return vv;
}

template <typename T>
BinNodePos(T) 
BST<T>::insert(const T &e)
{
    BinNodePos(T) & x = search(e);
    if(!x)
    {
        x = new BinNode<T>(e, _hot); // 回忆binNode的构造方式
        ++_size;
        updateHeightAbove(x);
    }
    return x;
}

template <typename T>
bool 
BST<T>::remove(const T &e)
{
    BinNodePos(T) & x = search(e); // 依然先是调用search接口，得到删除元素的位置引用和其父亲的位置引用
    if(!x) return false; // 判断目标元素是否存在应该是外面接口做的事情。
    removeAt(x, _hot); // 删除后的调整比较复杂
    --_size;
    updateHeightAbove(_hot);
    return true;
}

// 实际的删除稍微有些复杂, 因为删除后依然要维持BST的特性，主要分为三种情况。
// 1. 目标元素是叶子节点，这个很好处理，直接删除完事。
// 2. 目标元素有一个子树
// 3. 目标元素有俩个子树
template <typename T>
BinNodePos(T)  
BST<T>::removeAt(BinNodePos(T) &x, BinNodePos(T) &hot)
{
    BinNodePos(T)  w = x; // 指向删除元素
    BinNodePos(T)  succ = nullptr;
    // 有一个子树的情况下
    if(!HasLChild(*x))//没有左树，那么默认其有右树，即使右树为空
    {
        succ = x = x->rc; // 调整删除元素的后继, 注意这里的x是指针的引用，所以直接用其右树替换了x
    }
    else if(!HasRChild(*x))
    {
        succ = x = x->lc;
    }
    else{ // 这里实现的方法比较巧妙
        w = w->succ();// 指向被删除元素的后继。因为这里是俩边树都有，所以后继一定在右树中的最左孩子。
                       // 所以这个后继只可能有一个右孩子，或者没有
        std::swap(x->data, w->data);  
        BinNodePos(T)  u = w->parent; 
        // 这个判断需要对后继的求法有相当的了解。这个后继只存在俩个位置，要么为删除元素的右孩子。要么
        // 为其右孩子的左树中, 通过此可以直接判断后继是其父亲的左孩子还是右孩子。
        (( u == x) ? u->rc : u->lc) = succ = w->rc;   
    } 
    hot = w->parent; // 此时hot指向被删除元素父亲
    if(succ) succ->parent = hot;  //然后继的parent回指
    //release w->data;
    delete w;
    return succ;
} 

template <typename T>
BinNodePos(T) 
BST<T>::connect34( // 3+4 重构
        BinNodePos(T) a, BinNodePos(T) b, BinNodePos(T) c,
        BinNodePos(T) T0, BinNodePos(T) T1, BinNodePos(T) T2, BinNodePos(T) T3)
{
    a->lc = T0;     if(T0)  T0->parent = a;  
    a->rc = T1;     if(T1)  T1->parent = a;  
    updateHeight(a);
    c->lc = T2;     if(T2)  T2->parent = c;
    c->rc = T3;     if(T3)  T3->parent = c;      
    updateHeight(c);
    b->lc = a;      a->parent = b; 
    b->rc = b;      c->parent = b;  
    updateHeight(b); 
    return b;
}

template <typename T>
BinNodePos(T) 
BST<T>::rotateAt(BinNodePos(T) v) // 传入参数为孙子节点v
{
    BinNodePos(T) g, p; 
    p = v->parent;
    g = p->parent;  
    if(IsLChild(*p))
    {
        if(IsLChild(*v))
        {
            p->parent = g->parent; // 向上连接  
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);    
        }
        else{
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);      
        }
    }
    else{
        if(IsLChild(*v))
        {
            v->parent = g->parent;
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);      
        }
        else{
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);      
        }
    }
}
