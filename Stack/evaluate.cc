//c++ program
//design by >^.^<
//@date    2018-09-15 15:25:58
#include "stack.cc" 

#include <cmath> 
#include <cstdio> 
#include <iostream>
#include <cctype> 

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

void readNumber(char *&s, Stack<float> &opnd)
{
    opnd.push(static_cast<float>(*s - '0'));
    while(isdigit(*(++s)))
    {
        opnd.push(opnd.pop() * 10 + *s - '0');
    }
    if(*s != '.')
        return ;
    float fraction = 1;
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

float eval(float op1, char op, float op2)
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

float fac(float num) // 懒得写了，递归了
{
    if(num == 0)
        return 1;
    return num * fac(num - 1);
}
float eval(char op, float op1)
{
    if(op == '!')
        return fac(op1);
    return -1;
}

void process(char *&s, Stack<char> &optr, Stack<float> &opnd)
{
    int rop = convert(*s);
    int lop; 
    lop = convert(optr.top());
    switch(pri[lop][rop])
    {
        case '<' :
            optr.push(*s);
            ++s;
            break;
        case '>' :
            if(optr.top() == '!')
            {
                float op1 = opnd.pop();
                char opchar = optr.pop();
                opnd.push(eval(opchar, op1));
            }
            else{
                float op2 = opnd.pop(); float op1 = opnd.pop();
                char opchar = optr.pop();
                opnd.push(eval(op1, opchar, op2));
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

float evaluate(char * S)
{
    Stack<float> opnd; 
    Stack<char> optr;
    optr.push('#');
    char *idx = S;
    while(!optr.empty())
    {
        if(isdigit(*idx))
        {
            readNumber(idx, opnd);
        }
        else{
            process(idx, optr, opnd);
        }
    }

    return opnd.top();
}

void testReadNumber()
{
    char str[100];
    scanf("%s", str);
    char *ss = str;
    Stack<float> opnd;
    readNumber(ss, opnd);
    cout << opnd.top() << endl;
}
int main()
{
    char str[1000];
    while(scanf("%s", str))
    {
        printf("%f\n", evaluate(str));
        memset(str, 0, sizeof(str));
    }
    return 0;
}
