#ifndef myInfixPostfix_H
#define myInfixPostfix_H
#include "myStack.hpp"
#include <iostream>
#include <bits/stdc++.h>
#include <ctype.h>
#include <string>
using namespace std;

class myInfixPostfix
{
private:
  vector<string> postfix_exp;
  myStack <string> stack;
  myStack <float> calculate;
public:
  float result;
  myInfixPostfix(void);
  ~myInfixPostfix();
  string getPostfix(string str);
  float PostfixCalculator(string exp);
  bool isOperand(string s);

};
#endif

//Constrcutor
myInfixPostfix::myInfixPostfix(void)
{
}

//Destructor
myInfixPostfix::~myInfixPostfix()
{

}

//@Pre: Takes in
string myInfixPostfix::getPostfix(string str)
{
  //creates a vector of strings called "tokens"
  vector<string> tokens;
  //takes inputted string and converts to stringstream
  stringstream checkStream(str);
  string intermediate;
  //uses ' ' as a delimmiter to parse string into tokens
  while(getline(checkStream, intermediate, ' '))
  {
    tokens.push_back(intermediate);
  }
  for(int i=0; i<tokens.size(); i++)
  {
    string temp = tokens[i];
    if(isOperand(temp))
    {
      postfix_exp.push_back(temp);
    }
    else if((temp == "+") || (temp=="-"))
    {
      if(stack.empty())
      {
        stack.push(temp);
      }
      else if((stack.top() == "-")||(stack.top() == "+"))
      {
        postfix_exp.push_back(stack.pop());
        stack.push(temp);
      }
      else if((stack.top()== "*")||(stack.top()== "/" ))
      {
        postfix_exp.push_back(stack.pop());
        if(stack.empty())
        {
          stack.push(temp);
        }
        else
        {
          while((stack.top() == "+"||stack.top()=="-"))
          {
            postfix_exp.push_back(stack.pop());
          }
          stack.push(temp);
        }
      }
      else if(stack.top()=="(")
      {
        stack.push(temp);
      }
    }

    else if((temp == "*") || (temp=="/"))
    {
      if(stack.empty())
      {
        stack.push(temp);
      }
      else if((stack.top() == "-")||(stack.top() == "+"))
      {
        stack.push(temp);
      }
      else if((stack.top()== "*")||(stack.top()== "/" ))
      {
        postfix_exp.push_back(stack.pop());
        while(((stack.top() == "*")||(stack.top()=="/"))&&(!stack.empty()))
        {
          postfix_exp.push_back(stack.pop());
        }
        stack.push(temp);
      }
      else if(stack.top()=="(")
      {
        stack.push(temp);
      }
    }
    else if(temp == ")")
    {

      while(stack.top()!= "(")
      {
        postfix_exp.push_back(stack.pop());
      }
      stack.pop();
    }
    else if(temp == "(")
    {
      stack.push(temp);
    }
  }
  while(!stack.empty())
  {
    postfix_exp.push_back(stack.pop());
  }
  string output;
  for(int i=0; i<postfix_exp.size(); i++)
  {
    output += postfix_exp[i]+" ";
    // cout<<postfix_exp[i];
  }
  //cout<<output;
  return output;
}

bool myInfixPostfix::isOperand(string s)
{
  int length = s.length();
  for(int i=0; i<length; i++)
  {
    if(isdigit(s[i])==0)
    {
      return 0;
    }
  }
  return 1;
}
//@Pre: Takes in result of getPostfix as a string
//@Post: Returns the calculation of the postfix expression for line
float myInfixPostfix::PostfixCalculator(string postfix_exp)
{
  //creates a vector of strings called "tokens"
  vector<string> tokens;
  //takes inputted string and converts to stringstream
  stringstream checkStream(postfix_exp);
  string intermediate;
  //uses ' ' as a delimmiter to parse string into tokens
  while(getline(checkStream, intermediate, ' '))
  {
    tokens.push_back(intermediate);
  }
  for(int i=0; i<tokens.size(); i++)
  {
    string temp = tokens[i];

    if(isOperand(temp))
    {
      calculate.push(stoi(temp));
      //cout<<calculate.top()<<endl;
    }
    else if(temp == "+")
    {
      float v1= calculate.pop();
      // cout<<v1<<endl;
      float v2= calculate.pop();
      // cout<<v2<<endl;
      float r1=v1 + v2;
      // cout<<r1<<endl;
      calculate.push(v1 + v2);
    }
    else if(temp == "-")
    {
      float v1= calculate.pop();
      // cout<<v1<<endl;
      float v2= calculate.pop();
        //   cout<<v1<<endl;
      calculate.push(v2 - v1);
    }
    else if(temp == "*")
    {
      float v1= calculate.pop();
      //cout<<v1<<endl;
      float v2= calculate.pop();
      //cout<<v2<<endl;
      //cout<<v1*v2<<endl;
      calculate.push(v1 * v2);
    }
    else if(temp == "/")
    {
      float v1= calculate.pop();
      float v2= calculate.pop();
      calculate.push(v2 / v1);
    }
  }
  //cout<<endl<<calculate.top()<<endl;
  result = calculate.top();
  return result;
}
