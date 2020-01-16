#ifndef queue_h
#define queue_h

#include "node.h"

template <typename T>
class Queue {
public:
    // Iterator class for Queue
    class Iterator{
    public:
        friend class Queue;
        
        // Constructor
        Iterator(Node<T>* p = NULL) {
            _ptr = p;
        }
        
        Iterator(const Iterator& other){
            _ptr = new Node<T>(other._ptr->_item);
        }
        
        Iterator& operator=(const Iterator& other){
            if (this != &other){
                delete _ptr;
                _ptr = new Node<T>(other._ptr->_item);
            }
            return *this;
        }
        // Comparison operators
        operator bool(){
            return _ptr != NULL;
        }
        
        bool isNull(){
            return _ptr == NULL;
        }
        
        // Dereference operator
        T& operator *(){
            return _ptr->_item;
        }
        
        // it++
        friend Iterator operator ++(Iterator& it,
                                    int unused){
            Iterator hold = it;
            it._ptr = it._ptr->_next;
            return hold;
        }
        
        Iterator& operator ++(){                        //++it
            _ptr = _ptr->_next;
            return *this;
        }
        
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
    Queue();
    
    
    // Big 3
    ~Queue();
    Queue(const Queue<T> &copyThis);
    Queue& operator =(const Queue& RHS);
    
    // Add to the rear
    void Push(T i);
    
    // Delete at the front
    T Pop();
    
    // Return the Iterator to the Begin of Queue
    Iterator Begin() const;
    
    // Return the Iterator to the End
    Iterator End() const;
    
    // Get the value at Front
    T getFront();
    
    // Get the value at Rear
    T getRear();
    
    // Check if the Queue is empty
    bool isEmpty() const;
    
    // Copy a Queue
    void CopyQueue(const Queue<T> &copyThis);
    
    // Delete the Queue
    void DeleteQueue();
    
    // Overloading the output operator
    template <typename U>
    friend ostream& operator <<(ostream& outs, const Queue<U>& q);
    
private:
    int size;
    Node<T>* _front;
    Node<T>* _rear;
};

// Constructor
template <typename T>
Queue<T>::Queue() {
    _front = NULL;
    _rear = NULL;
    size = 0;
}

// Destructor
template <typename T>
Queue<T>::~Queue() {
    DeleteQueue();
}

// Copy Constructor
template <typename T>
Queue<T>::Queue(const Queue<T> &copyThis){
    CopyQueue(copyThis);
}

// Overloading assignment operator
template <typename T>
Queue<T>& Queue<T>::operator =(const Queue<T>& RHS){
    // Check for self-assignment
    if (this != &RHS){
        DeleteQueue();
        CopyQueue(RHS);
    }
    return *this;
}

// Add i to the rear
template <typename T>
void Queue<T>::Push(T i) {
    // If the Queue is empty
    if (isEmpty()){
        _front = new Node<T>(i);
        _rear = _front;
    }
    
    
    else {
        // Create node temp and point _rear to temp
        Node<T>* temp = new Node<T>(i);
        _rear->_next = temp;
        _rear = temp;
    }
    
    size++;
}

// Delete at the front
template <typename T>
T Queue<T>::Pop() {
    T item = T();
    
    // if the queue is empty
    if (isEmpty()){
        cout << "Queue is empty! No more to pop" << endl;
    }
    
    else {
        item = _front->_item;
        Node<T>* to_delete = _front;
        _front = _front->_next;
        
        // if the last node is removed
        if (_front == NULL)
            _rear = NULL;
        
        delete to_delete;
        
        size--;
    }
    
    return item;
}

// Return the Iterator to the Begin of Queue
template <typename T>
typename Queue<T>::Iterator Queue<T>::Begin() const {
    return Iterator(_front);
}

// Return the Iterator to the End
template <typename T>
typename Queue<T>::Iterator Queue<T>::End() const {
    return Iterator();
}

// Get the value at Front
template <typename T>
T Queue<T>::getFront(){
    return *Begin();
}

// Get the value at Rear
template <typename T>
T Queue<T>::getRear(){
    return *End();
}

// Check if the Queue is empty
template <typename T>
bool Queue<T>::isEmpty() const{
    return (_front == NULL);
}

// Copy Queue
template <typename T>
void Queue<T>::CopyQueue(const Queue<T> &copyThis){
    if (copyThis.isEmpty())
        _front = _rear = NULL;
    else {
        typename Queue<T>::Iterator it = Iterator(copyThis._front);
        _rear = new Node<T>(*it);
        _front = _rear;
        
        it++;
        
        for (; it != copyThis.End(); it++){
            _rear->_next = new Node<T>(*it);
            _rear = _rear->_next;
        }
    }
}

// Delete the whole queue
template <typename T>
void Queue<T>::DeleteQueue(){
    while(!isEmpty())
        Pop();
}

// Overloading output operator
template <typename U>
ostream& operator <<(ostream& outs, const Queue<U>& q){
    for (typename Queue<U>::Iterator it = q.Begin(); it != q.End(); ++it)
        outs << "[" << *it << "]->";
    
    outs << "|||";
    
    return outs;
}


#endif /* queue_h */
