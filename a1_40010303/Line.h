/** Tianlin Yang
	ID 40010303
	For Comp 5421/1-BB Assignment 1 - Revision 1
	Due May 31, 2019
*/

#ifndef LINE_H
#define LINE_H

#include <iostream>

class Line {
private:
	char* linePtr{ nullptr };/** Stores a pointer to the first character in a dynamically 
							 created array of char, effectively representing the underlying 
							 line of text.*/

	int lineLength{ 0 };			// Length of this line
	int lineCapacity{ 0 };			// Storage capacity of this line

public:
	Line() = delete; // specific requirement------------

	explicit Line(const char* cstr); /**	Constructs this line, assigning linePtr a pointer 
									 to a deep copy of the supplied C-string text */

	Line(const Line& l); // copy ctor

	const Line& operator=(const Line& rhs); // copy assignment operator overload.

	virtual ~Line(); // releases dynamic memory owned by this line

	const char* cstr() const; // returns C-style version of this Line

	int length() const; // returns length of this line

	bool empty() const; // returns whether this line is empty

	bool full() const; // returns whether this line is full

	int capacity() const; // returns capacity of this line

	void resize(); // doubles capacity of this line

	void push_Back(const char& ch); // appends ch to the end of this line

	void pop_Back(); // removes the last char in this line


	friend	// prints this line Overloads operator << as a friend
		std::ostream& operator<<(std::ostream& out, const Line& line);

	friend	// reads into this line Overloads operator>> as a friend
		std::istream& operator>>(std::istream& in, Line& line);

	friend bool operator==(const Line& str1, const Line& str2); // free function

	friend bool operator!=(const Line& str1, const Line& str2); // free function

}; // class Line

#endif // !LINE_H