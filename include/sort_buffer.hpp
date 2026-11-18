
// Headers and Libraries

#pragma once // Include the header only once in a compilation unit

#include <cstddef> // Provides std::size_t(unsigned integers) which we use to represent the elements in an array

/*
We define a class called SortBuffer, it's responsibility is to:
  1.Allocate memory for an integer array
  2.Keep track of its size
  3.Allow other parts of the program to access its elements
  4.Free the allocate memory when it is no longer needed
*/

class SortBuffer {
public:
    explicit SortBuffer(std::size_t size)
        : data_(new int[size]), size_(size) {} // Constructor for the class without implicit conversions

    ~SortBuffer() {
        delete[] data_;
    } // Destructor

    SortBuffer(const SortBuffer&) = delete; // We do not allow copy constructors
    SortBuffer& operator=(const SortBuffer&) = delete; // We do not allow copy assignments

    int* begin() noexcept {
        return data_;
    } // Return the address of the first element which throws no exceptions

    int* end() noexcept {
        return data_ + size_;
    } // Return the address of the last element which throws no exceptions

    // We define the same functions for the constant type of the SortBuffer

    const int* begin() const noexcept {
        return data_;
    }

    const int* end() const noexcept {
        return data_ + size_;
    }

    std::size_t size() const noexcept {
        return size_;
    } // Return the size of the sort buffer

private:
    int* data_;
    std::size_t size_; // The sort buffer has a size and an array(pointer to the first element of the array)
};
