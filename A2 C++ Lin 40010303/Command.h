/*
Name: Tianlin Yang
ID: 40010303
C++ A2, 06/25/2019
*/

#pragma once
#ifndef COMMAND_H
#define COMMAND_H

#include<iostream>
#include<string>

using std::string;

/*Represents a command and is in charge of parsing that command into its
components*/
class Command {
public:

	Command(const string& inputLine);
	void parse(const string& inputLine);
	string getAddress1() const;
	string getAddress2() const;
	string getSymbol() const;
	bool getStatus() const;
	void setStatus(bool s);


private:
	string command_line;
	bool status;			// flag indicating the command is valid
	string symbol;		// the command letter
	string address1;		// start address in line range
	string address2;
	void parseAddress(const string& s);
	bool validate(const string& s);
}; // end of class Command

#endif // !COMMAND_H
