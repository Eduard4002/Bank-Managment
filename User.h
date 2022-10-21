#pragma once
#include <string>
struct Transaction {
	unsigned short fromID;
	unsigned short toID;
	unsigned int amount;

	Transaction(unsigned short _fromID, unsigned short _toID, unsigned int _amount) {
		fromID = _fromID;
		toID = _toID;
		amount = _amount;
	}
};
class User {
public:
	static const int variableAmount = 6;
	int ID = 0;
	std::string fName, lName, userN, passw;
	int balance = 0;

	bool WithDraw(int amount);
	bool Deposit(int amount);
	void SaveInfo();
	void SaveTransaction(Transaction);
	void SendTo(std::string to, unsigned int amount);

	User(int ID, std::string fname, std::string lname, std::string userN, std::string passw, int balance);
};