#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
template <typename Comparable>
class myBinaryMinHeap //*******************************************************************************************************************#5 X
{
public:
  explicit myBinaryMinHeap( int capacity = 100 ) : array( capacity +1, -1), currentSize{0} //*************************************************#6 X
  {

  }
  explicit myBinaryMinHeap( const vector<Comparable> & items ) : array( items.size( ) + 10 ), currentSize{ items.size( ) }
  {
    for( int i = 0; i < items.size( ); ++i )
      array[ i + 1 ] = items[ i ];
    buildHeap( );
  }
  bool isEmpty( ) const //*****************************************************************************************************************#7 X
  {
    {return currentSize == 0;}
  }
  const Comparable & findMin( ) const  //**************************************************************************************************#8 X
  {
    if( isEmpty( ) )
      std::cerr << "Underflow" << '\n';
    return array[1];
  }
  void insert( const Comparable & x )
  {
    if( currentSize == array.size( ) - 1 )
      array.resize( array.size( ) * 2 );

      // Percolate up
    int hole = ++currentSize;
    Comparable copy = x;

    array[ 0 ] = std::move( copy );
    for( ; x < array[ hole / 2 ]; hole /= 2 )
      array[ hole ] = std::move( array[ hole / 2 ] );
    array[ hole ] = std::move( array[ 0 ] );
  }
  void insert( Comparable && x )  //*******************************************************************************************************#9 X
  {
    if( currentSize == array.size( ) - 1 )
      array.resize( array.size( ) * 2 );

        // Percolate up
    int hole = ++currentSize;
    for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
      array[ hole ] = std::move( array[ hole / 2 ] );
    array[ hole ] = std::move( x );
  }
  void deleteMin( )
  {
    if( isEmpty( ) )
      //throw UnderflowException{ }; //****************************************************************************************************#12
      std::cerr << "Underflow" << '\n';
    array[ 1 ] = std::move( array[ currentSize-- ] );
    percolateDown( 1 );
  }
  void deleteMin( Comparable & minItem )
  {
    if( isEmpty( ) )
      //throw UnderflowException{ }; //****************************************************************************************************#12
      std::cerr << "Underflow" << '\n';
    minItem = std::move( array[ 1 ] );
    array[ 1 ] = std::move( array[ currentSize-- ] );
    percolateDown( 1 );
  }
  void makeEmpty( )  //*******************************************************************************************************************#10 X
  {
    currentSize = 0;
  }

  void levelOrder(std::ostream & outfile)  //**************************************************************************************************#11
  {
    for( int i = 1; i < array.size( ); ++i )
      if(array[i] != -1)
        outfile<<array[i]<<"\n";
  }
private:
  int currentSize;
  vector<Comparable> array;
  // Number of elements in heap
  // The heap array
  void buildHeap( )
  {
    for( int i = currentSize / 2; i > 0; --i )
      percolateDown( i );
  }
  void percolateDown( int hole )
  {
    int child;
    Comparable tmp = std::move( array[ hole ] );

    for( ; hole * 2 <= currentSize; hole = child )
    {
      child = hole * 2;
      if( child != currentSize && array[ child + 1 ] < array[ child ] )
        ++child;
      if( array[ child ] < tmp )
          array[ hole ] = std::move( array[ child ] );
      else
        break;
    }
    array[ hole ] = std::move( tmp );
  }
};
