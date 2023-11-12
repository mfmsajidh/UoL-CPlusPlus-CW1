#include <string>
using std::string;

class FlexArray {

public:
	FlexArray();

	FlexArray(const int* arr, int size);

	~FlexArray();

	// Copy constructor
	FlexArray(const FlexArray& other);

	// Copy assignment
	FlexArray& operator=(const FlexArray& other);

	// PRINTING AND SIZE INFORMATION

	// Return the number of elements
	int getSize() const;

	// Return the capacity, i.e. the size of the internal array,
	// part of which may not contain the intended elements.
	int getCapacity() const;

	// Return a string that lists all elements, in order, separated by
	// a space and a comma, and with square brackets at the beginning
	// and the end, e.g. "[4, 2, 13, 5, 77]"
	string print() const;

	// Return a string that shows the contents of the internal array
	// including unoccupied spaces with an X, following the notation
	// described in the assignment page, e.g.
	// "[X, 4, 2, 13, 5, 77, X, X, X]"
	string printAll() const;

	// GETTERS AND SETTERS

	// Return the element at index i.
	int get(int i) const;

	// Set the element at index i to v, and return true afterwards.
	// If i is out of bounds, return false and do nothing.
	bool set(int i, int v);

	// STRUCTURAL MODIFIERS

	// You should also resize the data structure and recenter the
	// elements, if required, as described in the assignment

	// Insert v to the back
	void push_back(int v);

	// Remove last element and return true
	// If FlexArray is empty, return false and do nothing
	bool pop_back();

	// Insert v to the front
	void push_front(int v);

	// Remove first element and return true
	// If FlexArray is empty, return false and do nothing
	bool pop_front();

	// Insert v so that it is at index i, pushing others either to
	// the left or right as described in the assignment, and return
	// true afterwards.
	// If index is out of bounds, return false and do nothing.
	bool insert(int i, int v);

	// Erase the element at index i, shifting others either to the
	// left or right as described in the assignment, and return
	// true afterwards.
	// If index is out of bounds, or the FlexArray is empty,
	// return false and do nothing.
	bool erase(int i);

	// We didn't explain what static and constexpr are, but you can just
	// use them in FlexArray.cpp just like normal constants
	// DO NOT CHANGE, MOVE OR REMOVE IT
	static constexpr int INITIALCAP = 5;
	static constexpr int LO_THRESHOLD = 3;
	static constexpr int HI_THRESHOLD = 7;

private:
	int* arr_;
    int size;
    int capacity;
};
