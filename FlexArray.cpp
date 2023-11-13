#include "FlexArray.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// Constructors and Destructor
FlexArray::FlexArray() : arr_(new int[INITIALCAP]), size_(0), capacity_(INITIALCAP), headroom_(INITIALCAP / 2), tailroom_(INITIALCAP / 2) {}

FlexArray::FlexArray(const int* arr, int size) : size_(size), capacity_(LO_THRESHOLD * size) {
    arr_ = new int[capacity_];
    headroom_ = (capacity_ - size_) / 2;
    tailroom_ = capacity_ - headroom_ - size_;
    for (int i = 0; i < size_; ++i) {
        arr_[headroom_ + i] = arr[i];
    }
    cout << "Constructor headroom: " << headroom_ << endl;
    cout << "Constructor tailroom: " << tailroom_ << endl;
}

FlexArray::~FlexArray() {
    delete[] arr_;
}

FlexArray::FlexArray(const FlexArray& other) : size_(other.size_), capacity_(other.capacity_), headroom_(other.headroom_), tailroom_(other.tailroom_) {
    arr_ = new int[capacity_];

    // Not using the below code since I'm having doubt whether can I use it as per the assignment guide or not
//    copy(other.arr_, other.arr_ + capacity_, arr_);

    for (int i = 0; i < capacity_; ++i) {
        arr_[i] = other.arr_[i];
    }
}

FlexArray& FlexArray::operator=(const FlexArray& other) {
    if (this != &other) {
        delete[] arr_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        headroom_ = other.headroom_;
        tailroom_ = other.tailroom_;
        arr_ = new int[capacity_];

        // Not using the below code since I'm having doubt whether can I use it as per the assignment guide or not
//        copy(other.arr_, other.arr_ + capacity_, arr_);

        for (int i = 0; i < capacity_; ++i) {
            arr_[i] = other.arr_[i];
        }
    }
    return *this;
}

// Printing and Size Information
string FlexArray::print() const {
    stringstream ss;
    ss << "[";
    for (int i = 0; i < size_; ++i) {
        ss << arr_[headroom_ + i];
        if (i < size_ - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

string FlexArray::printAll() const {
    cout << "printAll headroom_: " << headroom_ << endl;
    cout << "printAll tailroom_: " << tailroom_ << endl;
    stringstream ss;
    ss << "[";
    for (int i = 0; i < capacity_; ++i) {
        if (i >= headroom_ && i < headroom_ + size_) {
            ss << arr_[i];
        } else {
            ss << "X";
        }
        if (i < capacity_ - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

int FlexArray::getSize() const {
    return size_;
}

int FlexArray::getCapacity() const {
    return capacity_;
}

// Getters and Setters
int FlexArray::get(int i) const {
    if (i >= 0 && i < size_) {
        return arr_[headroom_ + i];
    }
    return -1; // Undefined behavior if index is out of bounds
}

bool FlexArray::set(int i, int v) {
    if (i >= 0 && i < size_) {
        arr_[headroom_ + i] = v;
        return true;
    }
    return false;
}

// Structural Modifiers
void FlexArray::push_back(int v) {
    if (size_ >= capacity_ - tailroom_) {
        resizeAndRecenter(LO_THRESHOLD * (size_ + 1));
    }
    arr_[headroom_ + size_] = v;
    ++size_;
    --tailroom_;
}

bool FlexArray::pop_back() {
    if (size_ == 0) return false;
    --size_;
    ++tailroom_;
    if (size_ <= capacity_ / HI_THRESHOLD && capacity_ > INITIALCAP) {
        resizeAndRecenter(LO_THRESHOLD * size_);
    }
    return true;
}

void FlexArray::push_front(int v) {
    // Resize if no headroom is available
    if (headroom_ == 0) {
        resizeAndRecenter(LO_THRESHOLD * (size_ + 1));
    }

    // Move existing elements to the right to make space for the new element
    for (int i = size_ - 1; i >= 0; --i) {
        arr_[headroom_ + i + 1] = arr_[headroom_ + i];
    }

    // Insert the new element at the front
    arr_[headroom_] = v;
    ++size_;

    // Update tailroom only (headroom remains the same after a push_front)
    tailroom_ = capacity_ - headroom_ - size_;

    cout << "push_front headroom_: " << headroom_ << endl;
    cout << "push_front tailroom_: " << tailroom_ << endl;

}


bool FlexArray::pop_front() {
    if (size_ == 0) return false;
    ++headroom_;
    --size_;
    if (size_ <= capacity_ / HI_THRESHOLD && capacity_ > INITIALCAP) {
        resizeAndRecenter(LO_THRESHOLD * size_);
    }
    return true;
}

bool FlexArray::insert(int i, int v) {
    if (i < 0 || i > size_) return false;
    if (size_ >= capacity_ - tailroom_) {
        resizeAndRecenter(LO_THRESHOLD * (size_ + 1));
    }
    for (int j = size_; j > i; --j) {
        arr_[headroom_ + j] = arr_[headroom_ + j - 1];
    }
    arr_[headroom_ + i] = v;
    ++size_;
    --tailroom_;
    return true;
}

bool FlexArray::erase(int i) {
    if (i < 0 || i >= size_) return false;
    for (int j = i; j < size_ - 1; ++j) {
        arr_[headroom_ + j] = arr_[headroom_ + j + 1];
    }
    --size_;
    ++tailroom_;
    if (size_ <= capacity_ / HI_THRESHOLD && capacity_ > INITIALCAP) {
        resizeAndRecenter(LO_THRESHOLD * size_);
    }
    return true;
}

void FlexArray::resizeAndRecenter(int newCapacity) {
    int* newArr = new int[newCapacity];
    int newHeadroom = (newCapacity - size_) / 2;
    for (int i = 0; i < size_; ++i) {
        newArr[newHeadroom + i] = arr_[headroom_ + i];
    }
    delete[] arr_;
    arr_ = newArr;
    capacity_ = newCapacity;
    headroom_ = newHeadroom;
    tailroom_ = newCapacity - newHeadroom - size_;
}
