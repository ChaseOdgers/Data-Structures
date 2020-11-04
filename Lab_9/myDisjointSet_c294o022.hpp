//chase odgers lab9 eecs 560
#include <iostream>
#include <vector>
using namespace std;

class myDisjointSet
{
  public:
    explicit myDisjointSet( int numElements ) : s(numElements, -1)
    {

    }
    int find( int x ) const
    {
        if( s[ x ] < 0 )
            return x;
        else
            return find( s[ x ] );
    }
    int find( int x )
    {
        if( s[ x ] < 0 )
          return x;
        else
          return s[ x ] = find( s[ x ] );
    }
    void unionSets( int root1, int root2 )
    {
      if(root1 == root2)
      {
        return;
      }
      if(s[root2] < s[root1])
      {
        s[root2] += s[root1];
        s[root1] = root2;
      }
      else{
        s[root1] += s[root2];
        s[root2] = root1;
      }
    }

    int getNumberElements() const
    {
      return s.size();
    }

    void print(int i)
    {
      if(s[i] >= 0)
      {
        cout<<i<<endl;
        cout<<find(i)<<endl;
      }
      else
      {
        cout<<find(i)<<endl;
      }
    }

    int  getSetSize(int i) const
    {
      return -s[find(i)];
    }


  private:
    vector<int> s;
};
