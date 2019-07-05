/*
Name: Tianlin Yang
ID: 40010303
C++ A2, 06/25/2019
*/

#include<iostream>
#include<fstream>
#include<string>
#include "LineEd.h"

using namespace std;

LineEd::LineEd(std::string filename) : fname(filename)
{
	file = filename;
	if (filename.empty())
	{
		cout << "\"?\" [New File]" << endl;
	}
	else
	{
		cout << "filename is: " << filename << endl;
		ifstream fin;
		fin.open(filename); // opens file for input

							// if filename does not exist 
		if (!fin)
		{
			cerr << "Unable to open file " << filename << endl;
			cout << "\"" << filename << "\" " << "[New File]" << endl;
		}
		else // if filename exists read from it into the buffer line by line
		{
			int lineCounter{ 0 };
			string line;
			while (getline(fin, line))
			{
				//cout << line << endl;
				buffer.push_back(line);
				++lineCounter;
				currentLine = lineCounter;//Store total line number to curerentline.
			}
			// Show file name and number of lines
			cout << "\"" << filename << "\" " << lineCounter << " lines" << endl;
			cout << "Current line is " << currentLine << endl;
			cout << "Entering command mode." << endl;
		}
		// close stream
		fin.close();
	}


} // end of ctor

void LineEd::run()
{
	cout << "Entering command mode." << endl;
	while (true)
	{
		string iline{ "" };	// holds a line of input
		cout << "?";
		getline(cin, iline);
		Command temp{iline};
		temp.parse( iline );

		
		if (temp.getStatus())
		{
			order = temp;
			//cout << "Order: " << order.getSymbol() << endl;
			char getOrderSymbol = order.getSymbol()[0];
			
			int intAddress1 = strToInt(order.getAddress1());
			int intAddress2 = strToInt(order.getAddress2());
			if (intAddress1 > intAddress2) {//8.Regardless of how a line range is determined, the first line address cannot exceed the second line address; otherwise, LineEd will swap the two line addresses to ensure that the first line address is always less than or equal to the second line address.
				int temp = intAddress2;
				intAddress2 = intAddress1;
				intAddress1 = temp;
			}
			if (buffer.empty())
			{
				switch (getOrderSymbol)
				{
				case 'a':
				case 'i':
					cout << "Entering input mode." << endl;
					append();
					cout << "Entering command mode." << endl;
					break;
				case 'q':
					quit();
					break;
				case 'v'://Pastes with empty buffer;
					pastes(0);
					break;
				default:
					cerr << "File empty. Must use one of I,A,Q commands." << endl;
				}
			}
			else
			{
				switch (getOrderSymbol)
				{
				case 'a':
					cout << "Entering input mode." << endl;
					append();
					cout << "Entering command mode." << endl;
					break;
				case 'i':
					cout << "Entering input mode." << endl;
					insert(intAddress2);
					cout << "Entering command mode." << endl;
					break;
				case 'v'://Pastes with address;
					pastes(intAddress1);
					break;
				case 'n':
					down();
					//cout << "d=Down." << endl;
					break;
				case 'd':
					//cout << "d=delete." << endl;
					deletes(intAddress1, intAddress2);
					break;
				case 'x':
					cuts(intAddress1, intAddress2);
					break;
				case 'j':
					joins(intAddress1, intAddress2);
					break;
				case 'p':
					prints(intAddress1, intAddress2);
					break;
				case 'c':
					changes(intAddress1, intAddress2);
					break;
				case 'u':
					up();
					break;
				case 'g':
					goes(intAddress1);
					break;
				case 'w':
					write();
					break;
				case 'q':
					quit();
					break;
				case '=':
					cout << currentLine << endl;
					break;
				default:
					prints(intAddress1, intAddress2);
					break;
				} // end of switch
			} // end of else
		}
		else // temp is not valid
		{
			//cout << "Invalid." << endl;
		}
	} // end of while
} // end of run

void LineEd::runCommand(const string& iline)
{
	
	Command temp{ iline };
	temp.parse(iline);
		if (temp.getStatus())
		{
			order = temp;
			//cout << "Order: " << order.getSymbol() << endl;
			char getOrderSymbol = order.getSymbol()[0];
			int intAddress1 = strToInt(order.getAddress1());
			int intAddress2 = strToInt(order.getAddress2());
			if (intAddress1 > intAddress2) {//8.Regardless of how a line range is determined, the first line address cannot exceed the second line address; otherwise, LineEd will swap the two line addresses to ensure that the first line address is always less than or equal to the second line address.
				int temp = intAddress2;
				intAddress2 = intAddress1;
				intAddress1 = temp;
			}
			if (buffer.empty())
			{
				switch (getOrderSymbol)
				{
				case 'a':
				case 'i':
					cout << "Entering input mode." << endl;
					append();
					cout << "Entering command mode." << endl;
					break;
				case 'q':
					quit();
					break;
				case 'v'://Pastes with empty buffer;
					pastes(0);
					break;
				default:
					cerr << "File empty. Must use one of I,A,Q commands." << endl;
				}
			}
			else
			{
				switch (getOrderSymbol)
				{
				case 'a':
					cout << "Entering input mode." << endl;
					append();
					cout << "Entering command mode." << endl;
					break;
				case 'i':
					cout << "Entering input mode." << endl;
					insert(intAddress2);
					cout << "Entering command mode." << endl;
					break;
				case 'v'://Pastes
					pastes(intAddress1);
					break;
				case 'n':
					down();
					//cout << "d=Down." << endl;
					break;
				case 'd':
					//cout << "d=delete." << endl;
					deletes(intAddress1, intAddress2);
					break;
				case 'x':
					cuts(intAddress1, intAddress2);
					break;
				case 'j':
					joins(intAddress1, intAddress2);
					break;
				case 'p':
					prints(intAddress1, intAddress2);
					break;
				case 'c':
					changes(intAddress1, intAddress2);
					break;
				case 'u':
					up();
					break;
				case 'g':
					goes(intAddress1);
					break;
				case 'w':
					write();
					break;
				case 'q':
					quit();
					break;
				case '=':
					cout << currentLine << endl;
					break;
				default:
					prints(intAddress1, intAddress2);
					break;
				} // end of switch
			} // end of else
		}
		else // temp is not valid
		{
			//cout << "Invalid." << endl;
		}
}

int LineEd::strToInt(const string& x) {
	int intAddress;
	if (x.find_first_not_of(".,$1234567890") != string::npos) {
		//cout << "Invalid address!" << endl;
		return 1;
	}
	if (x == "$") {
		intAddress = buffer.size();
	}
	else if (x == ".") {
		intAddress = currentLine;
	}
	else {
		intAddress = std::stoi(x);
	}
	if (intAddress>buffer.size()) {
		//cout << "Out of buffer size!" << endl;
		return buffer.size();//7.If a line address exceeds the buffer size, then LineED defaults to the last line in the buffer.
	}
	if (intAddress < 0) {
		return 1;//6.If a line address is negative, then LineED defaults to the first line in the buffer.
	}
	return intAddress;

}

void LineEd::append()
{
	//cout << "inside append()" << endl;
	//cout << "Enter a new line:" << endl;
	string line;
	char t;
	getline(cin, line);
	//cout << "inside append has jumped 1st getline"<< endl;
	while (cin.good() && line != ".")
	{
		if (line.size()>=1 && line !="\n")
		buffer.push_back(line);
		changed = true;
		getline(cin, line);
	}
	// set current line to the last line appended
	currentLine = buffer.size();
}

void LineEd::insert(int pos)
{

	//cout << "inside insert(" << pos << ")" << endl;
	if (buffer.empty()) // append if empty
	{
		append();
	}
	else // not empty, insert before position
	{
		//cout << "Enter a new line:" << endl;
		string line;
		auto it = buffer.begin();
		// move iterator to position
		int i;
		for (i = 1; i < pos; ++i) {
			it++;
		}
		getline(cin, line);
		while (cin.good() && line != ".")
		{
			buffer.insert(it, line);
			changed = true;
			i++;
			getline(cin, line);
		}
		// make sure that the current line is set to the last line appended
		currentLine = --i;
	}
}


void LineEd::pastes(int x)
{
	//cout << "inside pastes(" << x << ")" << endl;
	string line;
	int i, i2;
	int j{ 0 };
	auto it = buffer.begin();
	if (buffer.empty() == true) {//Handle for single v pastes
		for (i = 1; i <= x; ++i) { it++; }
		for (i = 1; i <= clipboard.size() + x; ++i) {
			if (i >= x) {
				buffer.insert(it, clipboard.at(j));
				j++;
			}
		}
	}
	else {//Handle for v2 
		for (i = 0; i < x-1; ++i) { it++; }
		for (i = 1; i <= clipboard.size() + x - 1; ++i) {
			if (i >= x) {
				buffer.insert(it, clipboard.at(j));
				j++;
			}
		}
	}
	//Delete clipboard after pastes.
	clipboard.clear();

	changed = true;
	currentLine = i-1;

}

void LineEd::deletes(int x, int y)
{
	//Prerequisite x has to be > 0
	//cout << "inside remove(" << x << ", " << y << ")" << endl;

	if (y == buffer.size())
	{
		for (int i = y; i >= x; i--)
			buffer.pop_back();
		currentLine = x - 1;
	}
	else {
		// create 2 iterators
		auto iterX = begin(buffer);
		auto iterY = begin(buffer);
		// move iterator x to x position
		advance(iterX, x - 1);
		// move iterator y to position after y
		advance(iterY, y);
		// delete range (x,y)
		buffer.erase(iterX, iterY);
		currentLine = x;
	}
	changed = true;
}

void LineEd::cuts(int x, int y)
{
	if (x > y) {
		int temp = y;
		y = x;
		x = temp;
	}
	//cout << "inside cuts(" << x << ", " << y << ")" << endl;
	//check range
	auto it = buffer.begin();
	int i;
	for (i = 1; i <= y; ++i) {
		if (i >= x) {
			clipboard.push_back(*it);//cuts line range to clipboard.
		}
		it++;
	}
	deletes(x, y);//Remove old lines in range.
	changed = true;
	if(y==buffer.size()){// y is the end of buffer.
		if (x > 1) {//Has line before x.
			currentLine = x-1;//Line x-1 becomes the currentline.
		}
		if (x == 1) {//Cuts all buffer range.
			currentLine = NULL;//Currentline set undifined. 
		}
	}
	else if (y < buffer.size()) {// y is not the end.
		currentLine = y+1;//Line y-1 becomes the currentline.
	}

}


/*Joins the text from the specified line range together on one line at address x,
concatenating the characters in the lines. Line x becomes the current line.*/
void LineEd::joins(int x, int y)
{
	//cout << "inside joins(" << x << ", " << y << ")" << endl;
	string concat;
	auto it = buffer.begin();
	int i;
	for (i = 1; i <= y; ++i) {
		if (i >= x) {
				concat += *it;//Concatenating line range to CONCAT string.
		}
		it++;
	}
	deletes(x, y);//Remove old lines in range.
	//Insert concat to line x.
		auto it2 = buffer.begin();
		// move iterator to position
		int i2;
		for (i2 = 1; i2 < x; ++i2) {
			it2++;
		}
		buffer.insert(it2, concat);
		changed = true;

	currentLine = x;//Line x becomes the currentline.
}

/*Prints the line range x through y without affecting the current line address.*/
void LineEd::prints(int x, int y)
{
	auto it = buffer.begin();
	int i;
	for (i = 1; i <= y; ++i) {
		if (i >= x) {
			if (i == currentLine) {
				cout << i <<"> "<< *it << endl;
			}
			else
			{
				cout << i << ": " << *it << endl;
			}
		}
		it++;
	}
}

/*The current line address is set to the last line changed.*/
void LineEd::changes(int x, int y)
{
	//cout << "Inside change(" << x << ", " << y << ")" << endl;
	string target;
	string replacement;
	// prompt and read target text

		cout << "Change?" << endl;
		cin >> target;

	// prompt and read replacement text

		cout << "To?" << endl;
		cin >> replacement;

	// search for ocurrence and // change matched string
	int i = 1;
	int lastChanged = x;
	for (auto it = begin(buffer); it != end(buffer); it++, i++)
	{
		if (i >= x && i <= y) // on each string in range
		{
			//cout << "it is: " << *it << endl;
			//cout << "i is: " << i << endl;
			// look for an ocurrence
			if (it->find(target) != string::npos)
			{	// replace part of string that matches
				//cout << "inside if (it->find...)" << endl;
				it->replace(it->find(target), target.length(), replacement);
				lastChanged = i;
			}
		}
	}
	currentLine = lastChanged;
}

/* Ignores line range, if any. Moves the current line down by one line provided
that there is a line after the current line; otherwise, prints the message EOF
reached and sets the current line to the last line in the buffer.*/
void LineEd::up()
{
	auto currentIter = begin(buffer); // iterator to current line
	for (int i = 1; i < currentLine; i++) // move to current line
		++currentIter;

		if (currentIter == begin(buffer))
		{
			cout << "BOF reached" << endl;
		}
		else {
			--currentIter;
			--currentLine;
			prints(currentLine, currentLine);
		}
}

/* Ignores line range, if any. Moves the current line up by one line provided
that there is a line above the current line; otherwise, prints the message BOF
reached and sets the current line to the rst line in the buffer.*/
void LineEd::down()
{
	auto currentIter = begin(buffer); // iterator to current line
	for (int i = 1; i < currentLine; i++) // move to current line
		++currentIter;
		if (currentIter == --end(buffer))
		{
			cout << "EOF reached" << endl;
		}else {
			++currentIter;
			++currentLine;
			prints(currentLine, currentLine);
		}

}

/*Ignores line address 2, if any. Goes to the specified line x, meaning that it sets
the current line to x and prints it.*/
void LineEd::goes(int x)
{
	currentLine = x;
	prints(x, x);
}

/*Ignores line range, if any. If there is a file associated with the buffer, it prompts
the user asking whether it is OK to replace that file with the buffer contents. If
the answer is negative, or there is no file associated with the buffer, it prompts
the user for the name of a file to save the buffer to.*/
void LineEd::write()
{
	if (changed)
	{
		if (fname.empty()||file.size()<1)
		{
			savefile();
		}
		else{//fname != empty.

		//cout << "There are unsaved changes." << endl;
		char save{ '\0' };
		while (true)
		{
			
			cout << "Save changes to the file: " << file << " (y or n)? " << endl;
			cin >> save;
			if (save == 'Y' || save == 'y' || save == 'N' || save == 'n')
				break;
		}
		if (save == 'Y' || save == 'y')
		{
			ofstream fout;//create file for saving operation
			fout.open(file);
			for (auto it = begin(buffer); it != end(buffer); ++it)
				fout << *it << endl;
			cout << buffer.size() << " lines written to file " << "\"" << file << "\"" << endl;
			currentLine = buffer.size();
			fout.close();
			changed = false;

		}
		else
			savefile();
		}
	}
}

/*Ignores line range, if any. Quits LineEd. Before quitting, however, it gives the
user a last chance to save the buffer. If the user takes the chance, it simulates
the w command, and then quits; otherwise, it quits, discarding buffer contents.*/
void LineEd::quit()
{
	if (changed)
	{
		cout << "There are unsaved changes." << endl; 
		char save{ '\0' };
		while (true)
		{
			cout << "Do you wish to save the changes (y or n)?" << endl;
			cin >> save;
			if (save == 'Y' || save == 'y' || save == 'N' || save == 'n')
				break;
		}
		if (save == 'Y' || save == 'y')
		{
			write();
			exit(0);
		}
		else
			exit(0);// discarding buffer contents.
	}
	else
	{
		exit(0);// discarding buffer contents.
	}
}

void LineEd::savefile() {
	int repeat{ 1 };
	while (repeat == 1) {
		string f;
		cout << "Enter the name of a file to write to:" << endl;
		cin >> f;
		ifstream infile(f);//check exist file name or not
		bool find = infile.good();
		char replace{ '\0' };

		if (!find)
		{
			//cout << "File not found." << endl;
			ofstream fout;//create file for saving operation
			fout.open(f);
			for (auto it = begin(buffer); it != end(buffer); ++it)
				fout << *it << endl;
			cout << buffer.size() << " lines written to file " << "\"" << f << "\"" << endl;
			fout.close();
			changed = false;
			repeat = 0;
		}
		else {
			//cout << "File has found." << endl;
			while (true)
			{
				cout << "Replace file? y/n:" << endl;
				cin >> replace;
				if (replace == 'Y' || replace == 'y' || replace == 'N' || replace == 'n')
					break;
			}
			if (replace == 'Y' || replace == 'y')
			{
				ofstream fout;//create file for saving operation
				fout.open(f);
				for (auto it = begin(buffer); it != end(buffer); ++it)
					fout << *it << endl;

				changed = false;
				fout.close();
				repeat = 0;
			}
			else {
				cout << "Discarding buffer contents." << endl;// discarding buffer contents.
				repeat = 0;
			}
		}
	}
}





