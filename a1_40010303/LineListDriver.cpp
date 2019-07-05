/** Tianlin Yang
	ID 40010303
	For Comp 5421/1-BB Assignment 1 - Revision 1
	Due May 31, 2019
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cassert>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;

#include "Line.h"
#include "LineList.h"

// function prototypes
bool operator== (const LineList&, const LineList&);
bool operator!= (const LineList&, const LineList&);
void load_linked_list(const char*, LineList&);
void test_linked_list_operations(LineList&);

// -------
int main()
{
	const char* filename_a{ "C:\\input_a.txt" };
	const char* filename_b{ "C:\\input_b.txt" };

	LineList list_a{};
	load_linked_list(filename_a, list_a);      // load our first list list_a
	cout << "list_a loaded" << "\n";
	list_a.print();                           // print list_a

	test_linked_list_operations(list_a);      // manipulate lines in list_a
	cout << "\n" << "list_a rearranged" << "\n";
	list_a.print();                           // print manipulated list_a

	LineList list_b{};
	load_linked_list(filename_b, list_b);     // load our second list list_b
	assert(list_a == list_b);                 // test operator=

	cout << "Done!" << endl;
	return 0;                                // report success
}

/*
Loads the supplied line_list  with the lines of a given text file.
@ filename The name of the given text file.
@ line_list The LineList object to load.
*/
void load_linked_list(const char* filename, LineList & line_list)
{
	std::ifstream ifs(filename, std::ifstream::in);
	if (!ifs.is_open())
	{
		cout << "Unable to open file" << filename << endl;
		exit(0);
	}

	int lineno = 0;
	std::string line;
	while (getline(ifs, line)) // Read until end of file
	{
		++lineno;
		//cout << "(" << lineno << ") " << line << endl;
		const char* c_line = line.c_str(); // const makes this a safe idea.
		// Get a pointer to the c-string represented by the C++ string object
		// ONLY because Line's Ctor in the call below expects a char *
		line_list.push_back(Line(c_line));
	}
}

/*
Tests opeations provided by a given LineList object.
@ line_list The LineList object to use troughout the test.
*/

void test_linked_list_operations(LineList & line_list)
{

	if (line_list.empty()) return;                   // test empty()

	int lastPos = line_list.size();                  // size
	line_list.remove(lastPos);                       // remove
	if (line_list.empty()) return;                   // empty

	line_list.remove(1);                             // remove
	if (line_list.empty()) return;                   // empty

	Line lastline = line_list.get(line_list.size()); // get, copy ctor
	line_list.pop_back();                            // pop_back
	if (line_list.empty()) return;                   // empty

	Line line1 = line_list.get(1);                   // get
	line_list.pop_front();                           // pop_front()
	if (line_list.empty()) return;                   // empty

	line1 = line_list.get(1);                        // get, operator=
	line_list.pop_front();                           // pop_front();
	line_list.push_front(lastline);                  // push_front
	line_list.push_back(line1);                      // push_back
	if (line_list.size() >= 3)                       // size
		line_list.insert(Line("Line  3"), 3);         // insert

	line_list.insert(Line("Welcome to C++"), 1);     // insert
	line_list.push_back(Line("Have fun!"));          // push_back
}

/*
An oveload for operator==. Considers two lists equal
if they each have the same number of lines and same lines.
@ list1 The left hand side operand.
@ list2 The right hand side operand.
*/

bool operator== (const LineList & list1, const LineList & list2)
{
	if (list1.size() != list2.size()) return false;
	for (size_t i{ 1 }; i <= list1.size(); ++i)
	{
		if (list1.get(i) != list2.get(i)) return false;
	}
	return true;
}

/*
An overload for operator!=. Considers two lists unequal
if they they are not equal.
@ list1 The left hand side operand.
@ list2 The right hand side operand.
*/

bool operator!= (const LineList & list1, const LineList & list2)
{
	return !(list1 == list2);
}
