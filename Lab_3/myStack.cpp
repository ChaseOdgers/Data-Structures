#include "myStack.hpp"
#include<iostream>
using namespace std;

template<typename T>
myStack<T>::myStack(void)
{
  size=10;
  s_ptr=new T[size];
  head=-1;
}

template<typename T>
myStack<T>::~myStack()
{
  delete[] s_ptr;
}

template<typename T>
void myStack<T>::push(T val)
{
  if(!isfull())
  {
    s_ptr[++head]=val;
  }
  else
  {
    cout<<"myStack is full\n";
  }
}

template<typename T>
T myStack<T>::pop()
{
  if(!empty())
  {
    return s_ptr[head--];
  }
  else
  {
    cout<<"myStack is empty";
  }
}

template<typename T>
bool myStack<T>::isfull()
{
  return head==size-1;
}

template<typename T>
bool myStack<T>::empty()
{
  return head==-1;
}

template<typename T>
T myStack<T>::top()
{
  if(!empty())
  {
    return s_ptr[head];
  }
  else
  {
    return NULL;
  }
}

template<typename T>
void myStack<T>::clear()
{
  // while(top != NULL)
  // {
  //   temp = top;
  //   top = s_ptr[head--];
  //   delete temp;
  // }
}
