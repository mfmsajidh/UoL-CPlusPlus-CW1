#include "FlexArray.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// Constructors and Destructor
FlexArray::FlexArray() : arr_(new int[INITIALCAP]), size(0), capacity(INITIALCAP), headroom_(INITIALCAP / 2), tailroom_(INITIALCAP / 2) {}

FlexArray::FlexArray(const int* arr, int size) : size(size), capacity(LO_THRESHOLD * size) {
    arr_ = new int[capacity];
    headroom_ = (capacity - size) / 2;
    tailroom_ = capacity - headroom_ - size;
    for (int i = 0; i < size; ++i) {
        arr_[headroom_ + i] = arr[i];
    }
}

FlexArray::~FlexArray() {
    delete[] arr_;
}

FlexArray::FlexArray(const FlexArray& other) : size(other.size), capacity(other.capacity), headroom_(other.headroom_), tailroom_(other.tailroom_) {
    arr_ = new int[capacity];
    copy(other.arr_, other.arr_ + capacity, arr_);
}

FlexArray& FlexArray::operator=(const FlexArray& other) {
    if (this != &other) {
        delete[] arr_;
        size = other.size;
        capacity = other.capacity;
        headroom_ = other.headroom_;
        tailroom_ = other.tailroom_;
        arr_ = new int[capacity];
        copy(other.arr_, other.arr_ + capacity, arr_);
    }
    return *this;
}

// Printing and Size Information
string FlexArray::print() const {
    stringstream ss;
    ss << "[";
    for (int i = 0; i < size; ++i) {
        ss << arr_[headroom_ + i];
        if (i < size - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

string FlexArray::printAll() const {
    stringstream ss;
    ss << "[";
    for (int i = 0; i < capacity; ++i) {
        if (i >= headroom_ && i < headroom_ + size) {
            ss << arr_[i];
        } else {
            ss << "X";
        }
        if (i < capacity - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

int FlexArray::getSize() const {
    return size;
}

int FlexArray::getCapacity() const {
    return capacity;
}

// Getters and Setters
int FlexArray::get(int i) const {
    if (i >= 0 && i < size) {
        return arr_[headroom_ + i];
    }
    return -1; // Undefined behavior if index is out of bounds
}

bool FlexArray::set(int i, int v) {
    if (i >= 0 && i < size) {
        arr_[headroom_ + i] = v;
        return true;
    }
    return false;
}

// Structural Modifiers
void FlexArray::push_back(int v) {
    if (size >= capacity - tailroom_) {
        resizeAndRecenter(LO_THRESHOLD * (size + 1));
    }
    arr_[headroom_ + size] = v;
    ++size;
    --tailroom_;
}

bool FlexArray::pop_back() {
    if (size == 0) return false;
    --size;
    ++tailroom_;
    if (size <= capacity / HI_THRESHOLD && capacity > INITIALCAP) {
        resizeAndRecenter(LO_THRESHOLD * size);
    }
    return true;
}

void FlexArray::push_front(int v) {
    // Resize if no headroom is available
    if (headroom_ == 0) {
        resizeAndRecenter(LO_THRESHOLD * (size + 1));
    }

    // Move existing elements to the right to make space for the new element
    for (int i = size - 1; i >= 0; --i) {
        arr_[headroom_ + i + 1] = arr_[headroom_ + i];
    }

    // Insert the new element at the front
    arr_[headroom_] = v;
    ++size;

    // Update tailroom only (headroom remains the same after a push_front)
    tailroom_ = capacity - headroom_ - size;
}


bool FlexArray::pop_front() {
    if (size == 0) return false;
    ++headroom_;
    --size;
    if (size <= capacity / HI_THRESHOLD && capacity > INITIALCAP) {
        resizeAndRecenter(LO_THRESHOLD * size);
    }
    return true;
}

bool FlexArray::insert(int i, int v) {
    if (i < 0 || i > size) return false;
    if (size >= capacity - tailroom_) {
        resizeAndRecenter(LO_THRESHOLD * (size + 1));
    }
    for (int j = size; j > i; --j) {
        arr_[headroom_ + j] = arr_[headroom_ + j - 1];
    }
    arr_[headroom_ + i] = v;
    ++size;
    --tailroom_;
    return true;
}

bool FlexArray::erase(int i) {
    if (i < 0 || i >= size) return false;
    for (int j = i; j < size - 1; ++j) {
        arr_[headroom_ + j] = arr_[headroom_ + j + 1];
    }
    --size;
    ++tailroom_;
    if (size <= capacity / HI_THRESHOLD && capacity > INITIALCAP) {
        resizeAndRecenter(LO_THRESHOLD * size);
    }
    return true;
}

void FlexArray::resizeAndRecenter(int newCapacity) {
    int* newArr = new int[newCapacity];
    int newHeadroom = (newCapacity - size) / 2;
    for (int i = 0; i < size; ++i) {
        newArr[newHeadroom + i] = arr_[headroom_ + i];
    }
    delete[] arr_;
    arr_ = newArr;
    capacity = newCapacity;
    headroom_ = newHeadroom;
    tailroom_ = newCapacity - newHeadroom - size;
}
