#ifndef _TRIE_HH_
#define _TRIE_HH_ 

#include <string> 
#include <queue> 

using std::queue; 
using std::string; 

template <typename Value>
class Trie 
{ 
private: 
    static const int R = 26;
public:
    struct Node 
    { 
    public: 
        Node (Value *val = nullptr)
        : value{ val }
        {
            for(int i = 0; i < R; ++i)
                links[i] = nullptr;
        }
        ~Node ()
        {
            if(value)
                delete value;
            for(int i = 0; i < R; ++i)
                if(links[i])
                    delete links[i];
        }
        
        Value *value;
        Node *links[R];
    }; 

private:
    Node * _root;
public: 
    Trie ()
    {
        _root = new Node;
    }

    // 根据返回值是否是nullptr查看查找是否成功
    Value * get(const string &key)
    {
        auto node = get(_root, key, 0);
        return node->value;
    }

    // 插入 
    void put(const string & key, const Value & val)
    {
        if(key.empty()) return;
        put(_root, key, val, 0);
    }

    queue<string> *keys()
    {
        queue<string> *q = new queue<string>;
        collect(_root, "", q);
        return q;
    }

    // 找到所有以pre为前缀的keys
    queue<string> *keysWithPrefix(string pre)
    {
        queue<string> * q = new queue<string>;
        collect(get(_root, pre, 0), pre, q);
        return q;
    }

    // 找到所有匹配pat的keys , "."代表任意字符
    queue<string> *keysThatMatch(string pat)
    {
        queue<string> * q = new queue<string>;
        collect(_root, "", pat, q);
        return q;
    }

    // 找到s的最长前缀key
    string longestPrefixOf(string s)
    {
        int length = search(_root, s, 0, 0);
        return s.substr(0, length);
    }
private:
    // 从节点x出发， 寻找key是否存在，d代表从key的第几个字符开始
    Node * get(Node *x, const string &key, int d)
    {
        if(!x) return nullptr;
        if(d == key.size()) return x;
        char currentChar = key[d];
        return get(x->links[currentChar - 'a'], key, d + 1);
    }

    Node * put(Node *&x, const string &key, const Value &val, int d)
    {
        if(x == nullptr) x = new Node{};
        if(d == key.size()) {   x->value = new Value{val}; return x;  }
        char currentChar = key[d];
        put(x->links[currentChar - 'a'], key, val, d + 1);
        return x;
    }

    void collect(Node *x, string pre, queue<string> *q)
    {
        if(x == nullptr)   return;
        if(x->value) q->push(pre);
        for(char c = 'a'; c < 'a' + R; ++c)
            collect(x->links[c - 'a'], pre + c, q);
    }

    void collect(Node *x, string pre, string pat, queue<string> *q)
    {
        int d = pre.size();
        if( nullptr == x) return;
        if( d == pat.size() && nullptr != x->value) q->push(pre);
        if( d == pat.size()) return ;

        char next = pat[d];
        for(char c = 'a'; c < 'a' + R; c++)
            if('.' == next || next == c)
                collect(x->links[c - 'a'], pre + c, pat, q);
    }

    int search(Node *x, const string &s, int d, int length)
    {
        if(nullptr == x)    return length;
        if(x->value)    length = d;
        if(d == s.size()) return length;
        char currentChar = s[d];
        return search(x->links[currentChar - 'a'], s, d + 1, length);
    }
}; 
#endif // Trie.hh
