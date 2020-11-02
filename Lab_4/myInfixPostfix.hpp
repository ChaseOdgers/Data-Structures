#ifndef myInfixPostfix_H
#define myInfixPostfix_H
#include "myStack.hpp"
#include <iostream>
//This Library was used for Vector
#include <bits/stdc++.h>
//This library was used for STOI string to integer
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
  string stringToCalc;
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
  //For loop iterates over each token and either pushes to stack, pops from stack, pops from stack and stores in vector or just stores in vector
  for(int i=0; i<tokens.size(); i++)
  {
    //Sets a temp string to the token at tokens[i] at each iteration of for loop
    string temp = tokens[i];
    //Calls isOperand function on temp returning a 1 if the token is a number and a 0 if the token is not a number
    if(isOperand(temp))
    {
      postfix_exp.push_back(temp);
    }
    //Handles + and - tokens
    if((temp == "+") || (temp=="-"))
    {
      //if token is  + or - and stack is empty we just push to stack
      if(stack.empty())
      {
        stack.push(temp);
      }
      //if token is + or - and top of stack is ( we push to stack
      else if(stack.top()=="(")
      {
        stack.push(temp);
      }
      //If token is + or - and top of stack is + or -
      else if((stack.top() == "-")||(stack.top() == "+"))
      {
        // we first pop the stack
        postfix_exp.push_back(stack.pop());
        // Then we check the stack again to make sure the next token at the top of the stack doesnt need to be popped
        while((!stack.empty())&&(stack.top() != "(")&&(stack.top()!= "*")&&(stack.top()!= "/"))
        {
          //pops and adds to vector for output
          postfix_exp.push_back(stack.pop());
        }
        //pushes the + or - to the top of the stack
        stack.push(temp);
      }
      //If token is + or - and top of stack is * or /
      else if((stack.top()== "*")||(stack.top()== "/" ))
      {
        //we pop the stack and add to vector
        postfix_exp.push_back(stack.pop());
        //if the stack is then empty we push our token
        if(stack.empty())
        {
          stack.push(temp);
        }
        else if(stack.top()=="(")
        {
          stack.push(temp);
        }
        //If the top of our stack is + or - after popping
        else if((stack.top() == "+"||stack.top()=="-"))
        {
          //We continue to pop off the + or - until we reach a higher precedence
          while((!stack.empty())&&(stack.top() != "("))
          {
            //pops and adds to vector for output
            postfix_exp.push_back(stack.pop());
          }
          //we then push our value to the Stack
          stack.push(temp);
        }
      }
    }
    //Handles a * and / tokens
    if((temp == "*") || (temp=="/"))
    {
      // if our symbol is * or / and the stack is empty we can push to stack
      if(stack.empty())
      {
        stack.push(temp);
      }
      // If our symbol is * or / and the top of the stack is a ( we push to the stack
      else if(stack.top()=="(")
      {
        stack.push(temp);
      }
      // If our symbol is / or *, they have a higher precedence than + or - so we can just push to the stack
      else if((stack.top() == "-")||(stack.top() == "+"))
      {
        stack.push(temp);
      }
      //If our symbol is / or * and top of stack is / or *
      else if((stack.top()== "*")||(stack.top()== "/" ))
      {
        //we need to first pop and print
        postfix_exp.push_back(stack.pop());
        //after pop we check if stack is empty, if so we push our variable to the top of the stack
        if(stack.empty())
        {
          stack.push(temp);
        }
        //If the top of stack is + or - after pop we just push to stack
        else if((stack.top()=="(")||(stack.top() == "-")||(stack.top() == "+"))
        {
          stack.push(temp);
        }
      }
    }
    //Handles ) tokens
    if(temp == ")")
    {
      //We pop the stack and print it until we find the corresponding left (
      while(stack.top()!= "(")
      {
        postfix_exp.push_back(stack.pop());
      }
      //we then pop the left ( off of the stack
      stack.pop();
    }
    //Handles ( tokens
    if(temp == "(")
    {
      //if ( we just push to stack and wait for )
      stack.push(temp);
    }
  }
//  We then pop everything else off of the stack
  int num_operators_on_stack = stack.getStackCount();
  for(int i=num_operators_on_stack; i>0; i--)
  {
    postfix_exp.push_back(stack.pop());
  }
  // We have stored our tokens in postfix as a vector, the lab expects a string
  // We create a string
  string output;
  //We convert vector to string
  for(int i=0; i<postfix_exp.size(); i++)
  {
    //This preserves a postfix copy for easier calculation
    stringToCalc += postfix_exp[i] + " ";
    // For each token in the vector we append it and a space to the output string
    // If the token is an operand we put it in parentheses
    if(isOperand(postfix_exp[i]))
    {
      output += "("+postfix_exp[i]+")";
    }
    else
    {
      output += postfix_exp[i];
    }
   }
  //We return the string output
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
  string str = postfix_exp;
  //creates a vector of strings called "tokens"
  vector<string> tokens;
  //takes inputted string and converts to stringstream
  stringstream checkStream(stringToCalc);
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
    }
    else if(temp == "+")
    {
      float v1= calculate.pop();
      float v2= calculate.pop();
      float r1=v1 + v2;
      calculate.push(v1 + v2);
    }
    else if(temp == "-")
    {
      float v1= calculate.pop();
      float v2= calculate.pop();
      calculate.push(v2 - v1);
    }
    else if(temp == "*")
    {
      float v1= calculate.pop();
      float v2= calculate.pop();
      calculate.push(v1 * v2);
    }
    else if(temp == "/")
    {
      float v1= calculate.pop();
      float v2= calculate.pop();
      calculate.push(v2 / v1);
    }
  }
  result = calculate.top();
  return result;
}
