#ifndef stack_h
#define stack_h

#include "list.h"
#include "node.h"

template <typename T>
class Stack{
public:
    // Iterator for Stack
    class Iterator{
    public:
        friend class Stack;
        
        // constructor
        Iterator(typename List<T>::Iterator p = typename List<T>::Iterator()) {
            _ptr = p;
        }
        
        // Comparison operator
        operator bool(){
            return (_ptr);
        }
        
        // Check if the Iterator is NULL
        bool isNull(){
            return _ptr.isNull();
        }
        
        //dereference operator
        T& operator *(){
            return *_ptr;
        }
        
        // Postfix increment operator
        friend Iterator operator ++(Iterator& it, int unused){
            Iterator hold = it;
            it._ptr++;
            return hold;
        }
        
        // Prefix increment operator
        Iterator& operator ++(){                        //++it
            _ptr++;
            return *this;
        }
        
        // Overloading comparison operators to check whether two Iterators are the same or not
        friend bool operator ==(const Iterator& left,
                                const Iterator& right) {
            return left._ptr == right._ptr;
        }
        
        friend bool operator !=(const Iterator& left,   //it != it
                                const Iterator& right){
            return left._ptr != right._ptr;
        }
        
    private:
        typename List<T>::Iterator _ptr;
    };
    
    // Constructor
    Stack();
    
    // Clear the whole stack
    void Clear();
    
    // Add to the top
    void Push(const T& i);
    
    // Delete at the top
    T Pop();
    
    // Get the top
    T getTop();
    
    // Get the size of the stack
    int getSize();
    
    // Return the Iterator to the Begin of Stack
    Iterator Begin() const;
    
    // Return the Iterator to the End of Stack
    Iterator End() const;
    
    // Check if the Stack is empty
    bool isEmpty();
    
    // Overloading the output operator
    template <typename U>
    friend ostream& operator <<(ostream& outs, const Stack<U>& s);
    
private:
    int size;
    List<T> _stack;
};

// Constructor
template <typename T>
Stack<T>::Stack() {
    size = 0;
    _stack = List<T>();
}

// Clear the whole stack
template <typename T>
void Stack<T>::Clear(){
    _stack.Clear();
}
// Add to the top
template <typename T>
void Stack<T>::Push(const T& i){
    size++;
    _stack.InsertHead(i);
}

// Delete at the top
template <typename T>
T Stack<T>::Pop() {
    T temp = T();
    if (isEmpty()){
        cout << "The stack is empty."<< endl;
    }
    else {
        size--;
        temp = getTop();
        _stack.Delete(_stack.Begin());
    }
    return temp;
}

// Get the size of the stack
template <typename T>
int Stack<T>::getSize(){
    return size;
}

// Get the top
template <typename T>
T Stack<T>::getTop(){
    return *Begin();
}

// Return the Iterator to the Begin of Stack
template <typename T>
typename Stack<T>::Iterator Stack<T>::Begin() const{
    return Iterator(_stack.Begin());
}

// Return the Iterator to the End of Stack
template <typename T>
typename Stack<T>::Iterator Stack<T>::End() const{
    return Iterator();
}

// Check if the Stack is empty
template <typename T>
bool Stack<T>::isEmpty(){
    return Begin().isNull();
}

// Overloading the output operator
template <typename U>
ostream& operator <<(ostream& outs, const Stack<U>& s){
    for (typename Stack<U>::Iterator it = s.Begin(); it != s.End(); ++it){
        outs << "[" << *it << "]->";
    }
    outs << "|||";
    return outs;
}

#endif /* stack_h */
