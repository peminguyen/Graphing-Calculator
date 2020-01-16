#ifndef node_h
#define node_h


#include <iostream>

using namespace std;

template <typename T>
struct Node{
    T _item;
    Node<T>* _next;
    
    // Constructor
    Node(T item){
        _item = item;
        _next = NULL;
    }
};

#endif /* node_h */
