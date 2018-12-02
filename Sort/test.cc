//c++ program
//design by >^.^<
//@date    2018-10-17 19:39:49
#include <iostream>
#include <vector> 

using namespace std;

int main()
{
    vector<int> vec ={1, 2, 3, 4, 5};
    vector<int>::iterator iter= vec.begin() + 2; 
    cout << iter[2] << endl;
    return 0;
}

