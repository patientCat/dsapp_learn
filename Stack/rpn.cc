//c++ program
//design by >^.^<
//@date    2018-09-15 15:25:58
#include "stack.cc" 

#include <cmath> 
#include <cstdio> 
#include <iostream>
#include <cctype> 
#include <cstring> 

#define N_OPTR 9
using Operator = enum {Add, Sub, Mul, Div, Pow, Fac, Lp, Rp, Eoe};

const char pri[N_OPTR][N_OPTR] = {
         /*add  sub  mul  div  pow  fac  lp   rp   eoe*/
/*add*/    {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
/*sub*/    {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
/*mul*/    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
/*div*/    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
/*pow*/    {'>', '>', '>', '>', '>', '<', '<', '>', '>'},
/*fac*/    {'>', '>', '>', '>', '>', '>', ' ', '>', '>'},
/*lp*/     {'<', '<', '<', '<', '<', '<', '<', '=', ' '},
/*rp*/     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
/*eoe*/    {'<', '<', '<', '<', '<', '<', '<', ' ', '='},
 };

using namespace std;

void readNumber(char *&s, Stack<int> &opnd)
{
    opnd.push(static_cast<int>(*s - '0'));
    while(isdigit(*(++s)))
    {
        opnd.push(opnd.pop() * 10 + *s - '0');
    }
    if(*s != '.')
        return ;
    int fraction = 1;
    while(isdigit(*++s))
    {
        fraction = fraction / 10;
        opnd.push(opnd.pop() + (*s - '0') * fraction);
    }
}

int convert(char c)
{
    Operator op;
    switch(c)
    {
        case '+' : op = Add; break;
        case '-' : op = Sub; break;
        case '*' : op = Mul; break;
        case '/' : op = Div; break;
        case '^' : op = Pow; break;
        case '!' : op = Fac; break;
        case '(' : op = Lp;  break;
        case ')' : op = Rp;  break;
        case '$' : op = Eoe; break;
        case '#' : op = Eoe; break;
    }
    return op;
}

int eval(float op1, char op, float op2)
{
    switch(op)
    {
        case '+' :
            return op1 + op2;
        case '-' :
            return op1 - op2;
        case '*' :
            return op1 * op2;
        case '/' : 
            return op1 / op2;
        case '^' :
            return pow(op1, op2);
    }
    return -1;
}

int fac(float num) // 懒得写了，递归了
{
    if(num == 0)
        return 1;
    return num * fac(num - 1);
}
int eval(char op, float op1)
{
    if(op == '!')
        return fac(op1);
    return -1;
}

void append(char *&RPN, char a)
{
    RPN[strlen(RPN)] = a;
}

void append(char *&RPN, int a)
{
    char tmp[100] = {0};
    sprintf(tmp, "%d", a);
    int len = strlen(RPN);
    for(size_t i = 0; i < strlen(tmp); ++i)
        RPN[len + i] = tmp[i];
}

void process(char *&s, Stack<char> &optr, Stack<int> &opnd, char *&RPN)
{
    int rop = convert(*s);
    int lop; char op;
    lop = convert(optr.top());
    switch(pri[lop][rop])
    {
        case '<' :
            optr.push(*s);
            ++s;
            break;
        case '>' :
            {
            op = optr.pop();
            append(RPN, op);
            }
            break;
        case '=' :
            optr.pop(); 
            ++s;
            break;
        case ' ' ://非法情况
            cout << "illegal expression" << endl;
            exit(-1);
    }
}

int evaluate(char * S, char *RPN)
{
    Stack<int> opnd; 
    Stack<char> optr;
    optr.push('#');
    char *idx = S;
    while(!optr.empty())
    {
        if(isdigit(*idx))
        {
            readNumber(idx, opnd);
            append(RPN, opnd.top());
        }
        else{
            process(idx, optr, opnd, RPN);
        }
    }

    return opnd.top();
}

void testReadNumber()
{
    char str[100];
    scanf("%s", str);
    char *ss = str;
    Stack<int> opnd;
    readNumber(ss, opnd);
    cout << opnd.top() << endl;
}
int main()
{
    char str[1000];
    char RPN[100];
    while(scanf("%s", str))
    {
        evaluate(str, RPN);
        printf("%s\n", RPN);
        memset(str, 0, sizeof(str));
        memset(str, 0, sizeof(RPN));
    }
    return 0;
}
