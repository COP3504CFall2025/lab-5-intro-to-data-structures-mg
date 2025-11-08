#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>
#include <utility>

template <typename T>
class LLS : public StackInterface<T> {//LIFO

    LinkedList<T> list;

public:
    // Constructor
    LLS(){}

    LLS(const LLS<T>& other) : list(other.list){}

    LLS& operator=(const LLS<T>& other){//obg = a
        if(this == &other) return *this;
        list = other.list;
        return *this;
    }

    LLS(LLS<T>&& other) noexcept : list(std::move(other.list)){}

    LLS& operator=(LLS<T>&& other) noexcept{
        if(this == &other) return *this;
        list = std::move(other.list);
        return *this;
    }

    ~LLS(){}

    //print
    void PrintForward(){list.printForward();}
    void PrintReverse(){list.printReverse();}

    // Insertion
    void push(const T& item) override{
        list.AddHead(item);
    }

    // Deletion
    T pop() override{
        if (!(list.RemoveHead())) throw std::runtime_error("array is empty");
        T temp = list.getData();
        return temp;
    }

    // Access
    T peek() const override{
        if (list.getCount() == 0) throw std::runtime_error("array is empty");
        return list.getData();
    }

    //Getters
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }
};