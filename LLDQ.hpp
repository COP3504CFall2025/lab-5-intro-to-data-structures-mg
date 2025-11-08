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

    LLDQ(const LLDQ<T>& other) : list(other.list){}
    
    LLDQ& operator=(const LLDQ<T>& other){//obg = a
        if(this == &other) return *this;
        list = other.list;
        return *this;
    }

    LLDQ(LLDQ<T>&& other) noexcept : list(std::move(other.list)){}

    LLDQ& operator=(LLDQ<T>&& other) noexcept{
        if(this == &other) return *this;
        list = std::move(other.list);
        return *this;
    }

    ~LLDQ(){}

    // Core Insertion Operations
    void pushFront(const T& item) override{
        list.AddHead(item);
    }
    void pushBack(const T& item) override{
        list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override{
        if (list.getCount()==0) throw std::runtime_error("array is empty");
        T temp = list.getData();
        list.RemoveHead();
        return temp;
    }
    T popBack() override{
        if (list.getCount()==0) throw std::runtime_error("array is empty");
        T temp = list.getDataT();
        list.RemoveTail();
        return temp;
    }

    // Element Accessors
    const T& front() const override{
        if (list.getCount()==0) throw std::runtime_error("array is empty");
        return list.getHead()->data;
    }
    const T& back() const override{
        if (list.getCount()==0) throw std::runtime_error("array is empty");
        return list.getTail()->data;
    }
    void PrintForward(){list.printForward();}
    void PrintReverse(){list.printReverse();}
    
    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }
};






