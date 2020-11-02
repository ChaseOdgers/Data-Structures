//CHASE ODGERS LEFTIST HEAP
#include <iostream>
#include <fstream>
using namespace std;

template <typename Comparable>
class myLeftistHeap
{
  public:
    myLeftistHeap( ) : root{ nullptr }
      {

      }
    myLeftistHeap( const myLeftistHeap & rhs )
      {
        root = clone(rhs.root);
      }
    myLeftistHeap( myLeftistHeap && rhs )
      {
        root = clone(rhs.root);
      }

    ~myLeftistHeap( )
      {
        makeEmpty();
      }

    myLeftistHeap & operator=( const myLeftistHeap & rhs )
      {
        root = clone(rhs.root);
        return *this;
      }
    myLeftistHeap & operator=( myLeftistHeap && rhs )
      {
        root = clone(rhs.root);
        return *this;
      }

    bool isEmpty( ) const
      {
        return root == nullptr;
      }
    const Comparable & findMin( ) const
      {
        if(!isEmpty())
          //std::cerr << "Underflow1" << '\n';
          return root->element;
      }

    void insert( const Comparable & x )
      {
        root = merge( new LeftistNode{ x }, root );
      }
    void insert( Comparable && x )
      {
        root = merge( new LeftistNode{ std::move(x) }, root);
      }
    void deleteMin( )
      {
        if( isEmpty( ) )
            return;

        LeftistNode *oldRoot = root;
        root = merge( root->left, root->right );
        delete oldRoot;
      }
    void deleteMin( Comparable & minItem )
      {
        minItem = findMin( );
        deleteMin( );
      }
    void makeEmpty( )
      {
        reclaimMemory(root);
        root = nullptr;
      }
    void merge( myLeftistHeap & rhs )
      {
        if( this == &rhs )
        // Avoid aliasing problems
          return;
        root = merge( root, rhs.root );
        rhs.root = nullptr;
      }
    void printInOrder()
      {
        if(isEmpty())
          cout<<"Tree is Empty"<<endl;
        else
         printInOrder(root);
        // //system.out.println()
         //cout<<endl;
      }
    void printLevelOrder()
      {
        if(isEmpty())
          cout<<"Tree is Empty"<<endl;
        else
         printLevelOrder(root);
        // //system.out.println()
        // cout<<endl;
      }
  private:
      struct LeftistNode
      {
        Comparable  element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;
        bool deleted;//********************************************************************
        LeftistNode( const Comparable & e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0 ): element{ e }, left{ lt }, right{ rt }, npl{ np } { }
        LeftistNode( Comparable && e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0 ): element{ std::move( e ) }, left{ lt }, right{ rt }, npl{ np } { }
        };
      void printInOrder(LeftistNode *r)
      {
         if (r != nullptr )
         {
           printInOrder(r->left);
           cout<<r->element<<endl;
           printInOrder(r->right);
         }
      }

      void printLevelOrder(LeftistNode *r)
      {
         for(int i=1; i<= levelHeight(root);i++)
         {
           printGivenLevel(r, i);
         }
      }

      void printGivenLevel(LeftistNode *r, int level)
      {
        if(r == nullptr)
        {
          return;
        }
        if(level == 1)
        {
          cout<<r->element<<endl;
        }
        else if (level > 1)
        {
          printGivenLevel(r->left, level-1);
          printGivenLevel(r->right, level-1);
        }
      }
    int levelHeight(LeftistNode *r)
    {
      if(r == nullptr)
      {
        return 0;
      }
      else
      {
        int leftHeight = levelHeight(r->left);
        int rightHeight = levelHeight(r->right);
        if(leftHeight > rightHeight)
          return (leftHeight + 1);
        else return(rightHeight +1);
      }
    }

    LeftistNode *root;

    LeftistNode * merge( LeftistNode *h1, LeftistNode *h2 )
    {
      if( h1 == nullptr )
        return h2;
      if( h2 == nullptr )
        return h1;
      if( h1->element < h2->element )
        return merge1( h1, h2 );
      else
        return merge1( h2, h1 );
    }
    LeftistNode * merge1( LeftistNode *h1, LeftistNode *h2 )
    {
      if( h1->left == nullptr )
      // Single node
        h1->left = h2;
      // Other fields in h1 already accurate
      else
      {
        h1->right = merge( h1->right, h2 );
        if( h1->left->npl < h1->right->npl )
          swapChildren( h1 );
        h1->npl = h1->right->npl + 1;
      }
      return h1;
    }

    void swapChildren( LeftistNode *t )
    {
      LeftistNode *tmp = t->left;
     t->left = t->right;
     t->right = tmp;
    }
    void reclaimMemory( LeftistNode *t )
    {
      if( t != nullptr )
      {
        reclaimMemory( t->left );
        reclaimMemory( t->right );
        delete t;
      }
    }
    LeftistNode * clone( LeftistNode *t ) const
    {
      if( t == nullptr )
        return nullptr;
      else
        return new LeftistNode{ t->element, clone( t->left ), clone( t->right ), t->npl };
    }
};
