#ifndef _HASHTABLE_HH_
#define _HASHTABLE_HH_

#include <cstdio> 
#include <utility> 
#include <vector> 
using std::pair; 
using namespace std;

static int primeNLT(int c);

// 线性试探发
template <typename K, typename V>
class Hashtable 
{ 
private: 
    pair<K, V> ** _bucketArr; // 桶数组，存放词条指针    
    int _bucketArrSize; // 桶数组容量
    int _entrySize; // 词条数量
    vector<char> _bitmap;// bitmap // 懒惰删除标记

protected:
    int probe4Hit(const K & key); // 沿关键码key对应的查找链，找到词条匹配的桶
    int probe4Free(const K & key); // 沿关键码key对应的查找链，找到首个可用的空桶
    void rehash(); // 重散列算法：扩充桶数组，保证装填因子在警戒线之下

public: 
    Hashtable (int c = 5);  //创建一个容量不小于c的散列表
    ~Hashtable ();  // 释放桶数组及其中各（非空）元素所指向的词条
    int size() const    {   return _entrySize;  } // 当前的词条数目
    bool put(K, V); // 禁止雷同词条，故可能失败
    V * get(K k); // 读取
    bool remove(K k); // 删除
    // for test
    void testprint()
    {
        for(int i = 0; i < _bucketArrSize; ++i)
            if(_bucketArr[i])
                printf("%3d", _bucketArr[i]->second);
        printf("\n");
    }
}; 

template <typename K, typename V>
Hashtable<K, V>::Hashtable(int c)
{
    // 这里直接采用计算素数的方法，实际我们可以计算出一定数量的素数，存放在一个文件中，直接查询使用
    _bucketArrSize = primeNLT(c); // primeNLT可以得到一个不小于c的素数M
    _entrySize = 0;
    _bucketArr = new pair<K, V> *[_bucketArrSize]; // 开辟桶数组，初始装填因子为N/M
    memset(_bucketArr, 0, sizeof(pair<K, V> *) * _bucketArrSize); // 初始化各桶
    _bitmap.resize(_bucketArrSize);
    for(int i = 0; i < _bucketArrSize; ++i)
        _bitmap[i] = 0;
} 

static bool isSushu(int c)
{
    for(int i = 2; i < c; ++i)
    {
        if(c % i == 0)
            return false;
    }
    return true;
}
static int primeNLT(int c)
{
    int i = c + 1;
    while(true)
    {
        if(isSushu(i))
            return i;
        else
            ++i;
    }
}

template <typename K, typename V>
Hashtable<K, V>::~Hashtable()
{
    for(int i = 0; i < _bucketArrSize; ++i)
    {
        if(_bucketArr[i])
            delete _bucketArr[i]; // 释放非空的桶
    }
    delete []_bucketArr; // 释放桶数组
}

template <typename K, typename V>
int 
Hashtable<K, V>::probe4Hit(const K & key) // 沿关键码key对应的查找链，找到词条匹配的桶
{
    int r = static_cast<int>(key) % _bucketArrSize;
    while( (_bucketArr[r] && _bucketArr[r]->first != key) || (!_bucketArr[r] && _bitmap[r]) )
    {
        r = (r + 1) % _bucketArrSize;
    }
    return r; // 根据调用_bucketArrSize 是否为空，就可以知道查找是否成功了
}

template <typename K, typename V>
V *
Hashtable<K, V>::get(K k) // 散列表查找算法
{
    int r = probe4Hit(k);
    return _bucketArr[r] ? &(_bucketArr[r]->second) : nullptr; // 禁止词条的key值雷同
} 

template <typename K, typename V>
bool 
Hashtable<K, V>::remove(K k) // 删除
{
    int r= probe4Hit(k);
    if(!_bucketArr[r])
        return false;
    delete _bucketArr[r];
    _bucketArr[r] = nullptr;
    _entrySize--;
    _bitmap[r] = 1;
    return true;
}

template <typename K, typename V>
bool 
Hashtable<K, V>::put(K key, V value) // 禁止雷同词条，故可能失败
{
    if(_bucketArr[probe4Hit(key)]) return false; 
    int r = probe4Free(key);
    _bucketArr[r] = new pair<K, V>{key, value};
    ++_entrySize;
    // 装填因子如果大于50%， 则进行重散列
    return true;
}

template <typename K, typename V>
int 
Hashtable<K, V>::probe4Free(const K & key) // 沿关键码key对应的查找链，找到首个可用的空桶
{
    int r = static_cast<int>(key) % _bucketArrSize; // 从起始桶出发
    while(_bucketArr[r]) r = ( r + 1 ) % _bucketArrSize; // 沿查找链逐桶查找，不care删除标记
    return r;
}
#endif // hashTable.hh
