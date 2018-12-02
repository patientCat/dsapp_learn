#include "BinNode.h" 
#include <algorithm> 
#include <stack> 
#include <queue> 
#include <string> 
#include <fstream> 
// 用点实现比较好
#define HasRChild(x)  ((x).rc) 
#define HasLChild(x)  ((x).lc) 
#define IsRoot(x) (!(x).parent) 
#define IsLChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->lc))  
#define IsRChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->rc))  
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild((x).parent) ? (x).parent->lc : (x).parent->rc)) 
// 如果当前节点是根节点，则返会根节点，如果是左树，则返回左树，如果是右树返回右树。
// 这里是一种简便操作，返回其父亲节点的指针域
using std::stack; 
using std::queue; 
using std::string; 
using std::ifstream; 

template <typename T>
class BinTree 
{ 
public: 
    BinTree () : _size(0), _root(nullptr) {} 
    ~BinTree () = default; 

public:
    int size()const {   return _size;   }
    bool empty()const { return _root ? false : true; }
    BinNodePos(T) root()const { return _root;   }
    BinNodePos(T) insertRoot(int e) { ++_size; return _root = new BinNode<T>(e);    }
    BinNodePos(T) insertAsLC(BinNodePos(T) x, T e); 
    BinNodePos(T) insertAsRC(BinNodePos(T) x, T e); 
    // 子树接入
    BinNodePos(T) attachAsLC( BinNodePos(T) x, BinTree<T> * &s);
    BinNodePos(T) attachAsRC( BinNodePos(T) x, BinTree<T> * &s);
    // 删除
    BinNodePos(T) remove(BinNodePos(T) x);
    BinNodePos(T) removeAt(BinNodePos(T) x);

    // 遍历方式
    // 先序遍历
    template <typename VST>
    void preTraverseRecur(BinNodePos(T) x, VST visit);
    template <typename VST>
    void preTraverseIter(BinNodePos(T) x, VST visit);
    template <typename VST>
    void preTraverseIter2(BinNodePos(T) x, VST visit);

    // 中序遍历
    template <typename VST>
    void inTraverseRecur(BinNodePos(T) x, VST visit);
    template <typename VST>
    void inTraverseIter(BinNodePos(T) x, VST visit);
    // 后序遍历
    template <typename VST>
    void postTraverseRecur(BinNodePos(T) x, VST visit);
    template <typename VST>
    void postTraverseIter(BinNodePos(T) x, VST visit);
    // 层次遍历
    template <typename VST>
    void levelTraverse(BinNodePos(T) x, VST visit);

    // 逆层次遍历
    template <typename VST>
    void levelReverseTraverse(BinNodePos(T) x, VST visit);

    // 建树可以直接使用遍历的方式
    template <typename VST>
    void levelConstruct(VST construct);

    // 测试
    void constructFromTest();

protected:
    virtual int updateHeight(BinNodePos(T) x); // 更新节点x的高度
    void updateHeightAbove(BinNodePos(T) x); // 更新节点x以及其祖先的高度
     

private:
    template <typename VST>
    void visitAlongLeftChild(BinNodePos(T) x, VST visit, stack<BinNodePos(T) > &s);
protected: // 因为要遭很多种树，将会采取继承的方式，所以成员采用protected的方式
    int                 _size;
    BinNodePos(T)       _root;
}; 

// 更新节点x的高度
// 任意节点高度等于 1 + 最大子节点高度
template <typename T>
int 
BinTree<T>::updateHeight(BinNodePos(T) x)
{
    return x->height = 1 + std::max(stature(x->lc), stature(x->rc));  
}

template <typename T>
void 
BinTree<T>::updateHeightAbove(BinNodePos(T) x)
{
    while(x)
    {
        updateHeight(x);
        x = x->parent;
    } 
}

template <typename T>
BinNodePos(T) 
BinTree<T>::insertAsLC(BinNodePos(T) x, T e)
{
    ++_size;
    x->insertAsLC(e); 
    updateHeightAbove(x);
    return x->lc; 
}

template <typename T>
BinNodePos(T)
BinTree<T>::insertAsRC(BinNodePos(T) x, T e)
{
    ++_size;
    x->insertAsRC(e); 
    updateHeightAbove(x);
    return x->rc; 
}

template <typename T>
template <typename VST>
void 
BinTree<T>::preTraverseRecur(BinNodePos(T) x, VST visit)
{
    if(!x)
        return ;
    visit(x->data);
    preTraverseRecur(x->lc, visit);  
    preTraverseRecur(x->rc, visit); 
}

template <typename T>
template <typename VST>
void 
BinTree<T>::preTraverseIter(BinNodePos(T) x, VST visit)
{
    stack<BinNodePos(T)> s;
    s.push(x);
    while(!s.empty())
    {
        auto x = s.top(); 
        s.pop(); 
        visit(x->data);
        if(HasRChild(*x))
            s.push(x->rc);
        if(HasLChild(*x))
            s.push(x->lc);
    } 
}

template <typename T>
template <typename VST>
void 
BinTree<T>::preTraverseIter2(BinNodePos(T) x, VST visit)
{
    stack<BinNodePos(T) > tmp;
    while(true)
    {
        visitAlongLeftChild(x, visit, tmp);
        if(tmp.empty())
            break;
        x = tmp.top();
        tmp.pop();
    }
}

template <typename T>
template <typename VST>
void 
BinTree<T>::visitAlongLeftChild(BinNodePos(T) x, VST visit, stack<BinNodePos(T) > &s)
{
    while(x)
    {
        visit(x->data);
        s.push(x->rc); 
        x = x->lc;         
    }
}


template <typename T>
template <typename VST>
void 
BinTree<T>::inTraverseRecur(BinNodePos(T) x, VST visit)
{
    if(!x)
        return ;
    inTraverseRecur(x->lc, visit);
    visit(x->data);  
    inTraverseRecur(x->rc, visit);
}

template <typename T>
template <typename VST>
void 
BinTree<T>::inTraverseIter(BinNodePos(T) x, VST visit)
{
    if(!x)
        return ;
    stack<BinNodePos(T)> s;
    while(true)
    {
        // goAlongLeftChild
        {
            while(x)
            {
                s.push(x);
                x = x->lc; 
            }
        }
        if(s.empty())
            break;
        x = s.top();
        s.pop();
        visit(x->data);  
        x = x->rc;  
    }
}

template <typename T>
template <typename VST>
void 
BinTree<T>::postTraverseRecur(BinNodePos(T) x, VST visit)
{
    if(!x)
        return ;
    postTraverseRecur(x->lc, visit);
    postTraverseRecur(x->rc, visit);  
    visit(x->data); 
}

// 这个思想很巧妙，假如我们先访问节点，再访问右子树，再访问左子树。这样遍历，结果刚好是
// 后续遍历的逆序。所以我们使用俩个stack。
template <typename T>
template <typename VST>
void 
BinTree<T>::postTraverseIter(BinNodePos(T) x, VST visit)
{
    if(!x)
        return ;
    stack<BinNodePos(T)> s1;
    stack<BinNodePos(T)> s2;
    s1.push(x);
    while(!s1.empty())
    {
        x = s1.top(); 
        s1.pop();
        s2.push(x);
        if(HasLChild(*x))
            s1.push(x->lc);
        if(HasRChild(*x))
            s1.push(x->rc); 
    }
    while(!s2.empty())
    {
        auto ret = s2.top();
        s2.pop();
        visit(ret->data );
    }
}

template <typename T>
template <typename VST>
void 
BinTree<T>::levelTraverse(BinNodePos(T) x, VST visit)
{
    if(!x)
        return ;
    queue<BinNodePos(T) > q;
    q.push(x);
    while(!q.empty())
    {
        x = q.front();
        q.pop();
        visit(x->data );
        if(HasLChild(*x))
            q.push(x->lc);
        if(HasRChild(*x))
            q.push(x->rc);
    }  
}


template <typename T>
BinNodePos(T) 
BinTree<T>::attachAsLC( BinNodePos(T) x, BinTree<T> * &s)
{
    assert(nullptr == x->lc);
    x->lc = s;
    s->parent = x;   
    _size += s->size(); 
    updateHeightAbove(x);
    // 需要释放这颗树
    s->root = nullptr;
    s->_size = 0;  
    s = nullptr;
    return x;
}

template <typename T>
BinNodePos(T) 
BinTree<T>::attachAsRC( BinNodePos(T) x, BinTree<T> * &s)
{
    assert(nullptr == x->rc);
    x->rc = s;
    s->parent = x;   
    _size += s->size(); 
    updateHeightAbove(x);
    // 需要释放这颗树
    s->root = nullptr;
    s->_size = 0;  
    s = nullptr;
    return x;
}

template <typename T>
BinNodePos(T) 
BinTree<T>::remove(BinNodePos(T) x)
{
    if(!x->parent ) // 代表是根, 删除根节点
        _root = nullptr;
    else{
        if(x == x->parent->lc)
        {
            x->parent->lc;  
        }  
        else{
            x->parent->rc;  
        }
    }
     
    updateHeightAbove(x);    
    int n = removeAt(x) ; 
    _size -= n; 
    return n;
}

template <typename T>
BinNodePos(T) 
BinTree<T>::removeAt(BinNodePos(T) x)
{
    if(!x)
        return nullptr;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);  
    // release(x->data) 
    delete x;
    return n;
}

// 借助一个队列和一个栈就可以实现
template <typename T>
template <typename VST>
void 
BinTree<T>::levelReverseTraverse(BinNodePos(T) x, VST visit)
{
    if(!x)
        return ;
    queue<BinNodePos(T) > q;
    stack<BinNodePos(T) > s;
    q.push(x);
    while(!q.empty())
    {
        x = q.front();
        q.pop();
        s.push(x);
        if(HasRChild(*x))
            q.push(x->rc);
        if(HasLChild(*x))
            q.push(x->lc);  
    } 
    while(!s.empty())
    {
        x = s.top();
        s.pop();
        visit(x->data );
    }
}

template <typename T>
template <typename VST>
void 
BinTree<T>::levelConstruct(VST construct)
{
    queue<BinNodePos(T) > q;
    BinNodePos(T) x = insertRoot(T());
    q.push(x);
    int l, r;
    while(!q.empty())
    {
        x = q.front();
        q.pop();
        construct(x);
        scanf("%d%d", &l, &r);
        if(l)
        {
            insertAsLC(x, T());
            q.push(x->lc);
        }
        if(r)
        {
            insertAsRC(x, T());
            q.push(x->rc);
        }
    }  
}

template <typename T>
void 
BinTree<T>::constructFromTest()
{
    queue<BinNodePos(T) > q;
    ifstream ifs("test.txt");
    BinNodePos(T) x = insertRoot(T());
    q.push(x);
    T data ;
    int l, r;
    while(!q.empty())
    {
        ifs >> data >> l >> r;
        x = q.front();
        q.pop();
        x->data = data; 
        if(l)
        {
            insertAsLC(x, T());
            q.push(x->lc);
        }
        if(r)
        {
            insertAsRC(x, T());
            q.push(x->rc);
        }
    }  
}
