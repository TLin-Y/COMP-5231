/** Tianlin Yang
	ID 40010303
	For Comp 5421/1-BB Assignment 1 - Revision 1
	Due May 31, 2019
*/

#include "LineList.h"

using namespace std;

struct LineList::Node {

private:
	Line data; // this node's data object
	Node* prev; // pointer to previous node
	Node* next; // pointer to next node

public:
	//------------------------------Start of Node members-------------------------

	// -----Ctor and Dtor-----
	Node(const Node&) = default; // Shallow copy ctor

	Node(const Line& line, Node* prev = nullptr, Node* next = nullptr)
		: data{ line }, prev{ prev }, next{ next } {};	// Ctor

	~Node() = default;//dtor

	// -----Set member functions and get member functions-----

	void setData(const Line& L) {	// Set input L(ine) type to data
		data = L;
	}

	const Line& getData() const {	// Get node's data object
		return data;
	}

	void setPrev(Node* p) {			// Set prev to Node* p
		prev = p;
	}


	Node* getPrev() const {			// Get prev
		return prev;
	}


	void setNext(Node* n) {			// Set next to Node* n
		next = n;
	}


	Node* getNext() const {			// Get next
		return next;
	}

}; // ----------------------------End of Node members------------------------------


LineList::LineList() { 	// default ctor
	// create dummy head node
	Node* dummyHead = new Node{ Line { "" } };
	head = dummyHead;

	// create dummy tail node
	Node* dummyTail = new Node{ Line { "" } };
	tail = dummyTail;

	// connect head to tail and tail to head
	// size remains zero. Do not count dummy nodes.
	dummyHead->setNext(dummyTail);
	dummyTail->setPrev(dummyHead);
}

LineList::~LineList() {  // dtor
	removeAll();
}

LineList::LineList(const LineList& rhs) { // copy ctor
	deepCopy(rhs);
}

const LineList& LineList::operator=(const LineList& rhs) { // copy assignment
	if (this != &rhs) { // nothing to do on self-assignment
		removeAll(); // release storage space currently used by *this (LHS)
		deepCopy(rhs); // copy rhs to *this
	}
	return *this;
}

void LineList::push_front(const Line& line) { // inserts line at the front of this list
	// point new node prev to dummyhead and new node next to first node 
	Node* newNode = new Node{ line, head, head->getNext() };

	// point 1st node prev to new node
	head->getNext()->setPrev(newNode);

	// point dummyhead node next to new node
	head->setNext(newNode);

	// increase list size by 1
	++theSize;
}


void LineList::push_back(const Line& line) { // inserts line at the back of this list
	// point new node prev to last node and new node next to dummytail
	Node* newNode = new Node{ line, tail->getPrev(), tail };

	// point last node next to new node
	tail->getPrev()->setNext(newNode);

	// point dummytail prev to new node
	tail->setPrev(newNode);

	// increase list size by 1
	++theSize;
}


void LineList::pop_front() { // removes the first line in this list
	// create temp pointer to popping node to deallocate space later
	Node* temp = head->getNext();

	if (temp != tail) { // Avoids popping dummy tail node
		// point the following to popping node's prev to head
		temp->getNext()->setPrev(head);

		// point head next to 2nd node
		head->setNext(temp->getNext());

		// decrease size
		--theSize;

		// deallocate space
		delete temp;
		temp = nullptr;
	}
}


void LineList::pop_back() { // removes the last line in this list
	// create temp pointer to popping node to deallocate space later
	Node* temp = tail->getPrev();

	if (temp != head) {
		// point the previous to popping node's next to tail
		temp->getPrev()->setNext(tail);

		// point tail prev to node before popping node
		tail->setPrev(temp->getPrev());

		// decrease size
		--theSize;

		// deallocate space
		delete temp;
		temp = nullptr;
	}
}


int LineList::size() const { // returns the size of this list
	return theSize;
}


bool LineList::empty() const { // returns whether this list is empty
	return (head->getNext() == tail) && (tail->getPrev() == head) && (theSize == 0);
}

void LineList::insert(const Line & line, int k) { // inserts a new node with line at 
												// position k in this list
	if (checkIndex(k)) { // Check index in range[1~size(list)]. 
		// Special case
		if (k == 1) {
			push_front(line);
			return;
		}

		//get pointer to the k-1 node
		Node* pre = find(k - 1);

		// get pointer to the current k node
		Node* pos = find(k);

		// create new node pointing to the prev and next to be nodes
		Node* newNode = new Node{ line, pre, pos };

		// update post node's prev
		pos->setPrev(newNode);

		// update prev node's next
		pre->setNext(newNode);
		++theSize;
	}
	else { // invalid index
		cerr << "Error. Invalid index. Unable to insert" << endl;
	}
}

void LineList::remove(int k) { // removes node at position k in this list
	if (checkIndex(k)) { // Check index in range[1~size(list)]
		// get pointer to the k node
		Node* kNode = find(k);

		// update pointers to skip k node
		kNode->getPrev()->setNext(kNode->getNext());
		kNode->getNext()->setPrev(kNode->getPrev());

		--theSize;
		delete kNode;
		kNode = nullptr;
	}
	else { // invalid index
		cerr << "Invalid index. Unable to remove." << endl;
	}
}


void LineList::print() const { //prints the lines
	Node* tempNode = head->getNext();
	int i{ 1 };
		while (tempNode->getNext() != NULL&&i<=9)
		{
			cout << "( " << i << ") " << tempNode->getData() << endl;
			tempNode = tempNode->getNext();
			++i;
		}

		while (tempNode->getNext() != NULL)
		{
			cout << "(" << i << ") " << tempNode->getData() << endl;
			tempNode = tempNode->getNext();
			++i;
		}
	
}



Line LineList::get(int position) const { //Returns the line at position k in this list
	if (checkIndex(position)) { // Check index in range[1~size(list)]
		Node* tempNode = find(position);
		//cout << tempNode->getData() << endl;  //Print using cout to indicate which is 'get'
		return tempNode->getData();
		tempNode = nullptr;
	}else { // invalid index
		cerr << "Invalid index. Unable to remove." << endl;
	}
}



void LineList::deepCopy(const LineList & original) { // deep copies the supplied LinkedList
	head = new Node{ Line { "" } };
	tail = new Node{ Line { "" }, head }; // tail points to head
	head->setNext(tail); // head points to tail
	theSize = original.size();

	if (original.empty())
		return; // *this object is good to go
	Node* current = original.head->getNext(); // point to first node in original list
	while (current != original.tail) { // stop at tail
		push_back(current->getData()); // copy original line at the end of the new list
		current = current->getNext(); // point to the following node in original list
	}
}


void LineList::removeAll() { // releases all nodes / Don't KEEP DUMMY HEAD AND TAIL / USED BY DESTRUCTOR
	while (!empty()) {
		pop_front();
	}
	delete head;
	head = nullptr;
	delete tail;
	tail = nullptr;
}


/** Check index in range.*/

bool LineList::checkIndex(int i) const {
	return !(i < 1 || i > size());
}

/** Return pointer at given position.*/

LineList::Node* LineList::find(int i) const
{
	if (i < 1 || i > size()) {
		return nullptr; // When bad index, return nullptr
	}
	else {
		Node* current = head;
		for (int n = 0; n < i; ++n) {
			current = current->getNext();
		}
		return current;
	}
}