#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
        ABQ(){
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[1];
    }
    explicit ABQ(const size_t capacity) :
    capacity_(capacity), curr_size_(0), array_(new T[capacity]){}

    ABQ(const ABQ& other) :
    array_(new T[other.capacity_]), capacity_(other.capacity_), curr_size_(other.curr_size_){
        for(size_t i = 0; i < curr_size_; i++)
            array_[i] = other.array_[i];
    }

    ABQ& operator=(const ABQ& rhs){
        if(this == &rhs) return *this;
        T* temp = new T[rhs.capacity_];
        delete[] array_;
        array_ = temp;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        for(size_t i = 0; i < curr_size_; i++){
            array_[i] = rhs.array_[i];
        }
        return *this;

    }
    ABQ(ABQ&& other) noexcept : 
    array_(other.array_), capacity_(other.capacity_), curr_size_(other.curr_size_){
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept{
        if(this == &rhs) return *this;
        delete[] array_;
        array_ = rhs.array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;

        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
        return *this;
    }
    ~ABQ() noexcept override{
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override{return curr_size_;}
    [[nodiscard]] size_t getMaxCapacity() const noexcept{return capacity_;}
    [[nodiscard]] T* getData() const noexcept{return array_;}

    // Insertion
    void enqueue(const T& data) override{
        if(curr_size_ == capacity_){
            capacity_ = (capacity_ == 0) ? 1 : (capacity_ << 1);
            T* t = new T[capacity_];
            std::copy(array_, array_ + curr_size_, t);
            delete[] array_;
            array_ = t;
        }
        array_[curr_size_++] = data;
    }

    // Access
    T peek() const override{return array_[0];}

    // Deletion
    T dequeue() override{
        curr_size_--;
        T* t = new T[capacity_];
        std::copy(array_ + 1, array_ + curr_size_, t);
        delete[] array_;
        array_ = t;
    }

};
