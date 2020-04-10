#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;


template<class Object>
class Queue{
    public:
        Queue();
        ~Queue();

        bool isEmpty();
        const Object& GetFront() const;
        void enqueue(const Object &x);
        Object dequeue();
        void makeEmpty();
  private:
    struct ListNode
    {
        Object element;
        ListNode *next;
        ListNode(const Object &theElement,ListNode *n=0)
        :element(theElement),next(n){}
    };
    ListNode *front;
    ListNode *back;
};

template<class Object>
Queue<Object>::Queue()
{
    front = back = 0;
}

template<class Object>
Queue<Object>::~Queue()
{
    makeEmpty();
}

template<class Object>
void Queue<Object>::makeEmpty()
{

}
template<class Object>
bool Queue<Object>::isEmpty()
{
    return front == 0;
}

template<class Object>
const Object& Queue<Object>::GetFront() const
{
    
}

template<class Object>
void Queue<Object>::enqueue(const Object &x)
{
    if(isEmpty)
    {
        back = front = new ListNode(x);
    }
    else
    {
        back = back->next = new ListNode(x);
    }
    
}

template<class Object>
Object Queue<Object>::dequeue()
{
    Object old = GetFront();
    front = front->next;

}

int main()
{
    return 0;
}