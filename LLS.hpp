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

    LLS(const LLS<T>& other) {//LLS obj(a)
        LinkedList<T> newL(other.list);
        list = newL;
    }

    LLS& operator=(const LLS<T>& other){//obg = a
        list = other.list;
        return *this;
    }

    LLS(LLS<T>&& other) noexcept{
        LinkedList<T> newL(std::move(other.list));
        list = newL;
    }

    LLS& operator=(LLS<T>&& other) noexcept{
        list = std::move(other.list);
        return *this;
    }

    ~LLS(){}

    //print
    void PrintForward(){list.printForward();}
    void PrintReverse(){list.printReverse();}

    // Insertion
    void push(const T& item) override{
        list.addHead(item);
    }

    // Deletion
    T pop() override{
        T temp = list.getData();
        list.removeHead();
        return temp;
    }

    // Access
    T peek() const override{
        return list.getData();
    }

    //Getters
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }
};