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

    void PrintForward(){list.PrintForward();}
    void PrintReverse(){list.PrintReverse();}

    // Insertion
    void enqueue(const T& item) override{
        list.AddTail(item);
    }

    // Deletion
    T dequeue() override{
        if (list.getCount()==0) throw std::runtime_error("array is empty");
        T t = peek();
        list.RemoveHead();
        return t;
    }

    // Access
    T peek() const override{
        if (list.getCount()==0) throw std::runtime_error("array is empty");
        return list.getData();
    }

    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }

};