#ifndef list_h
#define list_h

#include "node.h"

template <typename T>
class List {
public:
    // Iterator class for list
    class Iterator{
    public:
        friend class List;
        
        // constructor
        Iterator(Node<T>* p = NULL) {
            _ptr = p;
        }
        
        // Comparison operator
        operator bool(){
            return _ptr != NULL;
        }
        
        // Check if the Iterator is NULL
        bool isNull(){
            return _ptr == NULL;
        }
        
        // Dereference operator
        T& operator *(){
            return _ptr->_item;
        }
        
        // Postfix increment operator
        friend Iterator operator ++(Iterator& it, int unused){
            Iterator hold = it;
            it._ptr = it._ptr->_next;
            return hold;
        }
        
        // Prefix increment operator
        Iterator& operator ++(){
            _ptr = _ptr->_next;
            return *this;
        }
        
        // Overloading operators comparing two iterators
        friend bool operator ==(const Iterator& left, const Iterator& right) {
            return left._ptr == right._ptr;
        }
        
        friend bool operator !=(const Iterator& left, const Iterator& right){
            return left._ptr != right._ptr;
        }
        
    private:
        Node<T>* _ptr;
    };
    
    // Default constructor
    List();
    
    // Destructor
    ~List();
    
    // Copy constructor
    List(const List<T> &copyThis);
    
    // Overloading assignment operator
    List& operator =(const List& RHS);
    
    // Insert i to the head of the linked list
    Iterator InsertHead(T i);
    
    // Insert i after the iMarker node
    Iterator InsertAfter(T i, Iterator it);
    
    // Insert i before the iMarker node
    Iterator InsertBefore(T i, Iterator it);
    
    // Delete a node in the linked list pointed by iMarker
    T Delete(Iterator it);
    
    // Clear a linked list
    void Clear();
    
    // Copy a list
    Iterator CopyList(const List<T>& src);
    
    // Search an element in the list and return the pointer to that; If not found return NULL
    Iterator Find(const T &key);
    
    // Overload the subscript operator
    T& operator[](int index);
    
    // Get the head node
    Iterator Begin() const;
    
    // Get the head node
    Iterator End() const;
    
    // Return the pointer to the previous node of node iMarker
    Iterator Prev(Iterator it);
    
    // Overload the output operator to print the list
    template <typename U>
    friend ostream& operator <<(ostream& outs, const List<U>& l);
    
private:
    Node<T>* head;
};


// Default constructor
template <typename T>
List<T>::List(){
    head = NULL;
}


// Destructor
template <typename T>
List<T>::~List(){
    Clear();
}

// Copy Constructor
template <typename T>
List<T>::List(const List<T> &copyThis){
    CopyList(copyThis);
}

// Overloading assignment operator
template <typename T>
List<T>& List<T>::operator =(const List<T>& copyThis){
    // Check for self assignment
    if (this != &copyThis) {
        Clear();
        CopyList(copyThis);
    }
    return *this;
}

// Insert to the head of the list
template <typename T>
typename List<T>::Iterator List<T>::InsertHead(T i){
    // Create temp node
    Node<T>* temp = new Node<T>(i);
    
    // Point next of temp to head
    temp->_next = head;
    
    // Set head to temp
    head = temp;
    
    return Begin();
}

// Insert i after an Iterator position
template <typename T>
typename List<T>::Iterator List<T>::InsertAfter(T i, Iterator it){
    assert(head);
    
    // Create temp node
    Node<T>* temp = new Node<T>(i);
    
    // Find the node pointer that point to position of Iterator it
    Node<T>* iMarker = head;
    while (it != Iterator(iMarker))
        iMarker = iMarker->_next;
    
    // If the position is the last node
    if (iMarker->_next == NULL)
        iMarker->_next = temp;
    
    // Other nodes
    else {
        // Point temp to next node
        temp->_next = iMarker->_next;
        
        // Point mark node to temp
        iMarker->_next = temp;
    }
    
    return Iterator(iMarker->_next);
}

// Insert i before the position of Iterator it
template <typename T>
typename List<T>::Iterator List<T>::InsertBefore(T i, Iterator it){
    assert(head);
    
    // if the node is head
    if (it == Begin())
        return InsertHead(i);
    
    // other nodes
    else {
        
        // Find the previous node pointer to the position of Iterator it
        Node<T>* prev = head;
        while (Iterator(prev->_next) != it)
            prev = prev->_next;
        
        // Create temp node with item i. Insert i after prev node
        Node<T>* temp = new Node<T>(i);
        temp->_next = prev->_next;
        prev->_next = temp;
        
        return Iterator(temp);
    }
}

// Delete a node in the linked list pointed by iMarker
template <typename T>
T List<T>::Delete(typename List<T>::Iterator it) {
    T value;
    
    // Delete head node
    if (it == Begin()) {
        Node<T>* temp = head;
        value = head->_item;
        head = head->_next;
        delete temp;
    }
    
    else {
        
        // Find prev node before the position of Iterator it
        Node<T>* prev = head;
        while (Iterator(prev->_next) != it)
            prev = prev->_next;
        
        // toDelete is the node of Iterator it
        Node<T>* toDelete = prev->_next;
        value = toDelete->_item;
        
        // Delete last node
        if (toDelete->_next == NULL) {
            prev->_next = NULL;
            delete toDelete;
        }
        
        // Delete other nodes
        else {
            prev->_next = toDelete->_next;
            delete toDelete;
        }
    }
    return value;
}


// Copy a linked list
template <typename T>
typename List<T>::Iterator List<T>::CopyList(const List<T> &copyThis){
    
    // If copyThis is NULL
    if (copyThis.head == NULL) {
        head = NULL;
        return Iterator();
    }
    
    
    else {
        // Create new head node for new linked list
        head = new Node<T>(copyThis.head->_item);
        
        // Create node pointers current and currentCopy so they can iterate
        Node<T> *current = head;
        Node<T> *currentCopy = copyThis.head;
        
        while (currentCopy->_next != NULL) {
            current->_next = new Node<T>(currentCopy->_next->_item);
            current = current->_next;
            currentCopy = currentCopy->_next;
        }
        
        return Iterator(current);
    }
}


// Clear a linked list, and set the head to NULL
template <typename T>
void List<T>::Clear(){
    Node<T>* current = head;
    
    while (current != NULL) {
        Node<T>* next = current->_next;
        delete current;
        current = next;
    }
    
    head = NULL;
}



// Search an element in the list and return the Iterator to that position; If not found return a NULL Iterator
template <typename T>
typename List<T>::Iterator List<T>::Find(const T &key) {
    Node<T>* temp = head;
    
    // Iterate temp to find the match item
    while (temp->_item != key && temp->_next != NULL)
        temp = temp->_next;
    
    if (temp->_item == key) // If found, return temp
        return Iterator(temp);
    else
        return Iterator();
}



// Overload the subscript operator
template <typename T>
T& List<T>::operator[](int index){
    Node<T>* current = head;
    int count = 0;
    
    while (current != NULL){
        if (count == index)
            return current->_item;
        count++;
        current = current->_next;
    }
}


// Get Iterator to the Begin node
template <typename T>
typename List<T>::Iterator List<T>::Begin() const{
    return Iterator(head);
}

// Get Iterator to the End
template <typename T>
typename List<T>::Iterator List<T>::End() const{
    return Iterator();
}

// Return the Iterator to the previous node
template <typename T>
typename List<T>::Iterator List<T>::Prev(Iterator it) {
    Node<T>* iMarker = head;
    
    while (it != Iterator(iMarker))
        iMarker = iMarker->_next;
    
    if (iMarker == head)
        return NULL;
    else {
        Node<T> *prev = head;
        
        // Iterate it until it reaches the one before prevToThis
        while(prev->_next != NULL && prev->_next != iMarker)
            prev = prev->_next;
        return prev;
    }
}

// Overloading the output operator
template <typename U>
ostream& operator <<(ostream& outs, const List<U>& l){
    for (typename List<U>::Iterator it = l.Begin(); it != l.End(); ++it)
        outs << "[" << *it << "]->";
    
    outs << "|||";
    
    return outs;
}

#endif /* list_h */
