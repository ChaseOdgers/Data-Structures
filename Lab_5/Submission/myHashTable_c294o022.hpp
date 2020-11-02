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
      theLists.resize(size);
      currentSize = 0;
      //   for(int i=0; i<size; i++){
      //     myDlList<HashedObj> l;
      //     theLists[i] = l;
      //   }
      // currentSize = size;
    }
    bool contains( const HashedObj & x ){
      auto && whichList = theLists[ myhash( x ) ];
      //CHANGE BACK?
      if(whichList.find( whichList.begin(),whichList.end(), x )!= whichList.end()){
        return true;
      }
      else{
        return false;
      }
    }
    void makeEmpty( ){
      for( auto & thisList : theLists )
      thisList.clear( );
    }
    bool insert( const HashedObj & x ){
      auto & whichList = theLists[ myhash( x ) ];
      if( whichList.find( whichList.begin(),whichList.end(), x ) != whichList.end() )
        return false;
      whichList.push_back( x );
      // Rehash; see Section 5.5
      if( ++currentSize > theLists.size( ) )
        rehash( );
      return true;
    }
    bool insert( HashedObj && x ){
      auto && whichList = theLists[ myhash( x ) ];
      if( whichList.find( whichList.begin(),whichList.end(), x ) != whichList.end() )
        return false;
      whichList.push_back(std::move(x));
      // Rehash; see Section 5.5
      if( ++currentSize > theLists.size( ) )
        rehash( );
      return true;
    }
    bool remove( const HashedObj & x ){
      auto & whichList = theLists[ myhash( x ) ];
      auto itr = whichList.find(whichList.begin(),whichList.end(), x );

      if( itr == whichList.end() )
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

    //FIGURE OUT
    bool isPrime(int n){
      if(n<=1){
        return false;
        }
      for(int i=2; i<=n/2; i++)
        {
          if(n%i ==0){
            return false;
            }
        }
        return true;
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
  size_t operator()( const hashitem & key ){
      size_t hashVal = 0;

      for( char ch : key )
        hashVal = 37 * hashVal + ch;
      return hashVal;
    }
};

#endif
