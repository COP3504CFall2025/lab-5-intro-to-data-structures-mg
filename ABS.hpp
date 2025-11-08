#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS(){
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[1];
    }
    explicit ABS(const size_t capacity) :
    capacity_(capacity), curr_size_(0), array_(new T[capacity]){}

    ABS(const ABS& other) :
    capacity_(other.capacity_), curr_size_(other.curr_size_), array_(new T[other.capacity_]){
        for(size_t i = 0; i < curr_size_; i++)
            array_[i] = other.array_[i];
    }

    ABS& operator=(const ABS& rhs){
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
    ABS(ABS&& other) noexcept : 
    capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }

    ABS& operator=(ABS&& rhs) noexcept{
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
    ~ABS() noexcept override{
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override{return curr_size_;}

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept{return capacity_;}

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept{return array_;}

    // Push item onto the stack
    void push(const T& data) override{
        if(curr_size_ == capacity_){
            capacity_ = (capacity_ == 0) ? 1 : (capacity_ * scale_factor_);
            T* t = new T[capacity_];
            std::copy(array_, array_ + curr_size_, t);
            delete[] array_;
            array_ = t;
        }
        array_[curr_size_++] = data;
    }

    // void shrinkIfNeeded(){
    //     if (curr_size_ <= capacity_/4){
    //         size_t newCap = (capacity_ == 2) ? 1 : (capacity_ / 2);
    //         T* t = new T[newCap];
    //         for(size_t i = 0; i < curr_size_; i++){
    //             t[i] = data_[i];
    //         }
    //         delete[] array_;
    //         capacity_ = newCap;
    //         array_ = t;
    //     }
    // }

    T peek() const override{
        if (curr_size_ == 0) throw std::runtime_error("array is empty");
        return array_[curr_size_-1];}

    T pop() override{
        if (curr_size_ == 0) throw std::runtime_error("array is empty");
        curr_size_--; 
        T t = array_[curr_size_];
        // shrinkIfNeeded();
        return t;
    }

    void PrintForward(){
        for(size_t i = 0; i < curr_size_; i++){
            std::cout << array_[i] << " ";
        }
        std::cout << std::endl;
    }

    void PrintReverse(){
        for(size_t i = curr_size_; i > 0; i--){
            std::cout << array_[i-1] << " ";
        }
        std::cout << std::endl;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
