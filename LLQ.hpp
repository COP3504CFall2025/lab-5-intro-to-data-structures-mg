#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ(){}

    LLQ(const LLQ<T>& other) {//LLQ obj(a)
        LinkedList<T> newL(other.list);
        list = newL;
    }

    LLQ& operator=(const LLQ<T>& other){//obg = a
        list = other.list;
        return *this;
    }

    LLQ(LLQ<T>&& other) noexcept{
        LinkedList<T> newL(std::move(other.list));
        list = newL;
    }

    LLQ& operator=(LLQ<T>&& other) noexcept{
        list = std::move(other.list);
        return *this;
    }

    ~LLQ(){}

    void PrintForward(){list.printForward();}
    void PrintReverse(){list.printReverse();}

    // Insertion
    void enqueue(const T& item) override{
        list.addTail(item);
    }

    // Deletion
    T dequeue() override{
        T t = peek();
        list.removeHead();
        return t;
    }

    // Access
    T peek() const override{
        return list.getData();
    }

    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }

};