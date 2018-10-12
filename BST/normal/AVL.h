#include "BST.h" 

#define PBalanced(x) (stature((x).lc) == stature((x).rc) ) //理想平衡

#define BalFac(x) (stature((x).lc) - stature((x).rc)) //平衡因子

#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2)) //AVL平衡条件

#define tallerChild(x) (\
        stature((x)->lc) > stature((x)->rc) ? (x)->lc : ( /*左高*/ \
        stature((x)->lc) < stature((x)->rc) ? (x)->rc : ( /*右高*/ \
        IsLChild(*(x)) ? (x)->lc : (x)->rc /*等高*/ \
        )\
        )\
        )\


template <typename T>
class AVL 
: public BST<T>
{ 
public: 
    // search接口重新沿用
    using BST<T>::search; 
    using BST<T>::_hot; 
    using BST<T>::_size; 
    using BST<T>::_root; 
    using BST<T>::updateHeightAbove; 
    using BST<T>::updateHeight; 
    BinNodePos(T) insert(const T &); // 插入重新定义
    bool remove(const T &); // 删除重新定义
     
private: 
}; 

template <typename T>
BinNodePos(T) 
AVL<T>::insert(const T &e)
{
    BinNodePos(T) & x = search(e);
    if(x) return x; // 排除目标存在的情况
    x = new BinNode<T>(e, _hot);
    ++_size;
    BinNodePos(T) xx = x; // 利用xx指代x，因为search返回的是指针的引用，不能随意改动
    for(BinNodePos(T) g = _hot; g; g = g->parent)
    {
        if(!AvlBalanced(*g))
        {
            // fromparentto返回当前节点父亲节点的指针域
            FromParentTo(*g) = rotateAt(tallerChild( tallerChild(g) ));
            break;
        }
        else{
            updateHeightAbove(g);
        }
    }   
    return xx;
} 

template <typename T>
bool 
AVL<T>::remove(const T &e)
{
    /* ----- BST 删除操作(缺少一个高度更新，在AVL中更新) ----- */
    BinNodePos(T) x = search(e);
    if(!x)
        return false; // 删除元素必须保证存在
    BST<T>::removeAt(x, _hot);
    --_size; 
    /* ----- AVL 删除所特有的 ----- */
    for(BinNodePos(T) g = _hot; g; g = g->parent)
    {
        if(!AvlBalanced(*g)) // 如果不满足avl平衡条件
        {
            g = FromParentTo (*g) = rotateAt(tallerChild(tallerChild(g)));
            updateHeight(g);
        }
    }  
    return true;
}
