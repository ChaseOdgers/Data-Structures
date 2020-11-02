#include <iostream>
using namespace std;
template <typename Comparable>
class myBinarySearchTree
{
public:
  myBinarySearchTree( ): root{nullptr}  //**********************************************************#11
  {
  }
  myBinarySearchTree( const myBinarySearchTree & rhs ) : root{nullptr}
  {
    root = clone( rhs.root );
  }
  myBinarySearchTree( myBinarySearchTree && rhs ) : root{rhs.root} //*******************************#12
  {
    rhs.root = nullptr;
  }
  ~myBinarySearchTree( )
  {
    makeEmpty( );
  }

  const Comparable & findMin( ) const   //*******************************************#13
  {
    return findMin( root )->element;
  }
  const Comparable & findMax( ) const   //*******************************************#13
  {
    return findMax( root )->element;
  }

  bool contains( const Comparable & x ) const
  {
    return contains( x, root );
  }
  bool isEmpty( ) const //**********************************************************#14
  {
    return root == nullptr;
  }

  void makeEmpty( ) //**************************************************************#15
  {
    makeEmpty(root);
  }
  void insert( const Comparable & x )
  {
    insert( x, root );
  }
  void insert( Comparable && x ) //*************************************************#16
  {
    insert(std::move(x), root);
  }
  void remove( const Comparable & x )
  {
    remove( x, root );
  }

  myBinarySearchTree & operator=( const myBinarySearchTree & rhs ) //***************#17
  {
    myBinarySearchTree copy = rhs;
    std::swap(*this, copy);
    return *this;
  }
  myBinarySearchTree & operator=( myBinarySearchTree && rhs )  //*******************#17
  {
    std::swap(root,rhs.root);
    return *this;
  }

  void printTreeInorder( ostream & out = cout ) //***********************************#18
  {
    if( isEmpty( ) )
      out << "Empty tree" << endl;
    else
      printTreeInorder( root, out );
  }

  void printTreePreorder( ostream & out = cout ) const//*****************************#19
  {
    if( isEmpty( ) )
      out << "Empty tree" << endl;
    else
      printTreePreorder( root, out );
  }

  void printTreePostorder( ostream & out = cout ) const//****************************#20
  {
    if( isEmpty( ) )
      out << "Empty tree" << endl;
    else
      printTreePostorder( root, out );
  }

private:
  struct BinaryNode
  {
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
      : element{ theElement }, left{ lt }, right{ rt } { }

    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
      : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
  };

  BinaryNode *root;

  void insert( const Comparable & x, BinaryNode * & t )
  {
    if( t == nullptr )
      t = new BinaryNode{ x, nullptr, nullptr };
    else if( x < t->element )
      insert( x, t->left );
    else if( t->element < x )
      insert( x, t->right );
    else
    ; // Duplicate; do nothing
  }
  void insert( Comparable && x, BinaryNode * & t )
  {
    if( t == nullptr )
      t = new BinaryNode{ std::move( x ), nullptr, nullptr };
    else if( x < t->element )
      insert( std::move( x ), t->left );
    else if( t->element < x )
      insert( std::move( x ), t->right );
    else
      ; // Duplicate; do nothing
  }
  void remove( const Comparable & x, BinaryNode * & t )
  {
    if( t == nullptr )
      return; // Item not found; do nothing
    if( x < t->element )
      remove( x, t->left );
    else if( t->element < x )
      remove( x, t->right );
    else if( t->left != nullptr && t->right != nullptr ) // Two children
      {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
      }
    else
    {
      BinaryNode *oldNode = t;
      t = ( t->left != nullptr ) ? t->left : t->right;
      delete oldNode;
    }
  }
  BinaryNode * findMin( BinaryNode *t ) const
  {
    if( t == nullptr )
      return nullptr;
    if( t->left == nullptr )
      return t;
    return findMin( t->left );
  }
  BinaryNode * findMax( BinaryNode *t ) const
  {
    if( t != nullptr )
    while( t->right != nullptr )
    t = t->right;
    return t;
  }
  bool contains( const Comparable & x, BinaryNode *t ) const
  {
    if( t == nullptr )
      return false;
    else if( x < t->element )
      return contains( x, t->left );
    else if( t->element < x )
      return contains( x, t->right );
    else
      return true;  // Match
  }
  void makeEmpty( BinaryNode * & t )
  {
    if( t != nullptr )
      {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
      }
    t = nullptr;
  }
  BinaryNode * clone( BinaryNode *t ) const
  {
    if( t == nullptr )
      return nullptr;
    else
      return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
  }

//Called by public member function, visits the left node, node, then right node
  void printTreeInorder( BinaryNode *t, ostream & out ) const //*********************#18
  {
    if( t != nullptr )
    {
      printTreeInorder( t->left, out );
        out << t->element << endl;
      printTreeInorder( t->right, out );
    }
  }
//Called by public member function, prints node, then left node, then right node
  void printTreePreorder( BinaryNode *t, ostream & out ) const //********************#19
  {
    if( t != nullptr )
    {
      out << t->element << endl;
      printTreePreorder( t->left, out );
      printTreePreorder( t->right, out );
    }
  }
//called by public member function, prints left, right then node 
  void printTreePostorder( BinaryNode *t, ostream & out ) const //*******************#20
  {
    if( t != nullptr )
    {
      printTreePostorder( t->left, out );
      printTreePostorder( t->right, out );
      out << t->element << endl;
    }
  }
};
