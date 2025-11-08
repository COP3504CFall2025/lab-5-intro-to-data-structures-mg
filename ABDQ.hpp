#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : capacity_(4), size_(0), front_(0), back_(0){
        data_ = new T[capacity_];
    }

    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0) {
        data_ = new T[capacity];
    }

    ABDQ(const ABDQ& other) : 
    data_(new T[other.capacity_]), capacity_(other.capacity_),
    size_(other.size_), front_(other.front_), back_(other.back_){
        for(size_t i = 0; i < size_; i++)
            data_[i] = other.data_[i];
    }

    ABDQ(ABDQ&& other) noexcept : 
    data_(other.data_), capacity_(other.capacity_), 
    size_(other.size_), front_(other.front_), back_(other.back_){
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other){
        if(this == &other) return *this;
        T* temp = new T[other.capacity_];
        delete[] data_;
        data_ = temp;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        for(size_t i = 0; i < size_; i++){
            data_[i] = other.data_[i];
        }
        return *this;
    }

    ABDQ& operator=(ABDQ&& other) noexcept{
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }

    ~ABDQ() override{
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void ensureCapacity(){
        size_t newCap = (capacity_ == 0) ? 1 : (capacity_ * SCALE_FACTOR);
        T* t = new T[newCap];
        for(size_t i = 0; i < size_; i++){
            t[i] = data_[(front_+ i) % capacity_];
        }
        delete[] data_;
        capacity_ = newCap;
        front_ = 0;
        back_ = size_;
        data_ = t;
    }

    void pushFront(const T& item) override{
        if(size_ == capacity_) ensureCapacity();
        front_ = (front_ - 1 + capacity_) % capacity_;
        data_[front_] = item;
        size_++;    
    }

    void pushBack(const T& item) override{
        if(size_ == capacity_) ensureCapacity();
        data_[back_] = item;
        back_ = (back_+1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override{
        if (size_ == 0) throw std::runtime_error("array is empty");
        T t = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        shrinkIfNeeded();
        return t;
    }

    T popBack() override{
        if (size_ == 0) throw std::runtime_error("array is empty");
        back_ = (back_ - 1 + capacity_) % capacity_;
        T t = data_[back_];
        size_--;
        shrinkIfNeeded();
        return t;
    }

    void shrinkIfNeeded(){
        if (size_ <= capacity_/4){
            size_t newCap = (capacity_ == 2) ? 1 : (capacity_ /= 2);
            T* t = new T[newCap];
            for(size_t i = 0; i < size_; i++){
                t[i] = data_[(front_+ i) % capacity_];
            }
            delete[] data_;
            capacity_ = newCap;
            front_ = 0;
            back_ = size_;
            data_ = t;
        }
    }
    
    void PrintForward(){
        for(size_t i = 0; i < size_; i++){
            std::cout << data_[(front_+ i) % capacity_] << " ";
        }
        std::cout << std::endl;
    }

    void PrintReverse(){
        for(size_t i = 0; i < size_; i++){
            std::cout << data_[(back_ - 1 - i + capacity_) % capacity_] << " ";
        }
        std::cout << std::endl;
    }
    // Access
    const T& front() const override{
        if (size_ == 0) throw std::runtime_error("array is empty");
        return data_[front_];}
    const T& back() const override{
        if (size_ == 0) throw std::runtime_error("array is empty");
        return data_[back_-1];}

    // Getters
    std::size_t getSize() const noexcept override{return size_;}

};
