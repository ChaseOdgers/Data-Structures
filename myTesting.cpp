#include <iostream>
#include <vector>
using namespace std;
vector<int> s {-1,-1,-1,2,3,4,4,6};


int  getSetSize(int i)
{
  int count=0;
  for(int x=0; x<7; x++)
  {
    if(s[x] == i)
    {
      count += getSetSize(x);
    }
  }
  return count+1;
}

int main()
{
  //cout<<s[0]<<endl;
  cout<<getSetSize(0)<<endl;
  cout<<getSetSize(1)<<endl;
  cout<<getSetSize(2)<<endl;
  cout<<getSetSize(3)<<endl;
  cout<<getSetSize(4)<<endl;
  cout<<getSetSize(5)<<endl;
  cout<<getSetSize(6)<<endl;
  cout<<getSetSize(7)<<endl;
}
