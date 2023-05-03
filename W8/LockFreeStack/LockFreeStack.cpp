// LockFreeStack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <atomic>
#include <thread>

template<typename T>
struct node
{
    T data;
    node* next;
    node(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
class stack
{
    std::atomic<node<T>*> head;
public:
    void push(const T& data)
    {
        node<T>* new_node = new node<T>(data);

        new_node->next = head.load(std::memory_order_relaxed);

        while (!head.compare_exchange_weak(new_node->next, new_node,std::memory_order_release,std::memory_order_relaxed)); //Body is Empty
    }

    void pop()
    {
        node<T>* nodeToPop = head.load(std::memory_order_relaxed);
        node<T>* new_node = nodeToPop->next;
        while (!head.compare_exchange_weak(nodeToPop, new_node, std::memory_order_release, std::memory_order_relaxed)); //Body is Empty
    }

    T top()
    {
        node<T>* nodeAtTop = head.load(std::memory_order_relaxed);
        return nodeAtTop->data;
    }
};


stack<int> s;

void TestThreads()
{
    s.push(1);
    s.push(2);
    s.pop();
    s.push(3);
    s.pop();
    s.push(4);
    std::cout << s.top() << std::endl;
}

int main()
{
    std::thread thread1(TestThreads);
    std::thread thread2(&TestThreads);
    std::thread thread3(&TestThreads);

    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << s.top() << std::endl;
}
