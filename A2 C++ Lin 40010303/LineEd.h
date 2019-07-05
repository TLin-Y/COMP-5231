/*
Name: Tianlin Yang
ID: 40010303
C++ A2, 06/25/2019
*/

#include <list>
#include <string>
#include "Command.h"
#include <vector>

class LineEd {
public:
	LineEd() = delete;
	LineEd(const LineEd&) = delete;
	explicit LineEd(std::string);
	void run();
	void runCommand(const string&);

private:

	std::string& fname;
	std::string file;
	std::list <std::string> buffer;
	std::vector<string> clipboard;
	std::string* current{ nullptr };
	int currentLine{ 0 };
	Command order{""};
	bool changed{ false };

	/*Memeber functions: aivdxjpcugwq */
	void append();
	void insert(int pos);
	void pastes(int pos);
	void deletes(int x, int y);
	void cuts(int x, int y);
	void joins(int x, int y);
	void prints(int x, int y);
	void changes(int x, int y);
	void up();
	void down();
	void goes(int x);
	void write();
	void quit();

	/*Member functions which be used by others*/
	int strToInt(const string& x);//Covert Addresses "string" to "Int"
	void savefile();
}; // end of class LineEd

