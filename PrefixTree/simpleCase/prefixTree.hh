#ifndef _PREFIXTREE_HH_
#define _PREFIXTREE_HH_

#include <string> 

using namespace std;
class PTNode 
{ 
public: 
    PTNode ()
    : R {26}
    {
        for(int i = 0; i < R; ++i)
            _indexs[i] = nullptr;
    }

    bool containKey(char ch)
    {
        return _indexs[ch - 'a'] != nullptr;
    }

    PTNode * get(char ch) const
    {
        return _indexs[ch - 'a'];
    }
     
    void put(char ch, PTNode * node)
    {
        _indexs[ch - 'a'] = node;
    }

    void setEnd()
    {
        _isEnd = true; 
    }

    bool isEnd() const
    {
        return _isEnd;
    }


private: 
    const int R;
    bool _isEnd;
    PTNode *_indexs[26];
}; 

class PrefixTree 
{ 
public: 
    PrefixTree ()
    {
        _root = new PTNode{};
    }
    ~PrefixTree ()
    {
        delete _root;
    }
     
    void insert(string word)
    {
        auto temp = _root;
        for(int i = 0; i < (int)word.size(); ++i)
        {
            char currentChar = word[i];
            if(!temp->containKey(currentChar))
            {
                temp->put(currentChar, new PTNode{});
            }
            temp = temp->get(currentChar);
        }
        temp->setEnd();
    }

    // 寻找单词word
    bool search(string word)
    {
        auto node = searchPrefix(word);
        return node != nullptr && node->isEnd();
    }

    // 寻找前缀
    bool startsWith(string word)
    {
        auto node = searchPrefix(word);
        return node != nullptr;
    }
private: 
    // 寻找前缀word
    // 如果找到，则停留在最后一个字母处
    // 如果没找到，则返回nullptr
    PTNode * searchPrefix(string word)
    {
        auto node = _root;
        for(int i = 0; i < (int)word.size(); ++i)
        {
            char currentChar = word[i];
            if(node->containKey(currentChar))
                node = node->get(currentChar);
            else
                return nullptr;
        }
        return node;
    }

private:
    PTNode * _root;
}; 

#endif // prefixTree.hh
