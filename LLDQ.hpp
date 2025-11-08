#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ(){}

    LLDQ(const LLDQ<T>& other) {//LLDQ obj(a)
        LinkedList<T> newL(other.list);
        list = newL;
    }
    
    LLDQ& operator=(const LLDQ<T>& other){//obg = a
        list = other.list;
        return *this;
    }

    LLDQ(LLDQ<T>&& other) noexcept{
        LinkedList<T> newL(std::move(other.list));
        list = newL;
    }

    LLDQ& operator=(LLDQ<T>&& other) noexcept{
        list = std::move(other.list);
        return *this;
    }

    ~LLDQ(){}

    // Core Insertion Operations
    void pushFront(const T& item) override{
        list.addHead(item);
    }
    void pushBack(const T& item) override{
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override{
        T temp = list.getData();
        list.removeHead();
        return temp;
    }
    T popBack() override{
        T temp = list.getDataT();
        list.removeTail();
        return temp;
    }

    // Element Accessors
    const T& front() const override{
        return list.getHead()->data;
    }
    const T& back() const override{
        return list.getTail()->data;
    }
    void PrintForward(){list.printForward();}
    void PrintReverse(){list.printReverse();}
    
    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }
};






