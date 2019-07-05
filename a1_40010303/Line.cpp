/** Tianlin Yang
	ID 40010303
	For Comp 5421/1-BB Assignment 1 - Revision 1 
	Due May 31, 2019
*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Line.h"

using namespace std;

Line::Line(const char* cstr) {
	lineLength = strlen(cstr); //Get length from 'cstr'
	lineCapacity = lineLength; //Assign length == capacity
	linePtr = new char[lineLength + 1]; //Create linePtr with length+1(ad+length)
	strcpy(linePtr, cstr);  //strcpy copy input string'cstr' to linePtr
}
 
Line::Line(const Line& l) {
	lineLength = l.lineLength;
	lineCapacity = lineLength;
	linePtr = new char[lineLength + 1];
	strcpy(linePtr, l.linePtr);
}


const Line& Line::operator=(const Line& rhs) {
	if (this == &rhs)
		return *this; // do nothing on self-assignment
	else {
		delete[] linePtr; // release dynamic storage currently used by calling object (LHS)
		lineLength = rhs.lineLength;
		lineCapacity = lineLength;
		linePtr = new char[lineLength + 1]; // allocate new storage
		strcpy(linePtr, rhs.linePtr); // copy									
	}
	return *this; // as const reference
}


Line::~Line() {
	lineLength = 0;
	lineCapacity = lineLength; //Clear Length&Capacity
	delete[] linePtr;	//Delete 
	linePtr = nullptr;   //Clear pointer for safety
}


const char* Line::cstr() const {
	return linePtr;	//Get line
}


int Line::length() const {
	return lineLength;//Get line length
}


bool Line::empty() const {
	return !(lineLength > 0);//Whether empty
}


bool Line::full() const {
	return (lineLength >= lineCapacity);//Whether full
}


int Line::capacity() const {
	return lineCapacity;//Capacity
}


void Line::resize() {
	int newCapacity = capacity() * 2; // Define doubled capacity
	char* tempArr = new char[newCapacity + 1]; // Allocate new storage 
	strcpy(tempArr, linePtr); // str copy
	lineCapacity = newCapacity; // set new line capacity(2x)
	delete[] linePtr; // Rrelease dynamic memory which currently be used by "linePtr"
	linePtr = tempArr; // Set linePtr to new dynamic memory
}


void Line::push_Back(const char& ch) {
	if (full())// Auto resize when full
		resize();
	linePtr[lineLength] = ch; // Append char to the end of this line
	linePtr[lineLength + 1] = '\0';// Append end char(by set null)
	lineLength++;
}


void Line::pop_Back() {
	if (!empty()) {// Check empty first
		linePtr[lineLength - 1] = '\0'; // Removes the last character in this line(by set null)
		lineLength--;
	}
}

// Friend members, privileged to see the private members of its parameter line

std::ostream& operator<<(ostream & out, const Line & line) {//Overloads operator << as a friend
	if (line.lineLength > 0)
		out << line.linePtr;//Output the line
	return out;
}


std::istream& operator>>(istream & in, Line & line) {//Overloads operator>> as a friend
	char c;
	while (in.get(c)) {
		if (line.full())
			line.resize();//Input to the line
		line.push_Back(c);
	}
	return in;
}


bool operator==(const Line& str1, const Line& str2) {//Overloads operator== as a friend
	const char* s1 = str1.cstr();
	const char* s2 = str2.cstr();
	int result = strcmp(s1, s2);// strcmp to compare line1 & line2
	if (result == 0) {
		return true;
	}
	else {
		return false;
	}
}; // free function

bool operator!=(const Line& str1, const Line& str2) {//Overloads operator!= as a friend
	const char* s1 = str1.cstr();
	const char* s2 = str2.cstr();
	int result = strcmp(s1, s2);
	if (result == 0) {
		return false;
	}
	else {
		return true;
	}
}; // free function
