#include "myStack.hpp"
#include<iostream>
using namespace std;

int main()
{
  myStack <string> stack;
  stack.push("1");
  stack.push("2");
  cout<<stack.top()<<endl;
  stack.clear();
  cout<<stack.top()<<endl;
  // stack.push("3");
  // stack.push("4");
  // stack.push("5");
  // stack.push("6");
  // stack.push("7");
  // stack.push("8");
  // stack.push("9");
  // stack.push("10");
  // stack.push("11");
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
  // cout<<stack.pop()<<endl;
}
