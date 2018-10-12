#pragma once
#include "BST.h" 

template <typename NodePos> 
inline
void attachAsLChild(NodePos p, NodePos lc)
{
    p->lc = lc ; 
    if(lc) // 注意lc可能不存在就行
        lc->parent = p; 
}

template <typename NodePos> 
inline
void attachAsRChild(NodePos p, NodePos rc)
{
    p->rc = rc ; 
    if(rc) // 注意rc可能不存在就行
        rc->parent = p; 
}

template <typename T>
class Splay 
: public BST<T>
{ 
protected:
    BinNodePos(T) splay(BinNodePos(T) v); // 将节点v伸展至树根
public: 
    using BST<T>::_hot; 
    using BST<T>::_root; 
    using BST<T>::_size; 
    using BST<T>::updateHeight; 
    using BST<T>::updateHeightAbove; 
    using BST<T>::searchIn; 
    BinNodePos(T) &search(const T &key);
    BinNodePos(T) insert(const T &key);
    bool remove(const T &key);
}; 

template <typename T>
BinNodePos(T) 
Splay<T>::splay(BinNodePos(T) v)
{
    if(!v)
        return nullptr;
    BinNodePos(T) p;
    BinNodePos(T) g;
    while((p = v->parent) && (g = p->parent))
    {
        BinNodePos(T) g_g = g->parent; 
        if(IsLChild(*p))
        {
            if(IsLChild(*v))
            {
                /* zig-zig */
                attachAsLChild(g, p->rc); 
                attachAsLChild(p, v->rc);  //
                attachAsRChild(p, g);      // 上句和本句可颠倒次序
                attachAsRChild(v, p); 
            }
            else{
                /* zag-zig */
                attachAsRChild(p, v->lc); 
                attachAsLChild(g, v->rc); 
                attachAsLChild(v, p);     
                attachAsRChild(v, g); 
            }
        }
        else{
            if(IsLChild(*v))
            {
                /* zag-zag */
                attachAsRChild(g, p->lc); 
                attachAsRChild(p, v->lc);  //
                attachAsLChild(p, g);      // 上句和本句可颠倒次序
                attachAsLChild(v, p); 
            }
            else{
                /* zig-zag */
                attachAsLChild(p, v->rc); 
                attachAsRChild(g, v->lc); 
                attachAsRChild(v, p);     
                attachAsLChild(v, g); 
            }
        }
        // 这个if包括接下来的if都是考虑树的深度为奇数或者偶数的情况下，单一假设3个节点或者4个节点
        if(!g_g) // 相当于考虑了p = v->parent 为空的情况下 
            v->parent = nullptr;
        else{
            (g == g_g->lc) ? attachAsLChild(g_g, v) : attachAsRChild(g_g, v);  
        } 
        updateHeight(g);
        updateHeight(p);
        updateHeight(v);
    }  
    
    // 这里需要注意的一点是当g == nullptr 的时候，p为根节点，此时只要根据v是p的做孩子
    // 还是右孩子进行旋转即可
    if((p = v->parent)) 
    { 
    if(IsLChild(*v))
    {
        attachAsLChild(p, v->rc);  
        attachAsRChild(v, p);  
    }
    else{
        attachAsRChild(p, v->lc);
        attachAsLChild(v, p);
    }
    v->parent = nullptr;
    updateHeight(p);
    updateHeight(v);
    }
    return v; 
}

/*  经过俩次zigzig变换, 需要注意的是我们要先从g，即祖父节点开始
                 .─.                                               .─.                   
                ( g )                                             ( v )                  
                 `─'▪                                             ▪`─'▪                  
                ▪    ▪                                           ▪     ▪                 
            .─.▪      ▪                  .─.                    ▪       ▪.─.             
           ( p )       ■                ( p )                   ■       ( p )            
            `─'▪      ■ ■              ▪ `─' ▪                 ■ ■       ▪─'▪            
           ▪    ▪    ■T3 ■           ▪         ▪              ■T0 ■     ▪    ▪           
       .─.▪      ▪  ■■■■■■■     .─.▪             ▪ .─.       ■■■■■■■   ▪      ▪.─.       
      ( v )       ■            ( v )              ( g )                ■      ( g )      
      ▪`─'▪      ■ ■           ▪`─'▪              ▪`─'▪               ■ ■     ▪`─'▪      
     ▪     ▪    ■T2 ■         ▪     ▪            ▪     ▪             ■T1 ■   ▪     ▪     
    ▪       ▪  ■■■■■■■       ▪       ▪          ▪       ▪           ■■■■■■■ ▪       ▪    
   ■         ■              ■         ■        ■         ■                 ■         ■   
  ■ ■       ■ ■            ■ ■       ■ ■      ■ ■       ■ ■               ■ ■       ■ ■  
 ■T0 ■     ■T1 ■          ■T0 ■     ■T1 ■    ■T2 ■     ■T3 ■             ■T2 ■     ■T3 ■ 
■■■■■■■   ■■■■■■■        ■■■■■■■   ■■■■■■■  ■■■■■■■   ■■■■■■■           ■■■■■■■   ■■■■■■■
根据图可以看出，v的左树没有发生变化，g的右树也没有发生变化
zag-zig的情况
          .─.                            .─.
         ( g )                          ( g )
          `─'▪                           `─'▪
         ▪    ▪                         ▪    ▪                       .─.
     .─.▪      ■                    .─.▪      ■                     ( v )
    ( p )     ■ ■                  ( v )     ■ ■                    ▪`─'▪
     `─'▪    ■T3 ■                  ▪─'▪    ■T3 ■                 ▪       ▪
    ▪    ▪  ■■■■■■■                ▪    ▪  ■■■■■■■              ▪           ▪ .─.
   ▪      ▪─.                  .─.▪      ▪■                  .─.             ( g )
   ■     ( v )                ( p )      ■ ■                ( p )            ▪`─'▪
  ■ ■    ▪`─'▪                ▪`─'▪     ■T1 ■               ▪`─'▪           ▪     ▪
 ■T2 ■  ▪     ▪              ▪     ▪   ■■■■■■■             ▪     ▪         ▪       ▪
■■■■■■■▪       ■            ■       ▪                     ▪       ▪        ■        ■
      ■ ■     ■ ■          ■ ■      ■                     ■       ■       ■ ■      ■ ■
     ■T0 ■   ■T1 ■        ■T2 ■    ■ ■                   ■ ■     ■ ■     ■T1 ■    ■T3 ■
    ■■■■■■■ ■■■■■■■      ■■■■■■■  ■T0 ■                 ■T2 ■   ■T0 ■   ■■■■■■■  ■■■■■■■
                                 ■■■■■■■               ■■■■■■■ ■■■■■■■

*/

template <typename T>
BinNodePos(T) &
Splay<T>::search(const T &key)
{
    BinNodePos(T) &x = searchIn(_root, key, _hot);
    _root = splay(x ? x : _hot); // 如果找到该元素，推上来，否则把其父亲节点推上来
    return _root;
}

template <typename T>
BinNodePos(T) 
Splay<T>::insert(const T &key)
{
    if(!_root) // 处理退化为空树的情况
    {
        _size++;
        return  _root = new BinNode<T>(key);
    }
    if( key == search(key)->data) return _root; // 处理节点已经存在的情况
    // 目标节点不存在
    ++_size; 
    BinNodePos(T) t = _root;
    if(_root->data < key)
    {
        t->parent = _root = new BinNode<T>(key, nullptr, t, t->rc); 
        if(HasRChild(*t))   {   t->rc->parent = _root; t->rc = nullptr; }   
    } 
    else {
        t->parent = _root = new BinNode<T>(key, nullptr, t->lc, t); 
        if(HasLChild(*t))   {   t->lc->parent = _root; t->lc = nullptr; }   
    }
    updateHeightAbove(*t);
    return _root;
}

template <typename T>
bool 
Splay<T>::remove(const T &key)
{
    if(!_root)
        return false;
    if(key != search(key)->data) 
        return false;
    // 假设目标存在
    --_size;
    // 这里我们以根的succ节点为新根
    BinNodePos(T) t = _root;
    BinNodePos(T) w = _root->succ(); 
    if(w->parent == _root)
    {
        attachAsLChild(w, t->lc);      
        _root = w;
        updateHeight(_root);
    }
    else{
        std::swap(t->data, w->data);  
        BinNodePos(T) p = w->parent; 
        attachAsLChilde(p, w->rc); 
        t = w;
        updateHeightAbove(p);
    } 
    // release (t)
    delete(t);
    return true;
}
