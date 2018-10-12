#include "BTNode.h" 

template <typename T>
class BTree 
{ 
protected:
    int _size; // 存放的key总数
    int _order; // B树的阶次，至少为3
    BTNodePos(T) _root;
    BTNodePos(T) _hot;
    void solveOverflow(BTNodePos(T) );
    void solveUnderflow(BTNodePos(T) );

public: 
    BTree(int order = 3)
    : _size(0)
    , _order(order)     
    {
        _root = new BTNode<T>();
    }

    int order()const {    return _order;  }
    int size()const {   return _size;   }
    BTNodePos(T) & root()   {   return _root;   }
    bool empty() const {    return !_root;  }
    BTNodePos(T) search(const T &e);
    bool insert(const T &e);
    bool remove(const T &e);
}; 

template <typename T>
BTNodePos(T) 
BTree<T>::search(const T &e)
{
    BTNodePos(T) v = _root;
    _hot = nullptr;
    while(v)
    {
        auto retIter = v->key.find(v->key.begin(), v->key.end(), [=](T t)->bool{
                                                                 if(e >= t) return true;
                                                                 return false;});
        int posnum = retIter - v->key.begin(); 
        if(e == *retIter)
            return v;
        _hot = v;
        v = v->child[posnum];
    }
    return nullptr;
}
/* 我们将key和child引用域稍稍错位，就得到具体信息，此时我们在这里失败，代表我们的目标值
 * 大于a，但是小于b，因此我们需要向下去的位置就是child-set中的 s2 + b - s1, 根据find，如果没有找到元素
 * 则返回end哨兵，同样可以保证合理性
 * 对于节点a来说，其左子树的秩为r，右子树的秩为r + 1
                                   r |
┌─────────┐      ┌───┬───┬───┬───┬───┬───┬───┬───┐  
│ key-set │───▶  │ s1│ o │ o │ o │█a█│ b │ o │ e1│  
├─────────┤    ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐
│child-set│───▶│ s2│ x │ x │ x │ x │█x█│ x │ x │ e2│
└─────────┘    └───┴───┴───┴───┴───┴───┴───┴───┴───┘
*/

template <typename T>
bool
BTree<T>::insert(const T &e)
{
    auto ret = search(e);
    if(ret) return false; // 保证目标元素不存在
    ++_size;
    // search查找失败后，_hot就是叶节点
    // 我们要在_hot中插入e
    auto retIter = find(_hot->key.begin(), _hot->key.end(), [=](T t){
                                                    if(e>=t)    return true;
                                                    return false;});  
    _hot->key.insert(retIter, e);
    // 理论上的插入
    //int posnum = retIter - _hot->key.begin(); 
    //_hot->child.insert(_hot->child.begin() + posnum + 1, nullptr );
    // 但是叶子节点后面全是外部节点，所以都是nullptr，不需要再特定位置插入 
    _hot->child.push_back(nullptr);
    // 插入之后，可能会导致这个节点的关键码超过m-1，从而溢出，违反了B树的定义。
    solveOverflow(_hot);
} 

/*
 superNode-_hot                    ┌───┐ 
                                   │ e │   
┌─────────┐      ┌───┬───┬───┬───┬─┴─┬─┴─┬───┬───┐  
│ key-set │───▶  │ s1│ o │ o │ o │█a█│ b │ o │ e1│  
├─────────┤    ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐
│child-set│───▶│ s2│ x │ x │ x │ x │█x█│ x │ x │ e2│
└─────────┘    └───┴───┴───┴───┴───┴───┴───┴───┴───┘
┌─────────┐      ┌───┬───┬───┬───┬───┬───┬───┬───┬───┐  
│ key-set │───▶  │ s1│ o │ o │ o │█a█│ e │ b │ o │ e1│  
├─────────┤    ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐
│child-set│───▶│ s2│ x │ x │ x │ x │█x█│   │ x │ x │ e2│
└─────────┘    └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
                                         ^ 
                                        这里为理论上需要插入的新节点
*/

/* overflow 示例图
          ┌───┬───┬───┐                      ┌───┬───┬───┐                  ┌───┬───┬───┬───┐
          │400│470│500│                      │400│470│500│                  │400│440│470│500│
          └───┼───┴───┤                      └───┼───┴───┤                  └───┼───┼───┴───┤
        ┌─────┘       └─┐                ┌───────┘       └─┐                ┌───┘   │       └─┐
        │               │                │                 │                │       │         │
        ▼               ▼                ▼                 ▼                ▼       ▼          ▼
  ┌───┬───┬───┐   ┌───┬───┬───┐    ┌───┬───┬───┬───┐ ┌───┬───┬───┐    ┌───┬───┐    ┌───┐     ┌───┬───┬───┐
  │410│430│450│   │520│540│570│    │410│430│440│450│ │520│540│570│    │410│430│    │450│     │520│540│570│
  └───┴───┴───┘   └───┴───┴───┘    └───┴───┴───┴───┘ └───┴───┴───┘    └───┴───┘    └───┘     └───┴───┴───┘
                                            mid
         ┌────────────┐                 ┌───────────┬───┐                  ┌───────────┐
         │ orgin tree │                 │insert node│440│                  │ overflow  │
         └────────────┘                 └───────────┴───┘                  └───────────┘

                        ┌───┐                    
                        │470│                    
                        ╳───╳                    
                       ╱     ╲                   
                    ╱─╱       ╲─────╲            
                   ╱                 ╲           
          ┌───┬───▼                 ┌─▼─┐        
          │400│440│                 │500│        
          └───┴───╳                 └───╳        
                 ╱                       ╲       
       ╱────────╱                        ╲       
      ▼                                   ▼      
┌───┬───┬───┐                       ┌───┬───┬───┐
│410│430│450│                       │520│540│570│
└───┴───┴───┘                       └───┴───┴───┘
     ┌───────────┐                               
     │ overflow  │                               
     └───────────┘                               
                                                        
*/

template <typename T>
void
BTree<T>::solveOverflow(BTNodePos(T) v)
{
    if(v->child.size() <= _order)
        return ; 
    size_t mid = _order >> 1;
    BTNodePos(T) u = new BTNode<T>(); // 注意此时节点已经有一个空孩子了。
    u->child[0] = v->child[mid + 1]; // 因此直接让其为中点的右孩子
    for(int i = mid + 1; i < v->key.size(); ++i )
    {
        u->key.push_back(v->key[i]);  
        u->child.push_back(v->child[i+1]);  
    }
    u->key.erase(u->key.begin() + mid + 1, u->key.end());
    u->child.erase(u->child.begid() + mid + 1, u->child.end());  
    if(u->child[0]) //父节点回指操作
    {
        for(auto a : u->child)
            a->parent = u;   
    } 
    // 开始上升操作
    BTNodePos(T) p = v->parent ; 
    if(!p) // 代表此时v是根节点，需要让s称为新的根节点
    {   _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p;    }  
    auto insertIter = find(p->key.begin(), p->key.end(), [=](int t){
                                                 if(v->key[mid] >= t) return true;
                                                 return false;});   
    int posnum = insertIter - p->key.begin();  
    p->insert(insertIter, v->key[mid]);   
    v->key.erase(v->key.begin() + mid);  
    p->child.insert(p->child.begin() + posnum + 1, u); 
    u->parent = p; 
    solveOverflow(p);
} 

template <typename T>
bool
BTree<T>::remove(const T &e)
{
    BTNodePos(T) v = search(e);
    if(!v)  return false;
    --_size;
    auto rIter = find(v->key.begin(), v->key.end(), e);  
    assert(rIter != v->key.end()); 
    int r = rIter - v->key.begin(); 
    if(v->child[0]) // 如果v不是叶子节点, 就交换其成为后继
    {
        BTNodePos(T) w = v->child[r + 1];
        while(w->child[0] ) w = w->child[0];   // 此时w就是v的后继叶子节点
        // 为什么？ 因为在B树中，如果一个节点左子树为空，那么右子树一定为空。且其一定为叶子节点，这是定义
        // 而一个节点的中序后继节点没有左子树，
        v->key[r] = w->key[0];
        v = w; r = 0;        
    } // 此时v处于最底层，删除v
    v->key.erase(v->key.begin());  
    v->child.erase(v->child.begin() + r + 1);  
    solveUnderflow(v);
    return true;
} 

// 节点的下溢，做节点的旋转或者合并处理
template <typename T>
void
BTree<T>::solveUnderflow(BTNodePos(T) v)
{
    if(v->child.size() >= (_order + 1) / 2) // _order + 1) / 2 就是向上取整的操作
        return ; // 递归基:当前节点不满足下溢情况
    BTNodePos(T) p = v->parent; 
    if(!p) // v已经是根节点，此时没有孩子的下限
    {
        if(!v->key.size() && v->child[0])
        {
            // 根节点没有关键码，却有非空孩子，此时应对根节点孩子发生合并的情况。可以直接跳过
            _root = v->child[0]; 
            _root->parent = nullptr; 
            v->child[0] = nullptr; 
            delete v;
        }  
        return ;
    }
    size_t r = 0;
    // 此时v中的目标节点已经被删除了，很可能不含有关键码
    while(p->child[r] != v) r++; // 确定v是p的第几个孩子 
    // 情况1： 左顾，向左兄弟借码
    if(r > 0) // 首先得有左兄弟
    {
        BTNodePos(T) ls = p->child[p->child.begin() + r - 1]; // v的左爹为y, ls的老幺为x
        if(ls->child.size() > (_order + 1) / 2) // 必须大于下限
        {
            v->key.insert(v->key.begin(), p->key[r - 1]);   // v向p借一个码y
            p->key[r - 1] = ls->key[ls->key.size() - 1];    // p向ls借一个码x
            v->child.insert(v->child.begin(), ls->child[ls->child.size() - 1]);//同时将x的右孩子过继给y
            ls->key.erase(ls->key.end() - 1);  
            ls->child.erase(ls->child.end() - 1);  
            if(v->child[0]) v->child[0]->parent = v;   
            return ;
        } 
    }
    // 情况2： 右盼，向右兄弟借码
    if(r < p->child.size() - 1)
    {
        BTNodePos(T) rs = p->child[p->child.begin() + r + 1]; // v的右爹为y，rs的老大为x
        if(rs->child.size() > (_order + 1) / 2) // 右孩子足够胖，大于下限就足够胖
        {
            v->key.insert(v->key.end(), p->key[r]); // 
            p->key[r] = rs->key[0];     
            v->child.insert(v->child.end(), rs->child[0]); // 将x的左孩子过继给y    
            rs->key.erase(rs->key[0]);  
            if(rs->child[0])
                rs->child[0]->parent = v;   
            rs->child.erase(rs->child[0]);  
        } 
    } 
    // 情况3： 左顾右盼失败，要么其没有左右兄弟(但不可能同时)，要么左右兄弟太瘦，此时需要从上面下来一个天使, 合并
    if(0 < r) // 和左兄弟合并，当然也可以先和右兄弟合并，随个人喜好
    {
        BTNodePos(T) ls = p->child[r - 1]; 
        ls->key.push_back(p->key[r - 1]);
        p->key.erase(p->key.begin() + r - 1);  
        ls->child.push_back(v->child[0]);   
        for(int i = 0; i < v->key.size(); ++i)
        {
            ls->key.push_back(v->key[i]); 
            ls->child.push_back(v->child[i+1]);  
        } 
        if(v->child[0])
        {
            for(int i = 0; i < v->child.size(); ++i)
            {
                v->child[i]->parent = ls;  
                delete v->child[i]; 
            } 
            v->child.erase(v->child.begin(), v->child.end());   
        } 
        p->child.erase[p->child.begin() + r];  
    }
    else// 和右兄弟合并
    {
        BTNodePos(T) rs = p->child[r + 1]; 
        rs->key.push_back(p->key[r]); // 把天使先合并过来
        p->key.erase(p->key.begin() + r);  //
        v->child.push_back(rs->child[0]);   
        for(int i = 0; i < rs->key.size(); ++i)
        {
            v->key.push_back(rs->key[i]); 
            v->child.push_back(rs->child[i+1]);  
        } 
        if(rs->child[0])
        {
            for(int i = 0; i < rs->child.size(); ++i)
            {
                rs->child[i]->parent = v;  
                delete rs->child[i]; 
            } 
            rs->child.erase(rs->child.begin(), rs->child.end());   
        } 
        p->child.erase[p->child.begin() + r];  
    }
    solveUnderflow(p);
    return ;
}
