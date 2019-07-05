/*
Name: Tianlin Yang
ID: 40010303
C++ A2, 06/25/2019
*/

#include <algorithm>
#include <istream>
#include <string>
#include "Command.h"

using namespace std;


Command::Command(const string& inputLine) : address1("."), address2("."), symbol("p"),
 status(true)
{
	command_line = inputLine;

}

void Command::parse(const string& inputLine)
{
	command_line = inputLine;
	int letterIndex{ -1 }; // holds command letter index
	
	//remove blanks
	command_line.erase(remove(command_line.begin(), command_line.end(), '\t'), command_line.end());
	command_line.erase(remove(command_line.begin(), command_line.end(), ' '), command_line.end());
	//cout << "remove blanks finished!" << endl;

	// start parsing
	if (!command_line.empty())
	{	// find command letter
		if (command_line.substr(0,1).find_first_of("ertyosfhklzbm[];'<>?/¡°¡®}{|¡¢~£¡@#%¡­¡­&*£¨£©¡ª¡ª+=") != string::npos) {
			cerr << "bad command: " << command_line.substr(0, 1) << endl;
			setStatus(false);
		}
		else {
				letterIndex = command_line.substr(0, 1).find_first_of("aivdxjnpcugwq");
				//cout << "command: " << command_line << endl;
				//cout << "letterIndex ="<< letterIndex << endl;
				if (letterIndex == -1) // has range only, use full line to get range.
				{
					//cout << "Has address only!" << endl;
					// filter invalid chars
						symbol = 'p';
						parseAddress(command_line);//Hanlde: x | ,y | x, | x,y | , |
						//setStatus(false);//? -10,10 silly line addresses, same as p1,$ currently
					
				}
				else if ((letterIndex == 0) & (command_line.size()==1)) // has letter command only, use only line[0]
				{
					//cout << "Only has letter command" << endl;
					symbol = command_line[letterIndex];
					address1 = ".";
					address2 = ".";
				}
				else // has range and letter command, use first part of line to get range
				{
					//cout << "Range&command" << endl;
					symbol = command_line[letterIndex];
					// filter invalid chars
					if (command_line.substr(0, letterIndex).find_first_not_of(".,$1234567890") == string::npos)
						parseAddress(command_line.substr(1));//Hanlde: x | ,y | x, | x,y | , |
					else { // there is an invalid char, print current.
						cout << "Has valid symbol, but invalid address!" << endl;
						symbol = 'p';
						address1 = "1";
						address2 = "$";
						setStatus(false);
					}
				}
		}

		
	}
	else {	// just pressed enter. Same as p.,.
		cout << "Enter only, empty input!" << endl;
		address1 = ".";
		address2 = ".";
		symbol = 'p';
	}

}


/*takes a non-empty substring containing only the range section*/
void Command::parseAddress(const string& s)
{
	int separatorIndex{ -1 };
	bool hasSeparator;
	separatorIndex = s.find_first_of(",");
	//cout << "separatorIndex = " << separatorIndex << endl;
	if (separatorIndex == -1) // no address 2, just address 1
	{
		//cout << "no address 2, just address 1" << endl;
		hasSeparator = false;
		if (validate(s) == true) {
			address1 = s;
			address2 = s;
		}
		else {
			cout << "Bad address1: " << s << endl;
			setStatus(false);
		}
	}
	else if (separatorIndex == 0) // has ,?
	{
		hasSeparator = true;
		if (s.length() == 1) // has separator only, no address 1 or 2.
		{
			//cout << " has separator only, no address 1 or 2." << endl;
			address1 = ".";
			address2 = ".";
		}
		else	// has ,address2 handle y ,1$ as invalid
		{
			//cout << " has ,address2." << endl;
			if (validate(s.substr(1)) == true) {
				address1 = ".";
				address2 = s.substr(1);
			}
			else {
				cout << "Bad address2: " << s.substr(1) << endl;
				setStatus(false);
			}
		}
	}
	else if (separatorIndex > 0)  // has address1,?
	{	// look for address1
		//cout << " has address1,?" << endl;
		string address1Temp = s.substr(0, separatorIndex);
		string address2Temp = s.substr(separatorIndex+1);
		if (validate(address1Temp) == true) {
			hasSeparator = true;
			address1 = address1Temp;
		}
		else {
			cout << "Bad address1: " << s << endl;
			setStatus(false);
		}
		
		// look for address2
		if (separatorIndex != s.length() - 1) // if ',' is not the last char, it has address2
		{
			//cout << " has address1,address2 " << address1Temp << address2Temp << endl;
			if (validate(address2Temp) == true) {
				hasSeparator = true;
				address2 = address2Temp;
			}
			else {
				cout << "Bad address2: " << address2Temp << endl;
				setStatus(false);
			}
			
		}else {// No address2, only "address1,".
			//cout << " Only address1, " << endl;
			address2 = address1;
		}
	}
}

string Command::getAddress1() const
{
	return address1;
}

string Command::getAddress2() const
{
	return address2;
}

string Command::getSymbol() const
{
	return symbol;
}

bool Command::getStatus() const
{
	return status;
}

void Command::setStatus(bool s) {
	status = s;
}

bool Command::validate(const string& s) {
	if (s.size() > 1) {//handle 1$ , $1
		if (s.find_first_not_of("-1234567890") == string::npos) {//Good
			return true;
		}
		else {
			return false;
		}
	}
	else {//handle 1
		if (s.find_first_not_of("-$.1234567890") == string::npos) {//Good
			return true;
		}
		else {
			return false;
		}
	}

}