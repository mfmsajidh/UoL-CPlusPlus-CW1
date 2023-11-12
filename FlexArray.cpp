#include "FlexArray.h"
#include <string>
#include <iostream>

using namespace std;

FlexArray::FlexArray() {
    size = 0;
    capacity = INITIALCAP;
    arr_ = new int[capacity];
}

FlexArray::FlexArray(const int* arr, int size) {
    int newCapacity = LO_THRESHOLD * size;
    arr_ = new int[newCapacity];
    int startIndex = (newCapacity - size) / 2;
    for (int i = 0; i < size; ++i) {
        arr_[startIndex + i] = arr[i];
    }
    this->size = size;
    capacity = newCapacity;
}

FlexArray::~FlexArray() {
    delete[] arr_;
}

FlexArray::FlexArray(const FlexArray& other) : arr_(nullptr), size(other.size), capacity(other.capacity) {
    arr_ = new int[capacity];
    for (int i = 0; i < capacity; ++i) {
        arr_[i] = other.arr_[i];
    }
}

FlexArray& FlexArray::operator=(const FlexArray& other) {
    if (this != &other) {
        delete[] arr_;
        size = other.size;
        capacity = other.capacity;
        arr_ = new int[capacity];
        for (int i = 0; i < capacity; ++i) {
            arr_[i] = other.arr_[i];
        }
    }
    return *this;
}

int FlexArray::getSize() const {
    return size;
}

int FlexArray::getCapacity() const {
    return capacity;
}

string FlexArray::print() const {
    if (size == 0) {
        return "[]";
    }

    string result = "[";
    for (int i = 0; i < size - 1; ++i) {
        result += std::to_string(arr_[i]) + ", ";
    }
    result += std::to_string(arr_[size - 1]) + "]";

    return result;
}

string FlexArray::printAll() const {
    string result = "[";
    for (int i = 0; i < size; ++i) {
        if (i < (capacity - size) / 2 || i >= (capacity + size) / 2) {
            result += "X";
        } else {
            result += std::to_string(arr_[i - (capacity - size) / 2]);
        }
        if (i < size - 1) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}

int FlexArray::get(int i) const {
    if (i >= 0 && i < size) {
        int internalIndex = i + (capacity - size) / 2;
        return arr_[internalIndex];
    } else {
        return -1;
    }
}

bool FlexArray::set(int i, int v) {
    if (i >= 0 && i < size) {
        int internalIndex = i + (capacity - size) / 2;
        arr_[internalIndex] = v;
        return true;
    } else {
        return false;
    }
}

void FlexArray::push_back(int v) {
    if (size >= capacity) {
        int newCapacity = LO_THRESHOLD * size;
        int newInternalSize = newCapacity + 2 * (HI_THRESHOLD - LO_THRESHOLD);
        int* newArr = new int[newInternalSize];

        int start = (newInternalSize - size) / 2;
        for (int i = 0; i < size; ++i) {
            newArr[start + i] = arr_[i];
        }

        delete[] arr_;
        arr_ = newArr;
        capacity = newCapacity;
    }

    int internalIndex = (capacity - size) / 2 + size;
    arr_[internalIndex] = v;
    ++size;
}

bool FlexArray::pop_back() {
    if (size == 0) {
        return false;
    }

    --size;

    if (size <= capacity / 2 && capacity > INITIALCAP) {
        int newCapacity = LO_THRESHOLD * size;
        int newInternalSize = newCapacity + 2 * (HI_THRESHOLD - LO_THRESHOLD);
        int* newArr = new int[newInternalSize];

        int start = (newInternalSize - size) / 2;
        for (int i = 0; i < size; ++i) {
            newArr[start + i] = arr_[i];
        }

        delete[] arr_;
        arr_ = newArr;
        capacity = newCapacity;
    }
    return true;
}

void FlexArray::push_front(int v) {
    if (size + 1 > capacity) {
        int newCapacity = LO_THRESHOLD * (size + 1);
        int newInternalSize = newCapacity + 2 * (HI_THRESHOLD - LO_THRESHOLD);
        int* newArr = new int[newInternalSize];

        int start = (newInternalSize - (size + 1)) / 2;
        for (int i = 0; i < size; ++i) {
            newArr[start + i + 1] = arr_[i];
        }

        delete[] arr_;
        arr_ = newArr;
        capacity = newCapacity;
    } else {
        int start = (capacity - (size + 1)) / 2;
        for (int i = size; i > 0; --i) {
            arr_[start + i] = arr_[start + i - 1];
        }
    }

    arr_[(capacity - (size + 1)) / 2] = v;
    ++size;
}

bool FlexArray::pop_front() {
    if (size == 0) {
        return false;
    }

    int start = (capacity - size) / 2;
    for (int i = 0; i < size - 1; ++i) {
        arr_[start + i] = arr_[start + i + 1];
    }

    --size;

    if (size < capacity / 2 && capacity > INITIALCAP) {
        int newCapacity = LO_THRESHOLD * size;
        int newInternalSize = newCapacity + 2 * (HI_THRESHOLD - LO_THRESHOLD);
        int* newArr = new int[newInternalSize];

        int newStart = (newInternalSize - size) / 2;
        for (int i = 0; i < size; ++i) {
            newArr[newStart + i] = arr_[start + i];
        }

        delete[] arr_;
        arr_ = newArr;
        capacity = newCapacity;
    }
    return true;
}

bool FlexArray::insert(int i, int v) {
    if (i < 0 || i > size) {
        return false;
    }

    if (size == capacity) {
        int newCapacity = HI_THRESHOLD * size;
        int newInternalSize = newCapacity + 2 * (HI_THRESHOLD - LO_THRESHOLD);
        int* newArr = new int[newInternalSize];

        int start = (newInternalSize - size) / 2;
        for (int j = 0; j < size; ++j) {
            newArr[start + j] = arr_[start + j];
        }

        delete[] arr_;
        arr_ = newArr;
        capacity = newCapacity;
    }

    int start = (capacity - size) / 2;
    for (int j = size - 1; j >= i; --j) {
        arr_[start + j + 1] = arr_[start + j];
    }

    arr_[start + i] = v;

    ++size;

    return true;
}

bool FlexArray::erase(int i) {
    if (i < 0 || i >= size) {
        return false;
    }

    int start = (capacity - size) / 2;
    for (int j = i; j < size - 1; ++j) {
        arr_[start + j] = arr_[start + j + 1];
    }

    --size;

    if (size < capacity / 2 && capacity > INITIALCAP) {
        int newCapacity = size * 2;
        int newInternalSize = newCapacity + 2 * (HI_THRESHOLD - LO_THRESHOLD);
        int* newArr = new int[newInternalSize];

        for (int j = 0; j < size; ++j) {
            newArr[start + j] = arr_[start + j];
        }

        delete[] arr_;
        arr_ = newArr;
        capacity = newCapacity;
    }

    return true;
}
