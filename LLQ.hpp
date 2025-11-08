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

    LLQ(const LLQ<T>& other) : list(other.list){}

    LLQ& operator=(const LLQ<T>& other){//obg = a
         if(this == &other) return *this;
        list = other.list;
        return *this;
    }

    LLQ(LLQ<T>&& other) noexcept : list(std::move(other.list)){}

    LLQ& operator=(LLQ<T>&& other) noexcept{
         if(this == &other) return *this;
        list = std::move(other.list);
        return *this;
    }

    ~LLQ(){}

    void PrintForward(){list.printForward();}
    void PrintReverse(){list.printReverse();}

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