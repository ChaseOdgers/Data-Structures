#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "myDlList.hpp"
using namespace std;


//Seperate chaining hashtable with methods
template <typename HashedObj>
class myHashTable
{
  private:
    vector<myDlList<HashedObj>> theLists;
    int currentSize;
    // The array of Lists
    void rehash( ){
      vector<myDlList<HashedObj>> oldLists = theLists;

      // Create new double-sized, empty table
      theLists.resize( nextPrime( 2 * theLists.size( ) ) );
      for( auto & thisList : theLists )
        thisList.clear( );

      // Copy table over
      currentSize = 0;
      for( auto & thisList : oldLists )
        for( auto & x : thisList )
          insert( std::move( x ) );
    }
    size_t myhash( const HashedObj & x ) const{
      static hash<HashedObj> hf;
      return hf( x ) % theLists.size( );
    }
  public:
    explicit myHashTable( int size = 101 ){
        for(int i=0; i<size; i++){
          myDlList<HashedObj> l;
          theLists[i] = l;
        }
      currentSize = size;
    }
    bool contains( const HashedObj & x ){
      auto & whichList = theLists[ myhash( x ) ];
      if(myDlList<HashedObj>::finds( whichList.begin(),whichList.end(), x ) != nullptr)
    }
    void makeEmpty( ){
      for( auto & thisList : theLists )
      thisList.clear( );
    }
    bool insert( const HashedObj & x ){
      auto & whichList = theLists[ myhash( x ) ];
      if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) )
        return false;
      whichList.push_back( x );
      // Rehash; see Section 5.5
      if( ++currentSize > theLists.size( ) )
        rehash( );
      return true;
    }
    bool insert( HashedObj && x ){
      auto && whichList = theLists[ myhash( x ) ];
      if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) )
        return false;
      whichList.push_back( x );
      // Rehash; see Section 5.5
      if( ++currentSize > theLists.size( ) )
        rehash( );
      return true;
    }
    bool remove( const HashedObj & x ){
      auto & whichList = theLists[ myhash( x ) ];
      auto itr = find( begin( whichList ), end( whichList ), x );

      if( itr == end( whichList ) )
        return false;
      whichList.erase( itr );
      --currentSize;
      return true;
    }
    int nextPrime(int n){
      if(n<=1){return 2;}
      int p = n;
      bool found = false;
      while(!found){
        p++;
        if(isPrime(p))
          found =true;
      }
      return p;
    }
    bool isPrime(int n){
      if(n <= 1){return false;}
      if(n <= 3){return true;}
      if(n%2==0 || n%3==0){return false;}
      for(int i=5; i*i<=n; i=i+6){if(n%i==0 || n%(i+2)==0){return false;}return true;}
    }
    typename myDlList<HashedObj>::iterator getiteratorbegin(int index){
      return theLists[index].begin();
    }
    typename myDlList<HashedObj>::iterator getiteratorend(int index){
      return theLists[index].end();
    }
    int hashsize(){
      return theLists.size();
    }
};

template<typename hashitem>
class hash
{
  public:
  size_t operator()( const string & key ){
      size_t hashVal = 0;

      for( char ch : key )
        hashVal = 37 * hashVal + ch;
      return hashVal;
    }
};

#endif
