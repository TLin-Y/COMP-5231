/** Tianlin Yang
	ID 40010303
	For Comp 5421/1-BB Assignment 1 - Revision 1
	Due May 31, 2019
*/

#ifndef LINE_LIST_H
#define LINE_LIST_H

#include "Line.h"

class LineList {
private:
	struct Node;				//A private member type (an inner class)
	int theSize{ 0 };			// number of elements in this list
	Node* head = { nullptr }; // pointer to the first node in this list
	Node* tail = { nullptr }; // pointer to the last node in this list


public:
	LineList(); // default ctor

	virtual ~LineList(); // dtor

	LineList(const LineList& rhs); // copy ctor

	const LineList& operator=(const LineList& rhs); // copy assignment

	void push_front(const Line& line); // inserts line at the front of this list

	void push_back(const Line& line); // inserts line at the back of this list

	void pop_front(); // removes the first line in this list

	void pop_back(); // removes the last line in this list

	int size() const; // returns the size of this list

	bool empty() const; // returns wether this list is empty

	void insert(const Line& line, int k); // inserts a new node with line at position k in this list

	void remove(int k); // removes node at position k in this list

	void print() const;// prints the whole Linelist

	Line get(int position) const;// prints the line stored in the node at given position----------------

private:
	bool checkIndex(int i) const; // returns whether a given index i is valid

	void deepCopy(const LineList& original);

	Node* find(int i) const; // returns a pointer to the node at position i

	void removeAll();

};
#endif // !LINE_LIST_H
